///sintese mudar de nível de sintese: lógica->física



//assing continuo
//não estamos instânciando portas, apenas estamos 
//incluindo instâncias como operadores bit a bit
//quando não há wire ou reg, o operador já declara como wire
module somador_completo{
    input a,
    input c,
    input cin,
    output s,
    output carry
}

    assing s = a ^ b ^ cin;//nunca poderá ser reg, pois, será um circuito combinacional

    assing carry = (a & b ) | (cin & (a ^ b));

endmodule
/
//intanciação de portas
//estrutural
module ms_est(
    input a,b,
    output s,c
);
    xor X1(s,a,b);//entrada é s e fica s = a xor b 
    and A1(c,a,b);
endmodule

//bloco aways
//comportamental
//blocos sequenciais ou combinacionais
module ms_beh(
    input a, b,
    output s, c
);
    //a cada vez que seu valor mudar, esse bloco será executável
    always @(*)begin
        s = a ^ b;
        c = a & b;
    end;
endmodule

module mux4x1_estrutural(
    input [3:0] i, [1:0] sel,//i = entrada de 4 bits; sel = linhas de seleção
    output y // saida
);

    //sinais internos para os inversores e portas AND
    wire s1n, s0n;
    wire a0, a1, a2, a3;

    //INVERSORES PARA AS LINHAS DE SELECAO (NOT)
    not n1 (s1n, sel[1]);
    not n2 (s0n, sel[0]);

    //portas AND de 3 entradas para selecinar os dados
    and go (a0, i[0], s1n, s0n); //00
    and g1 (a1, i[1], s1n, sel[0]); //01
    and g2 (a2, i[2], sel[1], s0n); //10
    and g3 (a3, i[3], sel[1], sel[0]); //11
    // porta OR para combinar os resultados
    or finaly_mux(y, a0, a1, a2, a3);
endmodule
