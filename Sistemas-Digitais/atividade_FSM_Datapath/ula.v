// Unidade Lógica Aritmética (ULA) - 10 bits
// SelOp | Operação
//  000  | A * B
//  001  | A << B
//  010  | A >> B
//  011  | A + B
//  100  | A AND B
//  101  | A / B
//  110  | A - B
//  111  | A XOR B
module ula (
    input  wire [9:0]  a,
    input  wire [9:0]  b,
    input  wire [2:0]  sel_op,
    output reg  [9:0]  s,     // Resultado
    output reg         z,     // Zero flag
    output reg         c      // Overflow/Underflow flag (Carry/Borrow)
);

    // Registradores intermediários de largura extra para detectar overflow
    reg [19:0] result_mul;
    reg [10:0] result_wide;   // 11 bits para capturar carry/borrow

    always @(*) begin
        c = 1'b0;
        z = 1'b0;

        case (sel_op)
            3'b000: begin // A * B (multiplicação — resultado truncado para 10 bits)
                result_mul = a * b;
                s = result_mul[9:0];
                c = |result_mul[19:10];  // Overflow se bits superiores != 0
            end

            3'b001: begin // A << B (shift lógico à esquerda)
                result_wide = {1'b0, a} << b;
                s = result_wide[9:0];
                c = result_wide[10];     // Bit deslocado para fora
            end

            3'b010: begin // A >> B (shift lógico à direita)
                s = a >> b;
                // Carry: último bit deslocado para fora (se b > 0)
                c = (b > 0) ? a[b-1] : 1'b0;
            end

            3'b011: begin // A + B (adição)
                result_wide = {1'b0, a} + {1'b0, b};
                s = result_wide[9:0];
                c = result_wide[10];     // Carry out
            end

            3'b100: begin // A AND B
                s = a & b;
                c = 1'b0;
            end

            3'b101: begin // A / B (divisão inteira)
                if (b == 10'd0) begin
                    s = 10'hXX;          // Divisão por zero — resultado indefinido
                    c = 1'b1;
                end else begin
                    s = a / b;
                    c = 1'b0;
                end
            end

            3'b110: begin // A - B (subtração)
                result_wide = {1'b0, a} - {1'b0, b};
                s = result_wide[9:0];
                c = result_wide[10];     // Borrow (underflow)
            end

            3'b111: begin // A XOR B
                s = a ^ b;
                c = 1'b0;
            end

            default: begin
                s = 10'd0;
                c = 1'b0;
            end
        endcase

        z = (s == 10'd0) ? 1'b1 : 1'b0;
    end

endmodule
