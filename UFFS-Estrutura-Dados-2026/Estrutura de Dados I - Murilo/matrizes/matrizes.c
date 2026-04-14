#include <stdio.h>

int main()
{
    /*int matriz[10]->linhas [10]->colunas*/
    /*Para percursar a matriz:
    for(int i = 0; i< LINHAS; i++){
        for(int j = 0; j<COLUNAS; j++){
            printf("(%d, %d): %d\n", i,j, m[i][j]);
        }
    }
    */


    int mt[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) if(i == j) printf("%d\n", mt[i][j]);



    return 0;
}