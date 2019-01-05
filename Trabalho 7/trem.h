struct pilha{
    struct elemento* ultimo;
    int numero;
};

struct elemento{
    int carga;
    struct elemento* prox;
};

typedef struct pilha trem;
typedef struct elemento vagao;

int insere_carga(trem* t, int carga);
int remove_carga(trem* t, int carga);
void mostra_vagoes(trem* t);
