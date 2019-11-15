library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Collector is
    generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600;                  -- FPGA clock / baud rate
              g_SIZE        : positive:= 3;
              g_BITS        : positive:= 32
            );
    Port    ( 
              i_clk         : in  STD_LOGIC;
              i_rx          : in  STD_LOGIC;
              o_query       : out STD_LOGIC_VECTOR((g_SIZE * 3) - 1 downto 0);
              o_subject     : out STD_LOGIC_VECTOR((g_SIZE * 2) - 1 downto 0)
           );
end Collector;

architecture Blastn of Collector is

component UartRx
    generic ( g_CLK_PER_BIT : positive:= 100000000 / 9600);
    Port    ( 
              i_clk         : in  STD_LOGIC;
              i_rx          : in  STD_LOGIC;
              o_done        : out STD_LOGIC;                                -- Byte received flag
              o_byte        : out STD_LOGIC_VECTOR(7 downto 0)
            );
end component;

    type state_machine is (s_size, s_gap_start, s_gap_count, s_query, s_subject);
    signal state         : state_machine:= s_size;
    
    signal index         : natural:= 0;
    signal int_size      : natural:= 0;
    signal int_gap_start : natural:= 0;
    signal int_gap_count : natural:= 0;
    
    signal done          : std_logic:= '0';
    signal temp          : std_logic_vector(7 downto 0):=  (others => '0');         -- Byte received by uart
    
    signal size          : std_logic_vector(g_BITS - 1 downto 0):= (others => '0');
    signal gap_start     : std_logic_vector(g_BITS - 1 downto 0):= (others => '0');
    signal gap_count     : std_logic_vector(g_BITS - 1 downto 0):= (others => '0');
    
    signal query         : std_logic_vector((g_SIZE * 3) - 1 downto 0):= (others => '0');
    signal subject       : std_logic_vector((g_SIZE * 2) - 1 downto 0):= (others => '0');

begin

BYTE_RX: UartRx generic map ( g_CLK_PER_BIT => g_CLK_PER_BIT)
                Port    map ( 
                              i_clk         => i_clk,
                              i_rx          => i_rx,
                              o_byte        => temp,
                              o_done        => done
                            );

RX_OUT:  process (i_clk)
         begin          
            if rising_edge(i_clk) then
                case state is
                    
                    when s_size =>
                        if (done = '1') then
                            if (index <= 24) then
                                size(index + 7 downto index) <= temp;
                                index    <= index + 8;
                            else
                                index    <= 0;
                                int_size <= to_integer(UNSIGNED(size));
                                state    <= s_gap_start;
                            end if;
                        end if;
                    
                    when s_gap_start =>
                        if (done = '1') then
                            if (index <= 24) then
                                gap_start(index + 7 downto index) <= temp;
                                index         <= index + 8;
                            else
                                index         <= 0;
                                int_gap_start <= to_integer(UNSIGNED(gap_start));
                                state         <= s_gap_count;
                            end if;
                        end if;
                    
                    when s_gap_count =>
                        if (done = '1') then
                            if (index <= 24) then
                                gap_count(index + 7 downto index) <= temp;
                                index         <= index + 8;
                            else
                                index         <= 0;
                                int_gap_count <= to_integer(UNSIGNED(gap_count));
                                state         <= s_query;
                            end if;
                        end if;
                    
                    when s_query =>
                        if (done = '1') then
                            if (index <= (int_size * 2) - 8) then
                                query(index + 7 downto index) <= temp;
                                index <= index + 8;
                            else
                                index <= 0;
                                state <= s_subject;
                            end if;
                        end if;
                    
                    when s_subject =>
                        if (done = '1') then
                            if (index <= (int_size * 2) - 8) then
                                subject(index + 7 downto index) <= temp;
                                index <= index + 8;
                            else
                                index <= 0;
                                state <= s_size;
                            end if;
                        end if;
                        
                    when others => state <= s_size;
                end case;
            end if;
         end process RX_OUT;
         
         o_query     <= query;
         o_subject   <= subject;
         
end Blastn;