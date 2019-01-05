#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct no{
    int val;
    int bal;
    struct no *esq, *dir;
} No;

int alt_no(No *no){
    if (no == NULL)
        return 0;
    int alt_esq = alt_no(no->esq);
    int alt_dir = alt_no(no->dir);
    return alt_esq > alt_dir ? alt_esq + 1 : alt_dir + 1;
}

void Rotacao_LL(No** no){
    No* n = *no;
    No* e = n->esq;
    n->esq = e->dir;
    e->dir = n;
    e->bal = 0;
    n->bal = 0;
    *no = e;
}

void Rotacao_RR(No** no){
    No* n = *no;
    No* d = n->dir;
    n->dir = d->esq;
    d->esq = n;
    n->bal = 0;
    d->bal = 0;
    *no = d;
}

void Rotacao_LR(No** no){
    No *n = *no;
    No *e = n->esq;
    No *d = e->dir;
    n->esq = d->dir;
    e->dir = d->esq;
    d->esq = e;
    d->dir = n;

    switch(d->bal){
        case -1:
            e->bal = 0;
            n->bal = 1;
        break;

        case 0:
            e->bal = 0;
            n->bal = 0;
        break;

        case +1:
            e->bal = -1;
            n->bal = 0;
        break;
    }
    d->bal = 0;
    *no = d;
}

void Rotacao_RL(No** no){
    No *n = *no;
    No *d = n->dir;
    No *e = d->esq;
    d->esq = e->dir;
    n->dir = e->esq;
    e->esq = n;
    e->dir = d;

    switch(e->bal) {
        case -1:
            n->bal = 0;
            d->bal = 1;
        break;

        case 0:
            n->bal = 0;
            d->bal = 0;
        break;

        case +1:
            n->bal = -1;
            d->bal = 0;
        break;
    }
    e->bal = 0;
    *no = e;
}

No* no_cria(int val, No* esq, No* dir){

    No* n = (No*) malloc (sizeof(No));
    n->val = val;
    n->bal = alt_no(dir) - alt_no(esq);
    n->esq = esq;
    n->dir = dir;
    return n;
}

int arv_insere_aux(No** no, int val, int *cresceu){

    if (*no == NULL){
        *no = no_cria(val, NULL, NULL);
        *cresceu = 1;
        return 1;
    }

    if (val == (*no)->val)
        return 0;

    if (val < (*no)->val){
        if (arv_insere_aux(&(*no)->esq, val, cresceu)){
            if (*cresceu){
                switch ((*no)->bal){
                    case -1:
                        if ((*no)->esq->bal == -1)
                            Rotacao_LL(no);
                        else
                            Rotacao_LR(no);
                            *cresceu = 0;
                    break;

                    case 0:
                        (*no)->bal = -1;
                        *cresceu = 1;
                    break;

                    case +1:
                        (*no)->bal = 0;
                        *cresceu = 0;
                    break;
                }
            }
            return 1;
        }
    else
      return 0;
  }

  if (arv_insere_aux(&(*no)->dir, val, cresceu)){
        if (*cresceu){
            switch ((*no)->bal){
                case -1:
                    (*no)->bal = 0;
                    *cresceu = 0;
                break;

                case 0:
                    (*no)->bal = +1;
                    *cresceu = 1;
                break;

                case +1:
                    if ((*no)->dir->bal == +1)
                        Rotacao_RR(no);
                    else
                        Rotacao_RL(no);
                    *cresceu = 0;
                break;
            }
        }
      return 1;
    }
    else
      return 0;
}

int arv_insere(No **no, int val){
  	int cresceu;
  	return arv_insere_aux(no, val, &cresceu);
}

No* encontra_maior(No** no){
    No *aux;
    aux = *no;
    if (aux->dir==NULL){
        *no=(*no)->esq;
        return aux;
    }
    else
        return encontra_maior(&((*no)->dir));
}

int arv_remove(No** no, int val){
    No *aux;

    if (*no == NULL)
        return 0;

    if ((*no)->val == val){
        aux=*no;

        if ((*no)->esq==NULL)
            *no=(*no)->dir;

        if ((*no)->dir==NULL)
            *no=(*no)->esq;
        else{
            aux = encontra_maior(&((*no)->esq));
            (*no)->val=aux->val;
        }
        free(aux);
        return 1;
    }
    else{
        if (val<(*no)->val)
            return (arv_remove(&((*no)->esq),val));
        else
            return (arv_remove(&((*no)->dir),val));
    }
}

void arv_imprime(No* no, char * lado){

   	static int tab = 0;

   	if (no==NULL) return;
	
   	int x;
   	for(x=0;x<tab;x++)
 	   printf("   ");
   	printf("%d (%s)\n", no->val, lado);

   	tab+=1;
   	arv_imprime(no->esq, "ESQ");
   	arv_imprime(no->dir, "DIR");
   	tab-=1;
}

void converte(){
    int i = 0, j = 0, cont = 0, contLinha = 0, opc;
    char s[200], linha[50], op[5], num[5], aux;
    FILE *arq;
    No *no;

    arq = fopen("dados.txt", "r");

    while((aux = fgetc(arq)) != EOF){
        *(s+i) = aux;
        if(aux == '\n'){
            contLinha++;
        }
        i++;
    }
    *(s+i) = '\0';

    printf("%s", s);

    i = 0;

    while(cont < contLinha){
        while(*(s+i) != '\n'){
            if(*(s+i) == ','){
                *(linha+j) = ' ';
            }
            else{
                *(linha+j) = *(s+i);
            }
                i++;
                j++;
        }
        i++;
        *(linha+j) = '\0';
        sscanf(linha, "%c %s", op, num);
        if(cont == 0){
            no = no_cria(atoi(num), NULL, NULL);
        }
        else{
            if(op[0] == '+')
                arv_insere(&no, atoi(num));
            else if(op[0] == '-')
                arv_remove(&no, atoi(num));
            else
                printf("Opcao invalida");
        }
        j = 0;
        cont++;
    }

    while(*(s+i) != '\0'){
            if(*(s+i) == ','){
                *(linha+j) = ' ';
            }
            else{
                *(linha+j) = *(s+i);
            }
            i++;
            j++;
    }
    *(linha+j) = '\0';

    sscanf(linha, "%s %s", op, num);
    if(op[0] == '+')
        arv_insere(&no, atoi(num));
    else if(op[0] == '-')
        arv_remove(&no, atoi(num));
    else
        printf("Opcao invalida\n");

    printf("\n\n\n");
    arv_imprime(no, "raiz");
    printf("\n\n\n");

    while(opc != 0){
        printf("Insira 1 para adicionar/remover, 2 para mostrar a arvore ou 0 para sair:\n");
        fflush(stdin);
        scanf("%d", &opc);

        switch(opc){
            case 1:
                printf("\nInsira operacao: ");
                fflush(stdin);
                gets(linha);
                linha[1] = ' ';
                sscanf(linha, "%s %s", op, num);
                if(op[0] == '+')
                    arv_insere(&no, atoi(num));
                else if(op[0] == '-')
                    arv_remove(&no, atoi(num));
                else
                    printf("\nOpcao invalida!\n");
            break;

            case 2:
                arv_imprime(no, "RAIZ");
                printf("\n\n");
            break;

            case 0:
                printf("Saindo...\n");
            break;

            default:
                printf("Opcao invalida!\n");
            break;
        }
    }
}
