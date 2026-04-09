#include <stdio.h>


int f(int n) {
    if (n == 0) return 0;
    return n + f(n-1);
}


/*A função realiza a soma dos n primeiros números naturais utilizando recursividade, 
com caso base f(0) = 0.*/