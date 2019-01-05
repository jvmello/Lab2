#include <stdio.h>
#include <stdlib.h>
#include "trem.h"

void menu(trem* t){
    int i, carga, aux;
    char* op;

    if(t==NULL){
       printf("Pilha vazia!\n");
        exit(1);
    }

    while(i != 0){
        printf("Insira opcao:\n\t(1)...Inserir ou remover carga\n\t(2)...Mostrar numero de vagoes e sua carga\n\t(3)...Limpar tela\n\n\t(0)...Sair\n\n");
        fflush(stdin);
        gets(op);
        i = atoi(op);

        switch(i){
            case 1:
                printf("Insira a quantidade de carga a ser inserida/removida(em toneladas): ");
                scanf("%d", &carga);
                if(carga > 0){
                    aux = insere_carga(t, carga) + 1;
                    if(aux != 0){
                        printf("Dados inseridos com sucesso!\n");
                        t->numero += aux;
                    }
                    else{
                        printf("Dados nao foram inseridos com sucesso.\n");
                    }
                }
                else if(carga < 0){
                    aux = remove_carga(t, carga) + 1;
                    if(aux != 0){
                        printf("Dados removidos com sucesso!\n");
                        t->numero -= aux;
                    }
                    else{
                        printf("Dados nao foram removidos com sucesso.\n");
                    }
                }
                else{
                    printf("Nada inserido nem removido");
                }
            break;

            case 2:
                mostra_vagoes(t);
            break;

            case 3:
                system("cls");
            break;

            case 0:
                exit(1);
            break;

            default:
                printf("Opcao Invalida! Tente novamente: \n");
            break;
        }
    }
}

trem* cria_pilha(){
    trem* t = (trem*) malloc(sizeof(trem));
    vagao* v = (vagao*) malloc(sizeof(vagao));
    if (t == NULL) exit(1);
    v->carga = 0;
    t->numero = 0;
    t->ultimo = v;
    t->ultimo->prox = NULL;
    return t;
}

int insere_carga(trem* t, int carga){
    static i;
    int aux;

    if(t==NULL){
        printf("Pilha vazia!\n");
        return 0;
    }

    if(carga < 0){
        return;
    }

    vagao* vag = (vagao*) malloc(sizeof(vagao));
    if(vag==NULL) exit(1);
    vag->carga = 0;
    vag->prox = t->ultimo;
    t->ultimo = vag;

    if(carga > 0 && carga <= 40 && t->ultimo->carga + carga <= 40){
        t->ultimo->carga += carga;
        aux = i;
        i = 0;
        return aux;
    }
    else{
        t->ultimo->carga = 40;
        insere_carga(t, carga - 40);
    }
    i++;
}

int remove_carga(trem* t, int carga){
    static i;
    int aux, c;
    vagao* v;

    carga *= -1;

    if(t==NULL){
        printf("Pilha vazia!\n");
        return 0;
    }

    if(carga < 0 || t->ultimo->carga == 0){
        return 0;
    }

    if((carga >= 0 && carga <= 40) && t->ultimo >= 0){
        t->ultimo->carga -= carga;
        aux = i;
        i = 0;
        return aux;
    }
    else{
        v = t->ultimo;
        c = t->ultimo->carga;
        t->ultimo = v->prox;
        free(v);
        i++;
        remove_carga(t, (-1)*(carga - c));
    }
}

void mostra_vagoes(trem* t){
    vagao* aux = t->ultimo;

    system("cls");

    if(aux == NULL || t == NULL)
        printf("Nenhum vagao existente!");

    if(aux->carga <= 0)
        return;

    printf("\nNumero de vagoes: %d\n", t->numero);
    for(aux = t->ultimo; aux->prox != NULL; aux = aux->prox){
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c\n%cCarga: %d %c\n%c%c%c%c%c%c%c%c%c%c%c%c\n %c        %c\n", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, aux->carga, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 248, 248);
    }
}
