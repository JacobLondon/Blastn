library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ScoreMatrix is
    generic (
        g_MATSIZE : POSITIVE := 10; -- square matrix size
        g_BITS : POSITIVE := 32;    -- result size in bits (ie. 32-bit integer result)
        g_LENGTH : POSITIVE := 100  -- length of the query and subject in letters
    );
    port (
        clk         : in  STD_LOGIC;    -- board clock
        rst         : in  STD_LOGIC;    -- reset the score counter
        rx_done     : in  STD_LOGIC;
        tx_done     : in  STD_LOGIC;
        
        -- Smith-Waterman match, mismatch, and gap scores
        i_match     : in  SIGNED(1 downto 0);
        i_mismatch  : in  SIGNED(1 downto 0);
        i_gap       : in  SIGNED(1 downto 0);
        
        i_length    : in  UNSIGNED(g_BITS - 1 downto 0);            -- length of the query or the subject
        i_query     : in  STD_LOGIC_VECTOR(g_LENGTH * 3 - 1 downto 0);  -- the query, groups of 3 adjacent bits per character
        i_subject   : in  STD_LOGIC_VECTOR(g_LENGTH * 2 - 1 downto 0);  -- the subject, groups of 2 adjacent bits per character
        o_score     : out UNSIGNED(g_BITS - 1 downto 0)             -- Smith-Waterman max score
    );
end ScoreMatrix;

architecture Blastn of ScoreMatrix is

    component Cell is
        Port (
            s        : in  STD_LOGIC_VECTOR(1 downto 0);
            q        : in  STD_LOGIC_VECTOR(2 downto 0);
            match    : in  SIGNED(1 downto 0);
            mismatch : in  SIGNED(1 downto 0);
            gap      : in  SIGNED(1 downto 0);
            diag     : in  STD_LOGIC_VECTOR(1 downto 0);
            up       : in  STD_LOGIC_VECTOR(1 downto 0);
            left     : in  STD_LOGIC_VECTOR(1 downto 0);
            score    : out STD_LOGIC_VECTOR(1 downto 0)
        );
    end component;
    
    -- twice as many columns to hold each score (2 adjacent bits)
    type MATRIX is array(0 to g_MATSIZE - 1) of STD_LOGIC_VECTOR(g_MATSIZE * 2 - 1 downto 0);
    signal m_score_matrix : MATRIX := (others => (others => '0'));

    -- Smith-Waterman score counter
    -- refer to page 4 of https://arxiv.org/pdf/1803.02657.pdf

    signal r_score : UNSIGNED(g_BITS - 1 downto 0) := (others => '0');
    signal r_score_en : STD_LOGIC;
    signal rx_rst, tx_rst : STD_LOGIC;
    signal done : STD_LOGIC;
    -- indicate whether any bits at the bottom are 1
    signal r_botbit : STD_LOGIC;

    -- hold the current state of the score system
    signal r_state : UNSIGNED(2 downto 0);

    -- the next SIZE letters from the query and subject
    signal q_buf : STD_LOGIC_VECTOR(g_MATSIZE * 3 - 1 downto 0);
    signal s_buf : STD_LOGIC_VECTOR(g_MATSIZE * 2 - 1 downto 0);

    -- auto disable max value for the current score segment
    constant MAX_STEP_COUNT : INTEGER := 10;
    signal r_step_count : UNSIGNED(g_BITS - 1 downto 0);
    signal r_step_en : STD_LOGIC;

    -- Count number of letters processed. Indicate scoring is over when
    -- this value equals the query_size
    signal r_shift_count : UNSIGNED(g_BITS - 1 downto 0);

begin

    r_botbit <= '1' when UNSIGNED(m_score_matrix(g_MATSIZE - 1)(g_MATSIZE - 1 downto 0)) > 0 else '0';
    o_score  <= r_score;

    SCORE_COUNTER: process (clk) is
    begin
        if rising_edge(clk) then
            -- synchronous reset
            if rst = '1' then
                r_state <= (others => '0');
            -- only increment the score if the
            elsif r_score_en = '1' then
                r_score <= r_score + 1;
            end if;
        end if;
    end process;

    STEP_COUNTER: process (clk) is
    begin
        if rising_edge(clk) then
            if r_step_en = '1' then
                r_step_count <= r_step_count + 1;
            end if;
        end if;
    end process;

    STATE_MACHINE: process (clk) is
    begin
        if rising_edge(clk) then
            case r_state is
                -- start
                when x"0" =>
                    r_score <= (others => '0');
                    r_step_en <= '0';
                    r_score_en <= '0';
                    q_buf <= (others => '0');
                    s_buf <= (others => '0');
                    done  <= '0';
                    if rx_done = '1' then
                        r_state <= x"1";
                    else
                        r_state <= x"0";
                    end if;
                -- load
                when x"1" => 
                    r_score_en <= '0';
                    r_step_en  <= '0';
                    r_step_count <= (others => '0');

                    q_buf <=   i_query(to_integer(r_shift_count) downto to_integer(r_shift_count) - g_MATSIZE);
                    s_buf <= i_subject(to_integer(r_shift_count) downto to_integer(r_shift_count) - g_MATSIZE);
                    r_state <= x"2";
                when x"2" => 
                    r_shift_count <= r_shift_count + g_MATSIZE;
                    r_state <= x"3";
                when x"3" => 
                    r_score_en <= '1';
                    r_step_en  <= '1';
                    if r_botbit = '1' or r_step_count = MAX_STEP_COUNT then
                        if r_shift_count >= g_LENGTH then
                            r_state <= x"4";
                        else
                            r_state <= x"1";
                        end if;
                    else
                        r_state <= x"3";
                    end if;
                when x"4" => 
                    r_score_en <= '0';
                    done <= '1';
                    if tx_done = '1' then
                        r_state <= x"0";
                    else
                        r_state <= x"4";
                    end if;
                when others => r_state <= (others => '0');
            end case;
        end if;
    end process;

    -- traverse each query and subject letter
    ROW: for i in 1 to g_MATSIZE - 1 generate
        COLUMN: for j in 1 to g_MATSIZE - 1 generate
            CURRENT_CELL: Cell
                Port map (
                    s        => s_buf(i*2 downto i*2 - 1),
                    q        => q_buf(j*3 downto j*3 - 2),
                    match    => i_MATCH,
                    mismatch => i_MISMATCH,
                    gap      => i_GAP,
                    diag     => m_score_matrix(i - 1)(j*2 - 1 downto j*2 - 2),
                    up       => m_score_matrix(i - 1)(j*2 - 1 downto j*2 - 2),
                    left     => m_score_matrix(i    )(j*2 - 1 downto j*2 - 2),
                    score    => m_score_matrix(i    )(j*2 + 1 downto j*2)
                );
        end generate;
    end generate;

end Blastn;
