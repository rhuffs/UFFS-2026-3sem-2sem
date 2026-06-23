module fsm_mult (
    input clk,
    input rst,
    input inicio,
    input [9:0] vb,   
    input z,          
    output reg escreve,
    output reg mux_w_sel,
    output reg [2:0] sel_op,
    output reg [2:0] sel_ra,
    output reg [2:0] sel_rb,
    output reg [2:0] sel_rw,
    output reg done
);

    typedef enum reg [2:0] {
        S0 = 0,
        S1 = 1,
        S2 = 2,
        S3 = 3,
        S4 = 4,
        S5 = 5
    } state_t;

    state_t state, next;

    wire lsb = vb[0];


    always @(posedge clk or posedge rst) begin
        if (rst)
            state <= S0;
        else
            state <= next;
    end


    always @(*) begin
        next = state;

        case (state)
            S0: if (inicio) next = S1;

            S1: next = S2;

            S2: next = (lsb) ? S3 : S4;

            S3: next = S4;

            S4: next = (z) ? S5 : S2;

            S5: next = S0;
        endcase
    end


    always @(*) begin
        escreve = 0;
        mux_w_sel = 0;
        sel_op = 3'b000;
        sel_rw = 0;
        sel_ra = 0;
        sel_rb = 0;
        done = 0;

        case (state)

            S1: begin
                escreve = 1;
                mux_w_sel = 1; 
                sel_rw = 2;  
            end

            S3: begin
                escreve = 1;
                sel_op = 3'b001;
                sel_rw = 2;      
            end

            S4: begin
                escreve = 1;
                sel_op = 3'b010;
            end

            S5: begin
                done = 1;
            end

        endcase
    end

endmodule