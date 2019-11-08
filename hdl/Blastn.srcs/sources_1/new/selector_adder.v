`timescale 1ns / 1ps

module SelectorAdder (
        x,
        score,
        sum,
    );
    input [1:0] x;
    input [1:0] score;
    output [2:0] sum;
    
    wire [3:0] result;
    
    assign result = {2'b00, x} + {2'b00, score};
    assign sum = ((result[3] == 1) || (result[2] == 1) || (score != 2'b10)) ? 2'b00 : result[1:0]; 
endmodule