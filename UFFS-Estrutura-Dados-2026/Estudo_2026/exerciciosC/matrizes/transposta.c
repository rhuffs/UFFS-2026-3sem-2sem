#include <stdio.h>

int main(){
    int matrizA[3][3];
    int matrizB[3][3];
    for (int i = 0 ; i < 3; i++){
        for (int j = 0; j < 3; j ++){
            scanf("%d", &matrizA[i][j]);
        }
    }

    for (int i = 0 ; i < 3; i++){
        for (int j = 0; j < 3; j ++){
            matrizB[j][i] = matrizA[i][j];
        }
    }

    for (int i = 0 ; i < 3; i++){
        for (int j = 0; j < 3; j ++){
            printf("%d ",matrizB[i][j]);
        }
    }


}