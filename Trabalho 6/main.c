#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "paciencia.h"

int numeros[40];

tipo_descritor_pilha* cria_pilha(int n){
    tipo_descritor_pilha* nova = (tipo_descritor_pilha*) malloc(sizeof(tipo_descritor_pilha));

    if(!nova) exit(1);

    nova->topo = NULL;
    nova->n = n;

    return nova;
}
tipo_descritor_lista* cria_lista(int n){
    tipo_descritor_lista* nova = (tipo_descritor_lista*) malloc(sizeof(tipo_descritor_lista));

    if(!nova) exit(1);

    nova->prim = NULL;
    nova->ult = NULL;
    nova->n = n;

    return nova;
}

int insere_pilha(tipo_descritor_pilha* aux, int n, int visivel){
    st_pilha* pilha = (st_pilha*) malloc(sizeof(st_pilha));

    if (pilha==NULL) return 0;

    pilha->carta.valor = valor_carta(n);
    pilha->carta.naipe = naipe_carta(n);
    pilha->carta.indice = n;
    pilha->visivel = visivel;
    pilha->prox = aux->topo;

    aux->topo = pilha;

    return 1;
}

int insere_lista(tipo_descritor_lista* lista, int n, int visivel){
    st_lista_circular* l = (st_lista_circular*) malloc(sizeof(st_lista_circular));

    if(l == NULL) return 0;

    l->carta.valor = valor_carta(n);
    l->carta.naipe = naipe_carta(n);
    l->carta.indice = n;
    l->visivel = visivel;

    if(lista->prim == NULL){
        l->ant = lista->prim;
        l->prox = lista->ult;
        lista->prim = l;
        lista->ult = l;
    }
    else{
        l->ant = lista->ult;
        l->prox = lista->prim;
        lista->ult->prox = l;
        lista->ult = lista->ult->prox;
    }

    return 1;
}

void remove_pilha(tipo_descritor_pilha* aux){
    st_pilha* p;

    if(p == NULL)
        exit(1);

    p = aux->topo;

    aux->n--;
    printf("N = %d\n", aux->n);

    aux->topo = aux->topo->prox;
    aux->topo->visivel = 1;

    free(p);
}

void remove_lista(tipo_descritor_lista *L, st_lista_circular *aux){
    st_lista_circular *l = aux;

    if(l == NULL) exit(1);

    aux = aux->prox;

    free(l);
}

