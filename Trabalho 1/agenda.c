#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "agenda.h"

int T_menu (){
	int i;

	printf("Menu Principal:\n\n(1)...Incluir na Agenda\n(2)...Excluir da agenda\n(3)...Buscar telefone por apelido\n(6)...Mostrar Agenda\n\n(9)...Sair\n");
	scanf("%d", &i);
	return i;
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

void desloca(int x){
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
			desloca(j);
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
            scanf("%s", a[i].apelido);
            printf("Nome: ");
            scanf("%s", a[i].nome);
            printf("Telefone: ");
            scanf("%s", a[i].telefone);
            printf("Idade: ");
            scanf("%d", &a[i].idade);
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
    scanf("%s", apel);
    for(i = 0; i < MAX; i++){
    	if((strcmp(apel, a[i].apelido)) == 0){
    		busca++;
			printf("Telefone de %s: %s.\n\n", a[i].apelido, a[i].telefone);
    	}
    }
    if(busca == 0){
    	printf("-1\n");
    }
}

int exclui_agenda(){
    int i, cont = 0;
    char aux[10];
    
    system("cls");
    printf("Insira o apelido a ser excluído: ");
    scanf("%s", aux);
    for(i = 0; i < MAX; i++){
		if((strcmp(aux, a[ind_apelido[i]].apelido)) == 0){
			a[ind_apelido[i]].idade = -1;
			cont = 1;
		}
	}
	return cont;
}

void mostra_agenda(){
	int i;
	system("cls");
    for(i = 0; i < MAX; i++){
    	if(ind_apelido[i] != -1 && a[ind_apelido[i]].idade != -1){
    		printf("\nCód.: %d\t Apelido: %s\t Nome: %s\t Telefone: %s\t Idade: %d\n", ind_apelido[i], a[ind_apelido[i]].apelido, a[ind_apelido[i]].nome, a[ind_apelido[i]].telefone, a[ind_apelido[i]].idade);
    	}
    }
    printf("\n");
}

int main (){

    int i;

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
			case 6:
            	mostra_agenda();
			break;
			default	: printf("Opção %d inválida.\n", i);
        }
    }
		return 1;
}
