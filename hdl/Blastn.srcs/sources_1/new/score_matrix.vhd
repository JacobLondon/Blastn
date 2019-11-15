library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ScoreMatrix is
    Generic (
        g_SIZE     : POSITIVE := 1000;
        g_BITS     : POSITIVE := 32;
        g_MATCH    : INTEGER  := 2;
        g_MISMATCH : INTEGER  := -1;
        g_GAP      : INTEGER  := -1
    );
    Port (
        i_length    : in  UNSIGNED(g_BITS - 1 downto 0);         -- length of the query or the subject
        i_gap_start : in  UNSIGNED(g_BITS - 1 downto 0);         -- gap start index in the query
        i_gap_count : in  UNSIGNED(g_BITS - 1 downto 0);         -- number of gaps in the query
        i_query     : in  STD_LOGIC_VECTOR(g_SIZE - 1 downto 0); -- the query
        i_subject   : in  STD_LOGIC_VECTOR(g_SIZE - 1 downto 0); -- the subject
        o_score     : out UNSIGNED(g_BITS - 1 downto 0)          -- Smith-Waterman max score
    );
end ScoreMatrix;

architecture BlastnRTL of ScoreMatrix is

    component Cell is
        Port (
            s        : in  STD_LOGIC_VECTOR(1 downto 0);
            q        : in  STD_LOGIC_VECTOR(2 downto 0);
            match    : in  STD_LOGIC_VECTOR(1 downto 0);
            mismatch : in  STD_LOGIC_VECTOR(1 downto 0);
            gap      : in  STD_LOGIC_VECTOR(1 downto 0);
            diag     : in  STD_LOGIC_VECTOR(1 downto 0);
            up       : in  STD_LOGIC_VECTOR(1 downto 0);
            left     : in  STD_LOGIC_VECTOR(1 downto 0);
            score    : out STD_LOGIC_VECTOR(1 downto 0)
        );
    end component;

    type MATRIX is array(0 to g_SIZE - 1) of STD_LOGIC_VECTOR(g_SIZE - 1 downto 0);
    
    signal m_score_matrix : MATRIX := (others => (others => '0'));

begin

    ROW: for i in 1 to g_SIZE - 1 generate
        COLUMN: for j in 1 to g_SIZE / 2 - 1 generate
            current_cell: Cell
                Port map (
                    s => i_subject(i),
                    q => i_query(j*2),
                    match => std_logic_vector(g_MATCH),
                    mismatch => std_logic_vector(g_MISMATCH),
                    gap => std_logic_vector(g_GAP),
                    diag => "11",
                    up => "11",
                    left => "11",
                    score => open
                );
        end generate;
    end generate;

end BlastnRTL;
