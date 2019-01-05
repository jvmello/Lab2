#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"

matriz_esparsa *cria_matriz_esparsa(int i, int j){
    matriz_esparsa* nova = (matriz_esparsa*)malloc(sizeof(matriz_esparsa));
    nova->i = i;
    nova->j = j;
    nova->prim_celula = NULL;
    nova->ult_celula = NULL;

    return nova;
}

int insere(matriz_esparsa *mat, int linha, int coluna, float valor){
    tipo_celula *p;
    p = (tipo_celula*) malloc(sizeof(tipo_celula));

    if(!p){
        return 0;
    }

    p->col = coluna;
    p->lin = linha;
    p->val = valor;
    p->prox = NULL;

    if((mat->prim_celula == NULL)){
        mat->prim_celula = p;
        mat->ult_celula = p;
    }

    else{
        mat->ult_celula->prox = p;
        mat->ult_celula = p;
    }

    return 1;
}

float valorElemento(matriz_esparsa *mat, int linha, int coluna){
	tipo_celula *p;

	p = mat->prim_celula;

	while(p != NULL){
		if(p->lin == linha && p->col == coluna){
			return p->val;
		}

		p = p->prox;
	}

	return 0;
}

int imprimeMatriz(matriz_esparsa *mat){
    int i, j;
    tipo_celula *p;

    p = (tipo_celula*) malloc(sizeof(tipo_celula));
    p = mat->prim_celula;

    for(i = 1; i <= mat->i; i++){
        for(j = 1; j <= mat->j; j++){
            if(p != NULL)
            {
                if(i == p->lin && j == p->col)
                {
                    printf("%.1f\t",p->val);
                    p = p->prox;
                }
                else
                    printf("0.0\t");
            }
            else
                printf("0.0\t");
        }
        printf("\n");
    }

    return 1;
}

matriz_esparsa *somaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    int i, j;
    float soma;
    matriz_esparsa *matriz_soma;

    matriz_soma = cria_matriz_esparsa(matA->i, matA->j);

    if ((matA->i != matB->i) || (matA->j != matB->j)){
        return 0;
    }
    else{
        for(i = 1; i <= matA->i; i++){
            for(j = 1; j <= matA->j; j++){
                soma = valorElemento(matA, i, j) + valorElemento(matB, i, j);
                if(soma != 0){
                    insere(matriz_soma, i, j, soma);
                }
            }
        }
    }

    return matriz_soma;
}

matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    matriz_esparsa *matriz_multiplicacao;
    int i, j, x;
    float aux = 0;

    if((matA->j == matB->i)){
        matriz_multiplicacao = cria_matriz_esparsa(matA->i, matB->j);
        for(i = 1; i <= matA->i; i++){
            for(j = 1; j <= matB->j; j++){
                for(x = 1; x <= matA->j; x++){
                      aux += valorElemento(matA, i, x) *  valorElemento(matB, x, j);
                }
                if(aux != 0){
                    insere(matriz_multiplicacao, i, j, aux);
                }
                aux = 0;
            }
        }
        return matriz_multiplicacao;
    }
    else{
        return 0;
    }
}

