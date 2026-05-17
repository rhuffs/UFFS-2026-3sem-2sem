module Contador_tb;
reg clk;
reg reset;
wire [2:0] q;

contado uut(
    .clk(clk),
    .reset(reset),
    .q(q)
);

always #5 clk = ~clk;

initial
begin

    clk = 0;
    reset = 1;

    $monitor("tempo=%0t q=%b", $time, q);

    #10 reset = 0;

    #100 $finish;

end
endmodule