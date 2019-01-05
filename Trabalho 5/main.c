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

int removeElemento(matriz_esparsa *mat, int linha, int coluna){
    tipo_celula *p;

    if(mat->prim_celula->lin == linha && mat->prim_celula->col == coluna){
        free(mat->prim_celula);
        mat->prim_celula = mat->prim_celula->prox;
        return 1;
    }
    else if(mat->ult_celula->lin == linha && mat->ult_celula->col == coluna){
        free(mat->ult_celula);
        return 1;
    }
    else{
        p = (tipo_celula*) malloc(sizeof(tipo_celula));

        p = mat->prim_celula;

        while(p != NULL){
            if(p->lin == linha && p->col == coluna){
                free(p);
                p = p->prox;
                return 1;
            }
		p = p->prox;
        }
    }

    return 0;
}

int insereOrdenado(matriz_esparsa *mat, int linha, int coluna, float valor, int pos){
    tipo_celula *p;
    int i, j;

    p = (tipo_celula*) malloc(sizeof(tipo_celula));

    printf("\n\nMatriz resultado:");

    if(!p){
        return 0;
    }

    p = mat->prim_celula;

    for(i = 1; i < linha; i++){
        for(j = 1; j < coluna; j++){
            p = p->prox;
        }
    }

    p->col = coluna;
    p->lin = linha;
    p->val = valor;

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

int Operacao(matriz_esparsa *mat, char ant[5], char aux[10]){
    int i = 0, j, lin1, lin2, lin3, col1, col2, col3, pos;
    float res;
    char op, l1[2], l2[2], l3[2];

    while(i < strlen(aux)){
        if((*(aux+i) == '+') || (*(aux+i) == '-') || (*(aux+i) == '*') || (*(aux+i) == '/')){
            op = *(aux+i);
            j = i;
        }
        i++;
    }

    *(l1) = aux[j-1];
    *(l2) = aux[j+2];
    *(l3) = *(ant+1);

    lin1 = atoi(l1);
    lin2 = atoi(l2);
    lin3 = atoi(l3);

    col1 = (*(aux+j-2) - 'A' + 1);
    col2 = (*(aux+j+1) - 'A' + 1);
    col3 = (*(ant) - 'A' + 1);

    switch(op){
        case '+':
            res = (valorElemento(mat, lin1, col1) + valorElemento(mat, lin2, col2));
        break;
        case '-':
            res = (valorElemento(mat, lin1, col1) - valorElemento(mat, lin2, col2));
        break;
        case '*':
            res = (valorElemento(mat, lin1, col1) * valorElemento(mat, lin2, col2));
        break;
        case '/':
            if((valorElemento(mat, lin2, col2)) == 0){
                res = 0;
            }
            else{
                res = (valorElemento(mat, lin1, col1)) / (valorElemento(mat, lin2, col2));
            }
        break;
        default:
            return 0;
        break;
    }

    pos = ((lin3-1)*(mat->j + col3));

    if(res == 0){
        removeElemento(mat, lin3, col3);
    }
    else{
        insereOrdenado(mat, lin3, col3, res, pos);
    }

    return 1;
}

void leOperacao(matriz_esparsa *mat){
    int i = 0, j = 0, cont = 0, contLinha = 0;
    FILE* arq;
    char s[100], ant[5], aux[10], linha[100], l;

    arq = fopen("operacao.txt", "r");

    while((l = fgetc(arq)) != EOF){
		if((l != '=')){
            *(s+i) = l;
		}
		else{
            *(s+i) = ' ';
		}
		if(l == '\n'){
            contLinha++;
		}
		i++;
	}
	*(s+i) = '\0';

	i = 0;

    while(cont < contLinha){
        while(*(s+i) != '\n'){
                *(linha+j) = *(s+i);
                i++;
                j++;
        }
        i++;
        *(linha+j) = '\0';
        sscanf(linha, "%s %s", ant, aux);
        Operacao(mat, ant, aux);
        j = 0;
        cont++;
    }

    j = 0;

    while(*(s+i) != '\0'){
        *(linha+j) = *(s+i);
        i++;
        j++;
    }

    *(linha+j) = '\0';
    sscanf(linha, "%s %s", ant, aux);
    Operacao(mat, ant, aux);

	fclose(arq);
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

matriz_esparsa *leMatriz(){
    int i = 0, j = 0, lin, col, contM = 0;
    float valor;
    FILE* arq1;
    FILE* arq2;
    char s[100], aux[100], l, matriz[6];
    matriz_esparsa *mat1;
    matriz_esparsa *mat2;

    arq1 = fopen("matrizes.txt", "r");
    arq2 = fopen("resultado.txt", "w+");

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

    printf("Matriz:\n");
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
        printf("Erro ao imprimir matriz");
	}

	fclose(arq1);
	fclose(arq2);

	return mat1;
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

int main(){
    matriz_esparsa *mat;
    mat = leMatriz();
    leOperacao(mat);
    printf("\n");
    imprimeMatriz(mat);

    system("resultado.txt");
    return 1;
}
