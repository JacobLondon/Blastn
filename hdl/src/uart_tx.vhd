library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity UartTx is
    generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);        -- Generic for timing between FPGA clock and baud rate
    Port    ( 
              i_clk         : in  STD_LOGIC;
              i_enable      : in  STD_LOGIC;
              i_byte        : in  STD_LOGIC_VECTOR(7 downto 0);    -- Byte to be transmitted 
              o_tx          : out STD_LOGIC;                       -- Individual serial bits transmission        
              o_ready       : out STD_LOGIC                        -- Active transmission flag
            );
end UartTx;

architecture Blastn of UartTx is

    type   state_machine is (s_idle, s_start_bit, s_transmit_bits, s_stop_bit, s_clean_up);
    
    -- System Initialization
    signal state      : state_machine:= s_idle;
    signal temp_ready : std_logic:= '0';
    signal temp_byte  : std_logic_vector(7 downto 0):= (others => '0');
    signal count      : natural range 0 to g_CLK_PER_BIT - 1:= 0;
    signal index      : natural range 0 to 7:= 0;

begin
    
STATE_CONTROL:  process(i_clk)
                begin
                    if rising_edge(i_clk) then
                        case state is
                        
                            when s_idle =>
                                o_tx       <= '1';        -- Line should be high until "i_enable" begins transmission
                                temp_ready <= '1';
                                count      <= 0;
                                index      <= 0;
                                
                                if (i_enable = '1') then
                                    temp_byte <= i_byte;
                                    state     <= s_start_bit;
                                end if;
                            
                            when s_start_bit =>
                                temp_ready <= '0';
                                o_tx       <= '0';                    -- Start bit = 0
                                
                                if (count < g_CLK_PER_BIT - 1) then   -- Wait until start bit ends
                                    count <= count + 1;
                                    state <= s_start_bit;
                                else
                                    count <= 0;
                                    state <= s_transmit_bits;
                                end if;

                            when s_transmit_bits =>
                                o_tx <= temp_byte(index);
                                
                                if (count < g_CLK_PER_BIT - 1) then
                                    count <= count + 1;
                                    state <= s_transmit_bits;
                                else
                                    count <= 0;
                                    
                                    if (index < 7) then
                                        index <= index + 1;
                                        state <= s_transmit_bits;
                                    else
                                        index <= 0;
                                        state <= s_stop_bit;
                                    end if;
                                end if;
                            
                            when s_stop_bit =>
                                o_tx <= '1';        -- Stop bit = 1
                                
                                if (count < g_CLK_PER_BIT - 1) then
                                    count <= count + 1;
                                    state <= s_stop_bit;
                                else
                                    count <= 0;
                                    state <= s_clean_up;
                                end if;
                                
                            when s_clean_up =>
                                state     <= s_idle;
                            
                            when others =>
                                state <= s_idle;            
                        end case;
                    end if;
                end process STATE_CONTROL;

                o_ready <= temp_ready;
    
end Blastn;