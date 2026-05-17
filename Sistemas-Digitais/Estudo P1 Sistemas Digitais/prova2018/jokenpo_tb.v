`timescale 1ps/1ps
module jokenpo_tb;
    reg [1:0] j1;
    reg [1:0] j2;
    wire j1_win;
    wire j2_win;
    wire tie;

    jokenpo utt(
        .j1(j1),
        .j2(j2),
        .j1_win(j1_win),
        .j2_win(j2_win),
        .tie(tie)
    );

    initial begin
        $monitor("Tempo=%0dns | j1=%b j2=%b | j1_win=%b tie=%b j2_win=%b", $time, j1, j2, j1_win, tie, j2_win);
        j1 = 2'b00; j2 = 2'b00;
        #10;
        j1 = 2'b01; j2= 2'b01;
        #10;
        j1 = 2'b10; j2 = 2'b11; 
        #10;
        
        j1 = 2'b11; j2 = 2'b01; 
        #10;
        
        j1 = 2'b10; j2 = 2'b01; 
        #10;
        
        j1 = 2'b01; j2 = 2'b11; 
        #10;

        $finish;

    end 
endmodule