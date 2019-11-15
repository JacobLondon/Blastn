library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ScoreMatrix is
    Generic (
        g_SIZE     : POSITIVE := 1000;
        g_BITS     : POSITIVE := 32;
    );
    Port (
        clk         : in  STD_LOGIC;
        rst         : in  STD_LOGIC;
        go          : in  STD_LOGIC;
        i_match     : in  SIGNED(1 downto 0);
        i_mismatch  : in  SIGNED(1 downto 0);
        i_gap       : in  SIGNED(1 downto 0);
        i_length    : in  UNSIGNED(g_BITS - 1 downto 0);         -- length of the query or the subject
        i_gap_start : in  UNSIGNED(g_BITS - 1 downto 0);         -- gap start index in the query
        i_gap_count : in  UNSIGNED(g_BITS - 1 downto 0);         -- number of gaps in the query
        i_query     : in  STD_LOGIC_VECTOR(g_SIZE - 1 downto 0); -- the query
        i_subject   : in  STD_LOGIC_VECTOR(g_SIZE - 1 downto 0); -- the subject
        o_score     : out UNSIGNED(g_BITS - 1 downto 0)          -- Smith-Waterman max score
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

    type MATRIX is array(0 to g_SIZE - 1) of STD_LOGIC_VECTOR(g_SIZE - 1 downto 0);
    
    signal m_score_matrix : MATRIX := (others => (others => '0'));

    -- Smith-Waterman score counter
    -- refer to page 4 of https://arxiv.org/pdf/1803.02657.pdf

    signal r_score : UNSIGNED(g_BITS - 1 downto 0) := (others => '0');
    signal r_en    : STD_LOGIC;
    signal r_dis   : STD_LOGIC;

begin

    r_en <= go;
    r_dis <= '1' when unsigned(m_score_matrix(g_SIZE - 1)(g_SIZE - 1 downto g_SIZE - g_BITS)) > 0 else '0';

    SCORE_COUNTER: process(clk) is
    begin
        if rising_edge(clk) then
            -- synchronous reset
            if rst = '1' then
                r_score <= (others => '0');
                r_en    <= '1';
                r_dis   <= '0';
            -- only increment the score if the
            elsif r_en = '1' and r_dis = '0' then
                r_score = r_score + 1;
            end if;
        end if;
    end process;

    ROW: for i in 1 to g_SIZE - 1 generate
        COLUMN: for j in 1 to g_SIZE / 2 - 1 generate
            CURRENT_CELL: Cell
                Port map (
                    s        => i_subject(i),
                    q        => i_query(j*2),
                    match    => i_MATCH,
                    mismatch => i_MISMATCH,
                    gap      => i_GAP,
                    diag     => m_score_matrix(i - 1)(j*2 - 1 downto j*2 - 2),
                    up       => m_score_matrix(i - 1)(j*2 + 1 downto j*2    ),
                    left     => m_score_matrix(i    )(j*2 - 1 downto j*2 - 2),
                    score    => m_score_matrix(i    )(j*2 + 1 downto j*2    )
                );
        end generate;
    end generate;

end Blastn;
