// =============================================================
//  Debounce — filtra bouncing do push-button
//  Gera pulso de 1 ciclo (clk_sys) na borda de descida do KEY
//  KEY da DE1 é ativo-baixo (pressionado = 0)
// =============================================================

module debounce (
    input  wire clk_sys,  // 50 MHz
    input  wire rst,
    input  wire btn_n,    // KEY ativo-baixo
    output reg  pulso     // pulso de 1 ciclo quando botão é pressionado
);
    // 20 ms a 50 MHz = 1.000.000 ciclos
    localparam LIMITE = 20'd1_000_000;

    reg [19:0] contador;
    reg [1:0]  sync;       // 2 FFs de sincronização
    reg        btn_limpo;
    reg        btn_ant;

    always @(posedge clk_sys or posedge rst) begin
        if (rst) begin
            sync      <= 2'b11;
            contador  <= 20'd0;
            btn_limpo <= 1'b1;
            btn_ant   <= 1'b1;
            pulso     <= 1'b0;
        end else begin
            sync <= {sync[0], btn_n};
            pulso <= 1'b0;

            if (sync[1] == btn_limpo) begin
                contador <= 20'd0;
            end else begin
                if (contador == LIMITE - 1) begin
                    btn_ant   <= btn_limpo;
                    btn_limpo <= sync[1];
                    contador  <= 20'd0;
                    // borda de descida = pressionamento
                    if (btn_limpo == 1'b1 && sync[1] == 1'b0)
                        pulso <= 1'b1;
                end else begin
                    contador <= contador + 1'b1;
                end
            end
        end
    end
endmodule
