// Nome: Rhuan Leandro Paiva && Henrique Schmitz Nilson
// link do youtube : https://youtube.com/shorts/Uorsnw_xdus?si=GAvxbkOYuRKjajb3

`timescale 1ns/1ps
module tbConta_portas;

    reg [9:0] SW_t;
    wire [3:0] led;

    Conta_portas uut(
        .SW(SW_t),
        .LEDG(led)
    );

    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tbConta_portas);

        SW_t = 10'b0000000000;
        #10;

        SW_t = 10'b0000000101;
        #10;

        SW_t = 10'b0000001000;
        #10;

        $stop;
    end

endmodule