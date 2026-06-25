// ============================================================
//  Debounce — filtra bouncing de push-button
//  Gera um pulso de 1 ciclo (clk_sys) na borda de descida
//  do botão (KEY da DE10-Lite é ativo-baixo).
// ============================================================

module debounce (
    input  wire clk_sys,   // Clock do sistema (50 MHz)
    input  wire rst,
    input  wire btn_n,     // Botão ativo-baixo (KEY)
    output reg  pulso      // Pulso 1 ciclo na borda de descida
);
    // Contador de ~20 ms a 50 MHz → 1_000_000 ciclos
    localparam integer CONTAGEM = 1_000_000;
    localparam integer NBITS    = 20;  // ceil(log2(1_000_000)) = 20

    reg [NBITS-1:0] contador;
    reg [2:0]       sincronizador;  // 3 FFs para metaestabilidade + filtragem
    reg             btn_filtrado;
    reg             btn_prev;

    always @(posedge clk_sys or posedge rst) begin
        if (rst) begin
            sincronizador <= 3'b111;   // btn_n inativo (alto)
            contador      <= 0;
            btn_filtrado  <= 1'b1;
            btn_prev      <= 1'b1;
            pulso         <= 1'b0;
        end else begin
            // Sincroniza entrada assíncrona
            sincronizador <= {sincronizador[1:0], btn_n};

            pulso <= 1'b0;

            if (sincronizador[2] == btn_filtrado) begin
                // Sinal estável — zera contador
                contador <= 0;
            end else begin
                if (contador == CONTAGEM - 1) begin
                    // Passou tempo suficiente → aceita novo valor
                    btn_filtrado <= sincronizador[2];
                    contador     <= 0;

                    // Borda de descida = pressionamento (KEY ativo-baixo)
                    if (btn_filtrado == 1'b1 && sincronizador[2] == 1'b0)
                        pulso <= 1'b1;
                end else begin
                    contador <= contador + 1;
                end
            end
        end
    end

endmodule
