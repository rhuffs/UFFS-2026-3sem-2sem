module gerador_pseudonimo (
    input clk,
    input rst,
    input enable,
    output [1:0] simbolo_randomico
);
    reg [3:0] LFSR;
    wire msb;
    assign msb = LFSR[3] ^ LFSR[2];

    always @(posedge clk or posedge rst) begin
        if(rst == 1'b1) LFSR <= 4'b0001;
        if(enable == 1'b1) LFSR <= {LFSR, msb};
    end
    assign simbolo_randomico = LFSR[1:0];
endmodule

module Memoria_sequencial (
    input clk,  
    input write_enable,
    input [3:0]write_addres,
    input [1:0]write_data,
    input [3:0]read_addres,
    output [1:0]read_data
);
    reg [1:0] memoria [15:0];
    always @(posedge clk) begin
        if(write_enable == 1'b1) memoria[write_addres] <= write_data;
    end
    assign read_data = memorai[write_addres];
endmodule

module Contador_exibicao (
    input clk,
    input rst,
    input clr,
    input increment,
    output reg [3:0] S
);
    always @(posedge clk or posedge rst) begin
        if(rst == 1'b1 || clk == 1'b1) S <= 4'b0000;
        if(increment == 1'b1) S <= S + 1'b1;
    end
endmodule



module Contador_entrada (
    input clk,
    input rst,
    input increment,
    output [3:0] counter
);
    always @(posedge clk or posedge rst) begin
        if(rst == 1'b1) counter <= 4'b0000;
        if(increment == 1'b1) counter <= counter + 1;        
    end
endmodule

module Registrador_nivel (
    input clk,
    input rst,
    input increment,
    output [3:0] Nivel
);
    always @(posedge clk or posedge rst) begin
        if(rst == 1'b1) Nivel <= 4'b0000;
        if(increment == 1'b1) Nivel <= Nivel + 1;        
    end
endmodule

module Comparar (
    input simbolo_esperando,
    input simbolo_jogado,
    output resultado_comparacao
);
    assign resultado_comparacao = (simbolo_esperando == simbolo_jogado);
endmodule

module temporizador(

    input clk,
    input rst,

    input ONLED,
    input INTERVALO,
    input OFFLED,

    output reg ENDLED,
    output reg ENDINTERVALO,
    output reg ENDOFFLED

);

    reg [31:0] contador;

    localparam TEMPO_LED = 25_000_000;      
    localparam TEMPO_GAP = 10_000_000;      
    localparam TEMPO_MAX = 3_000_000_000;   
    always @(posedge clk or posedge rst) begin

        if(rst) begin
            contador <= 0;
            ENDLED <= 0;
            ENDINTERVALO <= 0;
            ENDOFFLED <= 0;
        end

        else begin
            ENDLED <= 0;
            ENDINTERVALO <= 0;
            if(ONLED == 1'b1) begin
                if(contador >= TEMPO_LED) begin
                    ENDLED <= 1;
                    contador <= 0;
                end
                else
                    contador <= contador + 1;
            end if(INTERVALO == 1'b1) begin
                if(contador >= TEMPO_GAP) begin
                    ENDINTERVALO <= 1;
                    contador <= 0;
                end
                else
                    contador <= contador + 1;
            end if(OFFLED == 1'b1) begin
                if(contador >= TEMPO_MAX) begin
                    ENDOFFLED <= 1;
                end
                else
                    contador <= contador + 1;
            end
            else begin
                contador <= 0;
                ENDOFFLED <= 0;
            end
        end
    end
endmodule

module moduleName (
    ports
);
    
endmodule