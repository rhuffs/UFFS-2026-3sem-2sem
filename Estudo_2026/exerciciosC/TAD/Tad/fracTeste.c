#include <stdio.h>
#include "fracao.h"

int main(){

    fracao a, b, c;
    a = setFrac(3,6);
    b = setFrac(15,50);
    c = setFrac(10,100);
    
     

    showFrac(a);
    showFrac(multiFrac(a, b));




}