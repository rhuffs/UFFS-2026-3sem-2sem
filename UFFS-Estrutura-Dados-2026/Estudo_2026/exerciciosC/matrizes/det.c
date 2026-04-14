#include <stdio.h>

int main(){
    int matriz[2][2];
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    int diaP = matriz[0][0] * matriz[1][1];
    int diaS =  matriz[0][1] * matriz[1][0];
    int det =  diaP - diaS;
    printf("%d", det);
}