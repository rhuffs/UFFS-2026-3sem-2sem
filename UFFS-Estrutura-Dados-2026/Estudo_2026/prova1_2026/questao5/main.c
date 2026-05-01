#include <stdio.h>
#include "grimorio.h"

int main (){
    Grimorio *g = cria_grimorio();
    aprende_feitico(g,"bola de fogo",50);
    aprende_feitico(g,"nevasca",50);
    aprende_feitico(g,"meteoro",70);
    lista_feitico(g);
    
}
