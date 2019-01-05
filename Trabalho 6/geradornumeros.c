#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numeros[40];

void gera_numeros () {

    int i,j, v[40];

    for (i = 0; i < 40; i++) v[i] = 0;
    srand( (unsigned)time(NULL) );
    for (i = 0; i < 40; i++) {
       j = rand() % 40;
       while (v[j] == 1 ) j = ( j + 1 ) % 40;
       numeros[i] = j;
       v[j] = 1;
    }
    return;
}

int valor_carta (int i) {

    if  (i >= 0 && i <= 39)
        return numeros[i] % 10;
    else
        return -1;
}

char naipe_carta (int i) {

    char naipe[8] = { 'E','P','O','C','P','E','C','O' };

    if (i >= 0 && i <= 39)
        return naipe[numeros[i] / 5];
    else
        return ' ';
}