void leMatriz(){
    int i = 0, j = 0, lin, col, contM = 0;
    float valor;
    FILE* arq1;
    FILE* arq2;
    char s[100], aux[100], l, matriz[6];
    matriz_esparsa *mat1;
    matriz_esparsa *mat2;
    matriz_esparsa *matsoma;
    matriz_esparsa *matmult;

    arq1 = fopen("matrizes.txt", "r");
    arq2 = fopen("output.txt", "w+");

    while((l = fgetc(arq1)) != EOF){
		*(s+i) = l;
		i++;
	}
	*(s+i) = '\0';

	i = 0;

	while(*(s+i) != 'F'){
       	while(*(s+i) != '\n'){
            *(aux+j) = *(s+i);
            j++;
            i++;
        }
        if(*(aux) == 'M'){
            contM++;
            *(aux+j) = '\0';
            sscanf(aux, "%s %d %d", matriz, &lin, &col);
            printf("Opcao 1: %s %d %d\n", matriz, lin, col);
            if(contM == 1){
                mat1 = cria_matriz_esparsa(lin, col);
            }
            else{
                mat2 = cria_matriz_esparsa(lin, col);
            }
        }
        else{
            *(aux+j) = '\0';
            sscanf(aux, "%d %d %f", &lin, &col, &valor);
            printf("auxxxx %s", aux);
            printf("Opcao 2: %d %d %f\n", lin, col, valor);
            if(contM == 1){
                if(insere(mat1, lin, col, valor)){
                }
                else{
                }
            }
            else{
                if(insere(mat2, lin, col, valor)){
                }
                else{
                }
            }
        }
        *(aux+j) = '\0';
        i++;
        j = 0;
	}

    matsoma = somaMatriz(mat1, mat2);
    matmult = multiplicaMatriz(mat1, mat2);

    printf("\nMatriz 1:\n");
	if(imprimeMatriz(mat1)){
        fprintf(arq2, "Matriz %d %d\n", mat1->i, mat1->j);
        for(i = 1; i <= mat1->i; i++){
            for(j = 1; j <= mat1->j; j++){
                if(valorElemento(mat1, i, j) != 0){
                    fprintf(arq2, "%d %d %.1f\n", i, j, valorElemento(mat1, i, j));
                }
            }
        }
	}
	else{
        printf("Erro ao imprimir matriz 1");
	}

    printf("\nMatriz 2:\n");
	if(imprimeMatriz(mat2)){
        fprintf(arq2, "\nMatriz %d %d\n", mat2->i, mat2->j);
        for(i = 1; i <= mat2->i; i++){
            for(j = 1; j <= mat2->j; j++){
                if(valorElemento(mat2, i, j) != 0){
                    fprintf(arq2, "%d %d %.1f\n", i, j, valorElemento(mat2, i, j));
                }
            }
        }
	}
	else{
        printf("Erro ao imprimir matriz 2");
	}

    printf("\nMatriz soma:\n");
	if(!matsoma){
        printf("Erro ao somar matrizes\n");
        fprintf(arq2, "\nMatriz Soma 0 0\n");
	}
	else{
        if(imprimeMatriz(matsoma)){
            fprintf(arq2, "\nMatriz Soma %d %d\n", matsoma->i, matsoma->j);
            for(i = 1; i <= matsoma->i; i++){
                for(j = 1; j <= matsoma->j; j++){
                    if(valorElemento(matsoma, i, j) != 0){
                        fprintf(arq2, "%d %d %.1f\n", i, j, valorElemento(matsoma, i, j));
                    }
                }
            }
        }
        else{
            printf("Erro ao imprimir matriz soma\n");
            fprintf(arq2, "\nMatriz Soma 0 0\n");
        }
	}

    printf("\nMatriz multiplicacao:\n");
	if(!matmult){
        printf("Erro ao multiplicar matrizes\n");
        fprintf(arq2, "\nMatriz Multiplica 0 0\n");
	}
	else{
        if(imprimeMatriz(matmult)){
            fprintf(arq2, "\nMatriz Multiplica %d %d\n", matmult->i, matmult->j);
            for(i = 1; i <= matmult->i; i++){
                for(j = 1; j <= matmult->j; j++){
                    if(valorElemento(matmult, i, j) != 0){
                        fprintf(arq2, "%d %d %.1f\n", i, j, valorElemento(matmult, i, j));
                    }
                }
            }
        }
        else{
            printf("Erro ao imprimir matriz multiplica\n");
            fprintf(arq2, "\nMatriz Multiplica 0 0\n");
        }
	}

	fclose(arq1);
	fclose(arq2);
}

int main(){
    leMatriz();
    system("output.txt");
    return 1;
}
