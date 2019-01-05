typedef struct no No;

int alt_no(No *no);

void Rotacao_LL(No** no);

void Rotacao_RR(No** no);

void Rotacao_LR(No** no);

void Rotacao_RL(No** no);

No* no_cria(int val, No* esq, No* dir);

int arv_insere_aux(No** no, int val, int *cresceu);

int arv_insere(No **no, int val);

No* encontra_maior(No** no);

int arv_remove(No** no, int val);

void arv_imprime(No* no, char * lado);

void converte();
