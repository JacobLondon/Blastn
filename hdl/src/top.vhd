library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Top is
    Generic (
        g_RSTCNT: POSITIVE := 5;
        g_SIZE : POSITIVE := 16;    -- 
        g_BITS : POSITIVE := 32;
        g_LENGTH : POSITIVE := 160
    );
    Port (
        clk : in  STD_LOGIC;
        rst : in  STD_LOGIC;
        rx  : in  STD_LOGIC;
        tx  : out STD_LOGIC;
        enable : in  STD_LOGIC;
        led : out STD_LOGIC
    );
end Top;

architecture Blastn of Top is
    
    component Collector
        Generic ( 
            g_CLK_PER_BIT : POSITIVE:= 100000000 / 256000;          -- FPGA clock / baud rate
            g_SIZE        : POSITIVE:= 16;      -- Max. size of registers
            g_BITS        : POSITIVE:= 32
        );
        Port ( 
            i_clk         : in  STD_LOGIC;
            i_rx          : in  STD_LOGIC;
            --i_rst         : in  STD_LOGIC;
            
            --
            --
            --
            --
            -- TODO -------------------------------------------------------
            -- FIX g_SIZE
            --
            --
            --
            
            o_query       : out STD_LOGIC_VECTOR(g_SIZE - 1 downto 0);
            o_subject     : out STD_LOGIC_VECTOR(g_SIZE - 1 downto 0);
            co_done       : out STD_LOGIC;
            o_size        : out POSITIVE;
            o_index       : out NATURAL;
            o_count       : out NATURAL
    
            -- *** Used for thorough simulation of Collector
            --o_size        : out STD_LOGIC_VECTOR(g_BITS - 1 downto 0);
            --o_gap_start   : out STD_LOGIC_VECTOR(g_BITS - 1 downto 0);
            --o_gap_count   : out STD_LOGIC_VECTOR(g_BITS - 1 downto 0);
            --co_byte       : out STD_LOGIC_VECTOR(7 downto 0)
    );
    end component;
    
    component ScoreTx
        Generic (
            g_CLK_PER_BIT : POSITIVE := 100000000 / 256000;          -- FPGA clock / baud rate
            g_BITS        : POSITIVE := 32
        );
        Port (
            i_clk         : in  STD_LOGIC;
            --i_rst         : in  STD_LOGIC;
            i_enable      : in  STD_LOGIC;
            i_score       : in  STD_LOGIC_VECTOR(g_BITS - 1 downto 0);
            o_tx          : out STD_LOGIC;
            o_ready       : out STD_LOGIC
            
            -- *** Used for thorough simulation of ScoreTx
            --byte          : out STD_LOGIC_VECTOR(7 downto 0);
            --enable        : out STD_LOGIC;
            --ready         : out STD_LOGIC;
            --done          : out STD_LOGIC
        );
    end component;
    
    component ScoreMatrixSq
        generic (
            g_RSTCNT : POSITIVE := 10;
            g_MATSIZE : POSITIVE := 10; -- square matrix size
            g_BITS : POSITIVE := 32;    -- result size in bits (ie. 32-bit integer result)
            g_LENGTH : POSITIVE := 100  -- length of the query and subject in letters
        );
        port (
            clk         : in  STD_LOGIC;    -- board clock
            rst         : in  STD_LOGIC;    -- reset the score counter
            done        : out STD_LOGIC;
            
            -- Smith-Waterman match, mismatch, and gap scores
            i_match     : in  SIGNED(1 downto 0);
            i_mismatch  : in  SIGNED(1 downto 0);
            i_gap       : in  SIGNED(1 downto 0);
            
            i_query     : in  STD_LOGIC_VECTOR(g_LENGTH * 3 - 1 downto 0);  -- the query, groups of 3 adjacent bits per character
            i_subject   : in  STD_LOGIC_VECTOR(g_LENGTH * 2 - 1 downto 0);  -- the subject, groups of 2 adjacent bits per character
            o_score     : out UNSIGNED(g_BITS - 1 downto 0)             -- Smith-Waterman max score
        );
    end component;
        
    signal collector_done : STD_LOGIC:= '0';
    signal tx_ready : STD_LOGIC:= '0';
    
    signal subject, query : STD_LOGIC_VECTOR(g_SIZE - 1 downto 0):= (others => '0');
    signal size : POSITIVE := 1;
    signal index, count : NATURAL:= 0;
    
    signal score: UNSIGNED(31 downto 0):= X"7FFFFFFF";
    
    --
    --
    --
    --
    --TODO IS THIS RIGHT?
    --
    constant match : SIGNED(1 downto 0) := "10";
    constant mismatch : SIGNED(1 downto 0) := "11";
    constant gap : SIGNED(1 downto 0) := "11";

begin

    SCORE_TRANSMITTER: ScoreTx
        generic map (
            g_CLK_PER_BIT => 100000000 / 256000
        )
        port map (
            i_clk    => clk,
            --i_rst    => rst,
            i_enable => enable,
            i_score  => STD_LOGIC_VECTOR(score),
            o_tx     => tx,
            o_ready  => tx_ready
        );

    DATA_RECEIVER: Collector
        generic map (
            g_CLK_PER_BIT => 100000000 / 256000
        )
        port map (
            i_clk   => clk,
            --i_rst   => rst,
            i_rx    => rx,
            o_query => query,
            o_subject => subject,
            co_done => collector_done,
            o_size  => size,
            o_index => index,
            o_count => count
        );

    led <= tx_ready;

--    MAIN: process
--    begin
--        if (collector_done = '1') then
--            wait for 30 ns;
--            enable <= '1';
--            wait for 30ns;
--            enable <= '0';
--        end if;
--    end process MAIN;

    SmithWaterman: ScoreMatrixSq
        generic map (
            g_RSTCNT  => g_RSTCNT,
            g_MATSIZE => g_SIZE,
            g_BITS    => g_BITS,
            g_LENGTH  => g_LENGTH
        )
        port map (
            clk => clk,
            rst => collector_done,
            i_match => match,
            i_mismatch => mismatch,
            i_gap => gap,
            i_query => query,
            i_subject => subject,
            o_score => score
        );

end Blastn;