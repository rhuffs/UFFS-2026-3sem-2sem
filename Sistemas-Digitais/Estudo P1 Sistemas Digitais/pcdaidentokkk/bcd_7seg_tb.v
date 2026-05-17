module bcd_7seg_tb;
reg [3:0] bcd;
wire [6:0] seg;

bcd_7seg utt(
    .bcd(bcd),
    .seg(seg)
);

always #10 bcd = bcd + 1;

initial begin
    $monitor("Tempo = %t, bcd = %b, seg = %b ",$time, bcd, seg);
    bcd = 4'b0000;
    #100;
    $finish;
end
endmodule