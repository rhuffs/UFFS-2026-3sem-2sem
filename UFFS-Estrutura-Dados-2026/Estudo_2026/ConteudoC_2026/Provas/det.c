#include <stdio.h>

int calculaDeterminante();

int main(){
    int matriz[2][2], det, i, j;
    for (i = 0 ;  i < 2; i++){
        for (j = 0; j < 2; j++){
            scanf("%d",&matriz[i][j] );
        }
    }
    det = calculaDeterminante(matriz);
    printf("O determinante da Matriz é : %d \n", det);
}

int calculaDeterminante (int M[2][2]){
    int diaP = M[0][0] * M[1][1];
    int diaS = M[0][1] * M[1][0];
    return diaP - diaS;
}