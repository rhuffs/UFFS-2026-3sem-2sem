module fsm_polinomio (
    input  wire        clk,
    input  wire        reset,
    input  wire        inicio,
    input  wire        z,
    input  wire        c,
    output reg         escreve,
    output reg  [2:0]  sel_ra,
    output reg  [2:0]  sel_rb,
    output reg  [2:0]  sel_rw,
    output reg  [2:0]  sel_op,
    output reg         mux_w_sel,
    output reg         overflow_led
);

    parameter S0_IDLE     = 4'd0,
              S1_CALC_D1  = 4'd1,
              S2_CALC_D2  = 4'd2,
              S3_RST_CNT  = 4'd3,
              S4_VERIFICA = 4'd4,
              S5_PROX_P   = 4'd5,
              S6_PROX_D1  = 4'd6,
              S7_INC_CNT  = 4'd7,
              S8_FIM      = 4'd8;

    reg [3:0] estado_atual, proximo_estado;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            estado_atual <= S0_IDLE;
            overflow_led <= 1'b0;
        end else begin
            estado_atual <= proximo_estado;
            if ((estado_atual == S5_PROX_P || estado_atual == S6_PROX_D1) && c) begin
                overflow_led <= 1'b1;
            end
        end
    end

    always @(*) begin
        escreve   = 1'b0;
        sel_ra    = 3'd0;
        sel_rb    = 3'd0;
        sel_rw    = 3'd0;
        sel_op    = 3'b000;
        mux_w_sel = 1'b0;
        proximo_estado = estado_atual;

        case (estado_atual)
            S0_IDLE: begin
                escreve = 1'b1;
                sel_rw  = 3'd6;
                mux_w_sel = 1'b1;
                if (inicio)
                    proximo_estado = S1_CALC_D1;
            end

            S1_CALC_D1: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd1;
                sel_rw  = 3'd3;
                sel_op  = 3'b011;
                proximo_estado = S2_CALC_D2;
            end

            S2_CALC_D2: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd0;
                sel_rw  = 3'd4;
                sel_op  = 3'b011;
                proximo_estado = S3_RST_CNT;
            end

            S3_RST_CNT: begin
                escreve = 1'b1;
                sel_ra  = 3'd0;
                sel_rb  = 3'd0;
                sel_rw  = 3'd5;
                sel_op  = 3'b111;
                proximo_estado = S4_VERIFICA;
            end

            S4_VERIFICA: begin
                escreve = 1'b0;
                sel_ra  = 3'd6;
                sel_rb  = 3'd5;
                sel_op  = 3'b110;
                sel_ra  = (z) ? 3'd2 : 3'd6; 
                if (z) proximo_estado = S8_FIM;
                else   proximo_estado = S5_PROX_P;
            end

            S5_PROX_P: begin
                escreve = 1'b1;
                sel_ra  = 3'd2;
                sel_rb  = 3'd3;
                sel_rw  = 3'd2;
                sel_op  = 3'b011;
                proximo_estado = S6_PROX_D1;
            end

            S6_PROX_D1: begin
                escreve = 1'b1;
                sel_ra  = 3'd3;
                sel_rb  = 3'd4;
                sel_rw  = 3'd3;
                sel_op  = 3'b011;
                proximo_estado = S7_INC_CNT;
            end

            S7_INC_CNT: begin
                escreve = 1'b1;
                sel_ra  = 3'd5;
                sel_rb  = 3'd7;
                sel_rw  = 3'd5;
                sel_op  = 3'b011;
                proximo_estado = S4_VERIFICA;
            end

            S8_FIM: begin
                escreve = 1'b0;
                sel_ra  = 3'd2;
                proximo_estado = S8_FIM;
            end
            
            default: proximo_estado = S0_IDLE;
        endcase
    end
endmodule