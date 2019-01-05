#include <stdio.h>
#include <stdlib.h>
#include "trem.h"

int main()
{
    trem* t = cria_pilha();
    printf("t->ultimo->carga: %d", t->ultimo->carga);
    menu(t);
    return 0;
}
