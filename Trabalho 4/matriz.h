#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st_celula{
    struct st_celula *prox;
    int lin, col;
    float val;
}tipo_celula;

typedef struct{
    int i, j;
    tipo_celula *prim_celula, *ult_celula;
}tipo_matriz_esparsa;
typedef tipo_matriz_esparsa matriz_esparsa;

matriz_esparsa *cria_matriz_esparsa(int i, int j);

int insere(matriz_esparsa *mat, int linha, int coluna, float valor);

float valorElemento(matriz_esparsa *mat, int linha, int coluna);

void leMatriz();

matriz_esparsa *somaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);

matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);