void jogo(){
    tipo_descritor_pilha* p[7];
    st_pilha* aux[7];
    tipo_descritor_pilha* naipes[4];
    tipo_descritor_lista* L;
    st_lista_circular* Laux;
    int val, val2, i, j, n = 0, op, E = -1, P = -1, C = -1, O = -1;
    char pilha, pilha2;
    char E1, E2, C1, C2, P1, P2, O1, O2, N1, N2;

    gera_numeros();

    E1 = 'E';
    E2 = ' ';
    C1 = 'C';
    C2 = ' ';
    P1 = 'P';
    P2 = ' ';
    O1 = 'O';
    O2 = ' ';
    N1 = '-';
    N2 = '-';

    for(i = 0; i < 7; i++){
        p[i] = cria_pilha(i+1);
    }

    for(i = 0; i < 4; i++){
        naipes[i] = cria_pilha(i+1);
    }

    for(i = 0; i < 7; i++){
        for(j = 0; j <= i; j++){
            insere_pilha(p[i], n, i==j);
            n++;
        }
    }

    L = cria_lista(40 - n);

    for(i = n-1; i < 40; i++){
        insere_lista(L, i, 0);
    }

    Laux = L->prim;

    printf("Embaralhando...");
    Sleep(3000);

    system("cls");

    while(E != 10 && C != 10 && P != 10 && O != 10){
        printf("%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c                  %c%c%c%c%c%c%c%c%c\n%c       %c     %c       %c     %c       %c     %c       %c                  %c       %c\n%c       %c     %c       %c     %c       %c     %c       %c                  %c       %c\n%c  %c%c   %c     %c   %c%c  %c     %c   %c%c  %c     %c   %c%c  %c                  %c  %c%c   %c\n%c       %c     %c       %c     %c       %c     %c       %c                  %c       %c\n%c       %c     %c       %c     %c       %c     %c       %c                  %c       %c\n%c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c                  %c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 205, 205, 187, 201, 205, 205, 205, 205, 205, 205, 205, 187, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, E1, E2, 186, 186, C1, C2, 186, 186, P1, P2, 186, 186, O1, O2, 186, 186, N1, N2, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 200, 205, 205, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 205, 205, 188, 200, 205, 205, 205, 205, 205, 205, 205, 188);

        printf("\n P1    P2    P3    P4    P5    P6    P7\n\n");

        for(i = 0; i < 7; i++){
            aux[i] = p[i]->topo;
        }

        for(i = 0; i < 7; i++){
            for(j = 0; j < 7; j++){
                if(aux[j] == NULL){
                    printf("      ");
                }
                else{
                    if(aux[j]->visivel)
                        printf("|%d%c|  ", aux[j]->carta.valor, aux[j]->carta.naipe);
                    else
                        printf("   %c  ", 219);

                    aux[j] = aux[j]->prox;
                }
            }
        printf("\n");
        }

        printf("\nSelecione uma das seguintes opcoes:\n\t(1)...Consultar proxima carta da lista de estoque\n\t(2)...Empilhar uma das cartas nos naipes\n\t(3)...Empilhar uma das cartas em outra pilha\n\t(0)...Para sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                Laux = Laux->prox;
                N1 = Laux->carta.valor + 48;
                N2 = Laux->carta.naipe;
                system("cls");
            break;

            case 2:
                printf("Insira a pilha a ter a carta empilhada(P8 para lista auxiliar): ");
                fflush(stdin);
                scanf("%c%d", &pilha, &val);

                while((val < 1 && val > 8) || (pilha != 'P' && pilha != 'p')){
                    printf("Opcao invalida! Tente novamente: ");
                    fflush(stdin);
                    scanf("%c%d", &pilha, &val);
                }

                if(val == 8){
                    if(Laux->carta.naipe == 'E'){
                        if(Laux->carta.valor == E+1){
                            E1 = Laux->carta.valor + 48;
                            E2 = Laux->carta.naipe;
                            insere_pilha(naipes[0], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(Laux->carta.naipe == 'C'){
                        if(Laux->carta.valor == C+1){
                            printf("oloco");
                            C1 = Laux->carta.valor + 48;
                            C2 = Laux->carta.naipe;
                            insere_pilha(naipes[1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(Laux->carta.naipe == 'P'){
                        if(Laux->carta.valor == P+1){
                            printf("oloco");
                            P1 = Laux->carta.valor + 48;
                            P2 = Laux->carta.naipe;
                            insere_pilha(naipes[2], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(Laux->carta.naipe == 'O'){
                        if(Laux->carta.valor == O+1){
                            printf("oloco");
                            O1 = Laux->carta.valor + 48;
                            O2 = Laux->carta.naipe;
                            insere_pilha(naipes[3], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                }
                else{
                    if(p[val-1]->topo->carta.naipe == 'E'){
                        if(p[val-1]->topo->carta.valor == E+1){
                            E1 = p[val-1]->topo->carta.valor + 48;
                            E2 = p[val-1]->topo->carta.naipe;
                            insere_pilha(naipes[0], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                            E++;
                        }
                    }
                else if(p[val-1]->topo->carta.naipe == 'C'){
                        if(p[val-1]->topo->carta.valor == C+1){
                            C1 = p[val-1]->topo->carta.valor + 48;
                            C2 = p[val-1]->topo->carta.naipe;
                            insere_pilha(naipes[0], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                            C++;
                        }
                }
                else if(p[val-1]->topo->carta.naipe == 'P'){
                    if(p[val-1]->topo->carta.valor == P+1){
                            P1 = p[val-1]->topo->carta.valor + 48;
                            P2 = p[val-1]->topo->carta.naipe;
                            insere_pilha(naipes[2], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                            P++;
                    }
                }
                else if(p[val-1]->topo->carta.naipe == 'O'){
                    if(p[val-1]->topo->carta.valor == O+1){
                            O1 = p[val-1]->topo->carta.valor + 48;
                            O2 = p[val-1]->topo->carta.naipe;
                            insere_pilha(naipes[3], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                            O++;
                        }
                    }
                }
                system("cls");
            break;

            case 3:
                printf("Insira a pilha a ter a carta empilhada e a pilha de destino(P8 = pilha auxiliar): ");
                fflush(stdin);
                scanf("%c%d %c%d", &pilha, &val, &pilha2, &val2);

                while((val < 1 && val > 8 && val2 < 1 && val2 > 7) || (pilha != 'P' && pilha != 'p' && pilha2 != 'P' && pilha2 != 'p')){
                    printf("Opcao invalida! Tente novamente: ");
                    fflush(stdin);
                    scanf("%c%d %c%d", &pilha, &val, &pilha2, &val2);
                    printf("\n");
                }

                if(val2 == 8){
                    if(p[val2-1]->topo->carta.naipe == 'E'){
                        if(Laux->carta.valor == Laux->carta.valor+1 && (Laux->carta.naipe == 'C' || Laux->carta.naipe == 'O')){
                            insere_pilha(p[val2-1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'C'){
                        if(p[val2-1]->topo->carta.valor == Laux->carta.valor+1 && (Laux->carta.naipe == 'E' || Laux->carta.naipe == 'P')){
                            insere_pilha(p[val2-1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'P'){
                        if(p[val2-1]->topo->carta.valor == Laux->carta.valor+1 && (Laux->carta.naipe == 'C' || Laux->carta.naipe == 'O')){
                            insere_pilha(p[val2-1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'O'){
                        if(p[val2-1]->topo->carta.valor == Laux->carta.valor+1 && (Laux->carta.naipe == 'E' || Laux->carta.naipe == 'P')){
                            insere_pilha(p[val2-1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                }
                else{
                    if(p[val2-1]->topo->carta.naipe == 'E'){
                        if(p[val2-1]->topo->carta.valor == p[val-1]->topo->carta.valor+1 && (p[val-1]->topo->carta.naipe == 'C' || p[val-1]->topo->carta.naipe == 'O')){
                            insere_pilha(p[val2-1], Laux->carta.indice, 1);
                            remove_lista(L, Laux);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'C'){
                        if(p[val2-1]->topo->carta.valor == p[val-1]->topo->carta.valor+1 && (p[val-1]->topo->carta.naipe == 'E' || p[val-1]->topo->carta.naipe == 'P')){
                            insere_pilha(p[val2-1], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'P'){
                        if(p[val2-1]->topo->carta.valor == p[val-1]->topo->carta.valor+1 && (p[val-1]->topo->carta.naipe == 'C' || p[val-1]->topo->carta.naipe == 'O')){
                            insere_pilha(p[val2-1], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                        }
                    }
                    else if(p[val2-1]->topo->carta.naipe == 'O'){
                        if(p[val2-1]->topo->carta.valor == p[val-1]->topo->carta.valor+1 && (p[val-1]->topo->carta.naipe == 'E' || p[val-1]->topo->carta.naipe == 'P')){
                            insere_pilha(p[val2-1], p[val-1]->topo->carta.indice, 1);
                            remove_pilha(p[val-1]);
                        }
                    }
                }

                system("cls");
            break;

            case 0:
                exit(1);
            break;

            default:
                printf("Opcao invalida!\n");
            break;
        }
    }
}

int main(){
    system("color 2f");

    jogo();

    return 1;
}
