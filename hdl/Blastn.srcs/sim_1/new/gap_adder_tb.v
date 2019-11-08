 `timescale 1ns / 1ps
 
 module GapAdderTb();
    reg [1:0] x;
    reg [1:0] gap;
    wire[2:0] sum;
    
    GapAdder uut (
        .x(x),
        .gap(gap),
        .sum(sum)
    );
    
    initial begin
        x = 0; gap = -1;
        #100;
        x = 1; gap = -1;
        #100;
        x = 2; gap = -1;
        #100;
        x = 3; gap = -1;
        #100;
        $finish;
    end
endmodule 