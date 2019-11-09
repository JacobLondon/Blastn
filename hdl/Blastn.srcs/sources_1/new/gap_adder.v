`timescale 1ns / 1ps

module GapAdder(
        x,      // input from left or up
        gap,    // input global constant gap score
        sum,    // output sum of x and gap
    );
    input  [1:0] x;
    input  [1:0] gap;
    output [2:0] sum;
    
    /**
     * Gap is always -1 == 2'b11
     * 
     * Truth table:
     * 
     * x1 x0 g1 g0 | s1 s0
     * 0  0  1  1  | 0  0
     * 0  1  1  1  | 0  0
     * 1  0  1  1  | 0  1
     * 1  1  1  1  | 1  0
     * 
     * Result is zero if x[1] == 0
     */
    
    assign sum = x[1] == 0 ? 2'b00 : (x[0] == 0 ? 2'b01 : 2'b10);
    
endmodule