`timescale 1ns / 1ps

module AlignScore(
        q,
        s,
        diag,
        match,
        mismatch,
        gap,
        score
    );
    
    input q;
    input s;
    input [1:0] match;
    input [1:0] mismatch;
    input [1:0] gap;
    input [1:0] diag;
    output score;
    
    wire [2:0] CompResult;
    wire [1:0] SelResult;
    
    Comparator mod_cmp(
        .q(q),
        .s(s),
        .result(CompResult)      // output 100 match, 010 mismatch, 001 gap
   );
   Selector mod_sel(
        .i_bus(CompResult),
        .match(match),
        .mismatch(mismatch),
        .gap(gap),
        .result(SelResult)
    );
    SelectorAdder mod_seladd(
        .x(diag),
        .score(SelResult),
        .sum(score)
    );
endmodule