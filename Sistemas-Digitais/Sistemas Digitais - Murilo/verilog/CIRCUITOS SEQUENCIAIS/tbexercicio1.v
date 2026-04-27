`timescale 1ps/1ps

module tb_shift_reg_16;
    reg clk;
    reg rst_n;
    reg [1:0] mode;
    reg [15:0] d_in;
    wire [15:0] q;

    shift_reg_16 uut (
        .clk(clk),
        .rst_n(rst_n),
        .mode(mode),
        .d_in(d_in),
        .q(q)
    );
    always #5 clk = ~clk;

    initial begin
        $dumpfile("dump.vcd"); 
        $dumpvars(0, tb_shift_reg_16);
        clk = 0;
        rst_n = 1;
        mode = 2'b00;
        d_in = 16'h0000;

        //reset assíncrono
        #2 rst_n = 0;
        #5 rst_n = 1;

        if (q === 16'h0000) $display("reset feito");
        else $display("ERRO. O reset não ocorreu conforme o planejado");


        //coloca um dado
        @(negedge clk);
        mode = 2'b01;
        d_in = 16'hABCD;
        @(negedge clk);
        if (q === d_in) $display("O dado introduzido (%h) ocorreu normalmente",q);
        else $display("ERRO DE DADO. Resultado: %h", q);

        //joga pra direita
        mode = 2'b10;
        mode = 2'b10;
        repeat (4) @(negedge clk);

        if (q === 16'h0ABC) $display("O deslocamento ocorreu normalmente. Valor (%h)",q);
        else $display("ERRO NO DESLOCAMENTO. Resultado: %h", q);

        //manter resultado
        mode = 2'b00;
        repeat (2) @(negedge clk);

        if (q === 16'h0ABC) $display("Valor mantido corretamente (%h)", q);
        else $display("ERRO. O valor mudou durante a ação. Valor atual: %h", q);

        mode = 2'b01; 
        d_in = 16'h8000;
        @(negedge clk);
        if (q === d_in) $display("Resultado (%h) deu certo", q);
        else $display("ERRO DE DADO, o valor, não entrou na operação");

        //deslocamento esquerda
        mode = 2'b11;
        repeat (8) @(negedge clk);
        if (q === 16'h0000) $display("Houve deslocamento de dado. Resultado: %h", q);
        else $display("ERRO. O delocamento falou. Dado recebido: %h", q);

        mode = 2'b01; d_in = 16'hFFFF;
        #3 rst_n = 0;
        #2;
        if (q === 16'h0000) $display("Reset efetuado");
        else $display("ERRO: Reset assíncrono falhou");

        $display(" Iniciando 16 ciclos aleatórios:");
        repeat (16) begin
            @(negedge clk);
            mode = $random % 4;
            d_in = $random;
            $display("T=%0t | Modo=%b | d_in=%h | q=%h", $time, mode, d_in, q);
        end

        $finish;
    end 
endmodule