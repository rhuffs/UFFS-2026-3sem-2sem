`timescale 1ns/1ps
module tbbcdde1at1;
  reg [9:0]SW_test;
  wire [3:0]led_test;

  bcdde1at1 utt(
    .SW(SW_test),
    .LEDG(led_test)
  );
    initial begin
        SW_test = 10'b0000000000; #10; 
        SW_test = 10'b0000000011; #10; 
        SW_test = 10'b1010101010; #10; 
        SW_test = 10'b1111111111; #10;
        $stop;
    end
endmodule