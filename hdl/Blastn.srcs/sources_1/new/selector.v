`timescale 1ns / 1ps

module Selector(
        i_bus,
        match,
        mismatch,
        gap,
        result
    );
    
    input [2:0] i_bus;
    input [1:0] match;
    input [1:0] mismatch;
    input [1:0] gap;
    output [1:0] result;
    
    assign result = (i_bus[2] == 1) ? match : ((i_bus[1] == 1) ? mismatch : gap);
    
endmodule