#include <stdio.h>
#include <stdlib.h>

struct st_elemento{
    int valor;
    char naipe;
    int indice;
};

typedef struct{
    struct st_elemento carta;
    int visivel; // campo para definir se o elemento deve ficar visível ou não
    struct st_lista_circular *ant, *prox;
} st_lista_circular;

typedef struct{
    struct st_elemento carta;
    int visivel; // campo para definir se o elemento deve ficar visível ou não
    struct st_pilha *prox;
} st_pilha;

typedef struct{
    int n; // numero de elementos da lista
    st_lista_circular *prim, *ult;
} tipo_descritor_lista;

typedef struct{
    int n; // numero de elementos da pilha
    st_pilha *topo;
} tipo_descritor_pilha;
