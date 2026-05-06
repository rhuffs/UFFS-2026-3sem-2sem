`timescale 1ns/1ps

module tb_bcd_portas;

reg [9:0] SW;
wire [6:0] HEX0, HEX1, HEX2, HEX3;

bcd_portas uut (
    .SW(SW),
    .HEX0(HEX0),
    .HEX1(HEX1),
    .HEX2(HEX2),
    .HEX3(HEX3)
);

integer i;

initial begin
    $dumpfile("wave.vcd");
    $dumpvars(0, tb_bcd_portas);

    for (i = 0; i < 1024; i = i + 1) begin
        SW = i;
        #10;
    end

    $stop;
end

endmodule