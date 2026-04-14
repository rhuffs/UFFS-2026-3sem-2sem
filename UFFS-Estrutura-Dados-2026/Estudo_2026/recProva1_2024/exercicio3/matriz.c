#include <stdio.h>

int main( ){
    int i, j;
    int A[2][2], B[2][2];
    A[0][0] = 3;
    A[0][1] = 2;
    A[1][0] = -4;
    A[1][1] = 6;
    for (i = 0; i < 2; i++){
        for (j = 0; j < 2; j++){
            B[j][i] = A[i][j];
        }
    }


    printf("Matriz B (transposta):\n");
    for (i = 0; i < 2; i++){
        for (j = 0; j < 2; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
}