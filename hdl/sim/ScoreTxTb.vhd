library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ScoreTxTb is
    Generic (
        tb_CLK_PER_BIT : POSITIVE:= 100000000 / 256000;         -- Needs to be set correctly
        tb_BITS        : POSITIVE:= 32
    );
end ScoreTxTb;

architecture Blastn of ScoreTxTb is

    component UartRx
        Generic ( 
            g_CLK_PER_BIT : POSITIVE:= 100000000 / 256000       -- FPGA clock / baud rate
        );
        Port ( 
            i_clk         : in  STD_LOGIC;
            i_rx          : in  STD_LOGIC;                      -- Serial bit being received/sampled
            o_byte        : out STD_LOGIC_VECTOR(7 downto 0);
            o_done        : out STD_LOGIC                       -- Byte received flag
        );
    end component;

    component ScoreTx
        Generic (
            g_CLK_PER_BIT : POSITIVE:= 100000000 / 256000;
            g_BITS        : POSITIVE:= 16
        );
        Port (
            i_clk         : in  STD_LOGIC;
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
    
    signal wt        : TIME:= 5ns;
    
    signal tb_clk    : STD_LOGIC:= '0';
    signal tb_enable : STD_LOGIC:= '0';
    signal tb_ready  : STD_LOGIC:= '0';
    signal tb_tx     : STD_LOGIC:= '1';
    signal tb_done   : STD_LOGIC:= '0';
    
    signal tb_score  : STD_LOGIC_VECTOR(tb_BITS - 1 downto 0):= (others => '0');
    signal tb_byte   : STD_LOGIC_VECTOR(7 downto 0):= (others => '0');
    
    -- *** Used for thorough simulation of ScoreTx
    --signal tx_byte : STD_LOGIC_VECTOR(7 downto 0):= (others => '0');
    --signal tx_ready : STD_LOGIC:= '0';
    --signal tx_enable : STD_LOGIC:= '0';
    --signal tx_done   : STD_LOGIC:= '0';

begin
    
    SCORE_TX_INST: ScoreTx
        Generic map (
            g_CLK_PER_BIT => tb_CLK_PER_BIT,
            g_BITS        => tb_BITS
        )
        Port map (
            i_clk         => tb_clk,
            i_enable      => tb_enable,
            i_score       => tb_score,
            o_tx          => tb_tx,
            o_ready       => tb_ready
            --byte          => tx_byte,
            --enable        => tx_enable,
            --ready         => tx_ready,
            --done          => tx_done
        );
    
    UART_RX_INST: UartRx
        Generic map (
            g_CLK_PER_BIT => tb_CLK_PER_BIT
        )
        Port map (
            i_clk         => tb_clk,
            i_rx          => tb_tx,
            o_byte        => tb_byte,
            o_done        => tb_done
        );

    CLK_GEN: process      -- Generates 100 MHz clock signal
    begin
                
        tb_clk <= '1';
        wait for wt;
        tb_clk <= '0';
        wait for wt;

    end process CLK_GEN;

    SIM_GEN: process
    begin
        
        -- (FPGA clock period) * (g_CLK_PER_BIT) for 1 bit
        -- 1 start bit, 8 bit data, 1 stop bit
        -- Approx. 39.0625 micro-seconds for 1 byte to transfer (100 MHz clock and 256000 baud rate)
        
        tb_enable <= '0';
        wait for 2*wt;
        tb_score <= X"ABCDEF12";
        tb_enable <= '1';
        wait for wt;
        tb_enable <= '0';
        wait for 32001*wt;      -- Approx. (((FPGA clock period) * (g_CLK_PER_BIT) * 10) * 4)/5

    end process SIM_GEN;
end Blastn;