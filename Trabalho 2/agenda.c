#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "agenda.h"

int T_menu(){
    int i;
	char c[5];

	printf("Menu Principal:\n\n(1)...Incluir na Agenda\n(2)...Excluir da agenda\n(3)...Buscar telefone por apelido\n(4)...Gravar dados em arquivo\n(5)...Mostrar dados de arquivo\n(6)...Mostrar Agenda\n(7)...Mostrar agenda ordenada\n\n(9)...Sair\n");
	return atoi(gets(c));
}

int inicializa_agenda(){
    int i, cont = 0;

    for(i = 0; i < MAX; i++){
        a[i].idade = -1;
        ind_apelido[i] = -1;
        cont++;
    }
    if(cont == (MAX - 1)){
        return 1;
    }
}

void desloca_cima(int x){
	int k, i;

    for(k = x; k < (MAX - 1); k++){
    	printf("\nposicao %d tinha %d recebe %d\n", k, ind_apelido[k], ind_apelido[k+1]);
        ind_apelido[k] = ind_apelido[k+1];
    }
}

void desloca_baixo(int x){
    int k, i;

    for(k = (MAX - 1); k > x; k--){
        ind_apelido[k] = ind_apelido[k-1];
    }
}

int inclui_ind(int i){
    int j, sai = 0;

    for(j = 0; j < MAX && !sai; j++){
        if(ind_apelido[j] == -1){
            ind_apelido[j] = i;
            sai = 1;
        }
        else{
        }
        
        if(strcmp(a[i].apelido, a[ind_apelido[j]].apelido) < 0){
			desloca_baixo(j);
            ind_apelido[j] = i;
            sai = 1;
        }
    }
}

int inclui_agenda(){
    int i, j, cont = 0, k;

    for(i = 0; i < MAX; i++){
        if(a[i].idade == -1){
        	k = i;
        	system("cls");
        	printf("Apelido: ");
            gets(a[i].apelido);
            printf("Nome: ");
            gets(a[i].nome);
            printf("Telefone: ");
            gets(a[i].telefone);
            printf("Idade: ");
        	scanf("%d", &a[i].idade);
            fflush(stdin);
            system("cls");
            break;
    	}
    }

    for(j = 0; j < MAX; j++){
    	if(strcmp(a[j].apelido, a[i].apelido) == 0){
    		cont++;
    	}
    }
    if(cont == 1){
    	inclui_ind(k);
		return 1;
    }
    else{
    	a[i].idade = -1;
    	return 0;
    }
}

char busca_telefone_por_apelido(){
    int i, busca = 0;

	char apel[10];
	system("cls");
	printf("Insira o apelido para busca: ");
    gets(apel);
    for(i = 0; i < MAX; i++){
    	if((strcmp(apel, a[ind_apelido[i]].apelido)) == 0){
    		if(a[ind_apelido[i]].idade != -1){
            busca++;
			printf("Telefone de %s: %s.\n\n", a[ind_apelido[i]].apelido, a[ind_apelido[i]].telefone);
			}
    	}
    }
    if(busca == 0){
    	printf("\n-1(Apelido não encontrado)\n\n");
    }
}

int exclui_agenda(){
    int i, cont = 0;
    char aux[10];

    system("cls");
    printf("Insira o apelido a ser excluído: ");
    gets(aux);
    for(i = 0; i < MAX; i++){
		if((strcmp(aux, a[ind_apelido[i]].apelido)) == 0){
			a[ind_apelido[i]].idade = -1;
			printf("%d", ind_apelido[i]);
			desloca_cima(i);
			cont = 1;
		}
		if(cont)
			break;
	}
	return cont;
}

void mostra_agenda(){
	int i;
	system("cls");
    for(i = 0; i < MAX; i++){
    	if(a[i].idade != -1){
    		printf("\nCód.: %d\t Apelido: %s\t Nome: %s\t Telefone: %s\t Idade: %d\n", i, a[i].apelido, a[i].nome, a[i].telefone, a[i].idade);
    	}
    }
    printf("\n");
}

void mostra_agenda_ordenada(){
	int i;
	system("cls");
    for(i = 0; i < MAX; i++){
    	if(ind_apelido[i] >= 0 && a[ind_apelido[i]].idade != -1){
    		printf("\nCód.: %d\t Apelido: %s\t Nome: %s\t Telefone: %s\t Idade: %d\n", i, a[ind_apelido[i]].apelido, a[ind_apelido[i]].nome, a[ind_apelido[i]].telefone, a[ind_apelido[i]].idade);
    	}
    }
    printf("\n");
}

int cria_arquivo(){
	int i;
	FILE* arq;
	system("cls");
	arq = fopen("agenda.txt", "w+");
    for(i = 0; i < MAX; i++){
    	if((PA+i)->idade != -1){
    		fprintf(arq, "Cód.: %d\t Apelido: %s\t Nome: %s\t Telefone: %s\t Idade: %d\n", i, (PA+i)->apelido, (PA+i)->nome, (PA+i)->telefone, (PA+i)->idade);
		}
    }
    fclose(arq);
    return 1;
}

void abre_arquivo(){
	system("agenda.txt");
}

int main (){

    int i;

    PA = a;

	setlocale(LC_ALL, "PORTUGUESE");

	if (!inicializa_agenda()){
    	printf("Erro na inicialização do vetor da agenda.\n");
        return 0;
    }

	while ((i=T_menu()) != 9){
		switch (i){
            case 1:
                if(inclui_agenda()){
                	printf("\nDados incluídos com sucesso.\n\n");
                }
                else{
                	printf("\nOs dados não foram incluídos com sucesso(Apelido duplicado).\n\n");
                }
            break;
			case 2:
                if(exclui_agenda()){
                	printf("\nOs dados foram excluídos com sucesso.\n\n");
                }
                else{
                	printf("\nOs dados não foram excluídos com sucesso(Apelido inexistente).\n\n");
                }
			break;
			case 3:
                busca_telefone_por_apelido();
			break;
			case 4:
                if(cria_arquivo()){
                	printf("\nArquivo criado com êxito.\n\n");
                }
                else{
                	printf("\nArquivo não foi criado com êxito.\n\n");
                }
			break;
			case 5:
				abre_arquivo();
			break;
			case 6:
            	mostra_agenda();
			break;
			case 7:
				mostra_agenda_ordenada();
			break;
			default: printf("\nOpção %d inválida.\n\n", i);
        }
    }
		return 1;
}
