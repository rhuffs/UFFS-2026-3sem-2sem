`timescale 1ps/1ps


//testbench registrador de 16 bits
module tb_shift_reg_16;

    reg clk;
    reg rst_n;
    reg [1:0] mode;
    reg [15:0] d_in;
    wire [15:0] q;

    //Módulo registrador
    shift_reg_16 uut (
        .clk(clk),
        // .clk - porta do pino
        // (clk)- o sinal que está indo a porta
        .rst_n(rst_n),
        .mode(mode),
        .d_in(d_in),
        .q(q)
    );

    always #5 clk = ~clk;
    //o bloco always cria um loop infinito que executa repetidamente durante toda a simulação
    //clk = ~clk -> inverte o valor do clock: clk 1 = ~clk 0; clk 0 = ~clk 1

    initial begin
        //isso cria a EPWave: ações sobre as subidas do intervalo de tempo dos clock
        
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

        //inicializando os 16 ciclos aleatórios
        repeat (16) begin
            @(negedge clk);//Funcionamento da descida do clock
            mode = $random % 4;//randomiza a seleção
            d_in = $random;//randomiza a entrada
            $display("T(intervalo de tempo) = %0t\n Modo = %b\n d_in = %h q=%h\n", $time, mode, d_in, q);
        end

        $finish;
    end 
endmodule