`timescale 1ns / 1ps

module Comparator(
    q,
    s,
    result
    );
    input [2:0] q;
    input [1:0] s;
    output [2:0] result;
    
    assign result = ((q[0] == s[0]) && (q[1] == s[1]) && (q[2] == 0))
                  ? 3'b100 : (((q[0] != s[0]) || (q[1] != s[2]) || (q[2] != 0))
                  ? 3'b010 : 3'b001);
    
endmodule