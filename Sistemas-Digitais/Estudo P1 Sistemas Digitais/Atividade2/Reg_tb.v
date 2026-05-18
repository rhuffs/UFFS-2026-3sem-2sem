module Reg_tb;
reg clk;
reg rst_n;
reg [1:0] mode;
reg [15:0] d_in;
wire [15:0] q;

shift_reg_16 utt(
    .clk(clk),
    .rst_n(rst_n),
    .mode(mode),
    .d_in(d_in),
    .q(q)
);



initial begin
    $monitor("Tempo:%t , clk : %b, reset: %b q : %h",$time, clk, rst_n, q);
    d_in = 16'hABCD; #10;
    mode = 2'b01; #10;
    clk = 1'b1; #10;
    rst_n = 2'b1; #10;
    rst_n = 2'b0;
end

endmodule