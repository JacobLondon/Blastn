library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity UartTb is
        generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);
end UartTb;

architecture Blastn of UartTb is

    component UartTx
        generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);        -- Needs to be set correctly
        Port    (
                  i_clk         : in  STD_LOGIC;
                  i_enable      : in  STD_LOGIC;
                  i_byte        : in  STD_LOGIC_VECTOR(7 downto 0);    -- Byte to be transmitted 
                  o_tx          : out STD_LOGIC;                       -- Individual serial bits transmission        
                  o_ready       : out STD_LOGIC                        -- Active transmission flag
                );
    end component;
 
    component UartRx
        generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);        -- FPGA clock / baud rate
        Port    ( 
                  i_clk         : in  STD_LOGIC;
                  i_rx          : in  STD_LOGIC;
                  o_byte        : out STD_LOGIC_VECTOR(7 downto 0);
                  o_done        : out STD_LOGIC                        -- Byte received flag
                );
    end component;
    
    constant wt      : time:= 5ns;              -- (FPGA clock period)/2
  
    signal clock     : std_logic:= '0';
    signal tx_ready  : std_logic:= '0';
    signal tx_enable : std_logic:= '0';
    signal rx_done   : std_logic:= '0';
  
    signal tx_o      : std_logic:= '1';
    signal tx_byte   : std_logic_vector(7 downto 0):= (others => '0');
    signal rx_byte   : std_logic_vector(7 downto 0):= (others => '0'); 
   
begin
 
UART_TX_INST : UartTx generic map ( g_CLK_PER_BIT => g_CLK_PER_BIT)
                      port map    (
                                    i_clk         => clock,
                                    i_enable      => tx_enable,
                                    i_byte        => tx_byte,
                                    o_tx          => tx_o,
                                    o_ready       => tx_ready
                                  );
 
UART_RX_INST : UartRx generic map ( g_CLK_PER_BIT => g_CLK_PER_BIT)
                      port map    (
                                    i_clk         => clock,
                                    i_rx          => tx_o,
                                    o_byte        => rx_byte,
                                    o_done        => rx_done
                                  );
CLK_GEN:        process
                begin
                
                    clock <= '1';
                    wait for wt;
                    clock <= '0';
                    wait for wt;    -- Continuously generates clock signal

                end process CLK_GEN;
                
SIM_GEN:        process
                begin
   
                    -- Takes approx. 1,041,667 ns for 1 byte to transfer
                    -- ((1/100000000) * (100000000 / 9600) * 10); 1 start bit + 8 bit data + 1 stop bit
                
                    tx_byte <= "11000011";
                    tx_enable <= '1';
                    wait for 2*wt;
                    tx_enable <='0';
                    wait for 208334*wt;
                    
                    tx_byte <= "00000001";
                    tx_enable <= '1';
                    wait for 2*wt;
                    tx_enable <='0';
                    wait for 208334*wt;
     
                end process;
end Blastn;