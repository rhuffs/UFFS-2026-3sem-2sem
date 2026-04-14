#include <stdio.h>

/*Matrizes*/

int main (){
    int matriz[3][3] = {
        {0,1,2},
        {10,11,12},
        {20,21,22},
    };


    int vetor[1][200];

 /*Exercicios*/
 //1
    int matrizdia[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };
    for (int i = 0; i < 4 ; i++){
        for(int j = 0; i < 4; i++ ){
            if (i == j) printf("%d\n",matrizdia[i][j]);
        }
    }
    return 0;

//2
