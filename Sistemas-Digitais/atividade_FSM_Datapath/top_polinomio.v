module top_polinomio (
    input  wire        CLOCK_50,
    input  wire [3:0]  KEY,
    input  wire [9:0]  SW,
    output wire [9:0]  LEDR,
    output wire [6:0]  HEX0,
    output wire [6:0]  HEX1,
    output wire [6:0]  HEX2,
    output wire [6:0]  HEX3
);

    wire       escreve;
    wire [2:0] sel_ra, sel_rb, sel_rw, sel_op;
    wire       mux_w_sel;
    wire [9:0] va_out, vb_out, s_out;
    wire       ula_z, ula_c;

    wire clk_fsm   = ~KEY[0]; 
    wire rst_fsm   = ~KEY[3];
    wire start_fsm = ~KEY[1];

    fsm_polinomio fsm_inst (
        .clk          (clk_fsm),
        .reset        (rst_fsm),
        .inicio       (start_fsm),
        .z            (ula_z),
        .c            (ula_c),
        .escreve      (escreve),
        .sel_ra       (sel_ra),
        .sel_rb       (sel_rb),
        .sel_rw       (sel_rw),
        .sel_op       (sel_op),
        .mux_w_sel    (mux_w_sel),
        .overflow_led (LEDR[0])
    );

    datapath dp_inst (
        .clk       (clk_fsm),
        .escreve   (escreve),
        .sel_ra    (sel_ra),
        .sel_rb    (sel_rb),
        .sel_rw    (sel_rw),
        .sel_op    (sel_op),
        .mux_w_sel (mux_w_sel),
        .ext_w     (SW),
        .va        (va_out),
        .vb        (vb_out),
        .s         (s_out),
        .z         (ula_z),
        .c         (ula_c)
    );

    assign LEDR[9:1] = 9'b000000000;

    wire [3:0] digito_milhar  = va_out / 1000;
    wire [3:0] digito_centena = (va_out % 1000) / 100;
    wire [3:0] digito_dezena  = (va_out % 100) / 10;
    wire [3:0] digito_unidade = va_out % 10;

    function [6:0] bcd_to_7seg;
        input [3:0] bcd;
        case (bcd)
            4'd0: bcd_to_7seg = 7'b1000000;
            4'd1: bcd_to_7seg = 7'b1111001;
            4'd2: bcd_to_7seg = 7'b0100100;
            4'd3: bcd_to_7seg = 7'b0110000;
            4'd4: bcd_to_7seg = 7'b0011001;
            4'd5: bcd_to_7seg = 7'b0010010;
            4'd6: bcd_to_7seg = 7'b0000010;
            4'd7: bcd_to_7seg = 7'b1111000;
            4'd8: bcd_to_7seg = 7'b0000000;
            4'd9: bcd_to_7seg = 7'b0010000;
            default: bcd_to_7seg = 7'b1111111;
        endcase
    endfunction

    assign HEX0 = bcd_to_7seg(digito_unidade);
    assign HEX1 = bcd_to_7seg(digito_dezena);
    assign HEX2 = bcd_to_7seg(digito_centena);
    assign HEX3 = bcd_to_7seg(digito_milhar);

endmodule