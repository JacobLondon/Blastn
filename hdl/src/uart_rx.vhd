library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity UartRx is
    generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);               -- FPGA clock / baud rate
    Port    ( 
              i_clk         : in  STD_LOGIC;
              i_rx          : in  STD_LOGIC;
              o_byte        : out STD_LOGIC_VECTOR(7 downto 0);
              o_done        : out STD_LOGIC                               -- Byte received flag
            );
end UartRx;

architecture Blastn of UartRx is

    type state_machine is (s_idle, s_start_bit, s_receive_bits, s_clean_up);
    
    -- System Initialization
    signal state     : state_machine:= s_idle;
    signal temp_done : std_logic:= '0';
    signal temp_byte : std_logic_vector(8 downto 0):= (others => '0');      -- 9 bits to account for stop bit
    signal count     : natural range 0 to g_CLK_PER_BIT - 1:= 0;
    signal index     : natural range 0 to 8:= 0;

begin

STATE_CONTROL:  process(i_clk) 
                begin
                    if rising_edge(i_clk) then
                        case state is
                        
                            when s_idle =>
                                index     <= 0;
                                temp_done <= '0';
                                
                                if i_rx = '0' then
                                    state <= s_start_bit;
                                end if;
                            
                            when s_start_bit =>
                                if count < (g_CLK_PER_BIT - 1) / 2 then   -- Waiting for middle of bit
                                    count <= count + 1;
                                else
                                    count <= 0;
                                   
                                    if i_rx = '0' then
                                        state <= s_receive_bits;
                                    else
                                        state <= s_idle;
                                  end if;
                                end if; 
                                        
                            when s_receive_bits =>
                                if count < g_CLK_PER_BIT - 1 then
                                    count <= count + 1;
                                else
                                    count <= 0;
                                    temp_byte(index) <= i_rx;
                                   
                                    if index < 8 then
                                        index <= index + 1;
                                    else
                                        temp_done <= '1';                 -- Raising byte received flag
                                        state <= s_clean_up;
                                    end if;
                                end if;
                                   
                            when s_clean_up =>
                                state <= s_idle;
                            
                            when others =>
                                state <= s_idle;
                        end case;
                    end if;
                end process STATE_CONTROL;
                
                o_done <= temp_done;
                o_byte <= temp_byte(7 downto 0);
                
end Blastn;