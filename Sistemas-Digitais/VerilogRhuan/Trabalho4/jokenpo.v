module logica_jokenpo (
    input [2:0] j1,
    input [2:0] j2,
    output reg [1:0] resultado

);
    
    wire valido1;
    wire valido2;
    
    assign valido1 = (j1 == 3'b001) || (j1 == 3'b010) || (j1 == 3'b100);
    assign valido2 = (j2 == 3'b001) || (j2 == 3'b010) || (j2 == 3'b100);
    
    always @(*) begin
        if (!valido1 || !valido2)
            resultado = 2'b00;

        else if(j1 == j2)
            resultado = 2'b00;   

        else if (
            (j1 == 3'b001 && j2 == 3'b100) ||
            (j1 == 3'b010 && j2 == 3'b001) || 
            (j1 == 3'b100 && j2 == 3'b010)   
        )
            resultado = 2'b01;

        else
            resultado = 2'b10;
    end


    
endmodule

module Display (
    input [9:0] SW,
    output reg [6:0] HEX0,
    output reg [6:0] HEX1,
    output reg [6:0] HEX2,
    output reg [6:0] HEX3
);

    wire [1:0] resultado;

    logica_jokenpo jogo (
        .j1(SW[2:0]),
        .j2(SW[9:7]),
        .resultado(resultado)
    );

    always @(*) begin

        case(resultado)

            2'b01: begin
                HEX3 = 7'b1110001;  
                HEX2 = 7'b1000000;          
                HEX1 = 7'b0010000;  
                HEX0 = 7'b1111001; 
            end


            2'b10: begin
                HEX3 = 7'b1110001; 
                HEX2 = 7'b1000000; 
                HEX1 = 7'b0010000; 
                HEX0 = 7'b0100100; 
            end

            default: begin
                HEX3 = 7'b0000110; 
                HEX2 = 7'b0000110; 
                HEX1 = 7'b0000110; 
                HEX0 = 7'b0000110; 
            end

        endcase

    end

endmodule