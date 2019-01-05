#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float P[10], Q[10];

void quebra(char s[100], char escolha, bool positivo){
	float a, j = 0;
	char n[20];
	int i = 0;
	
	while(*(s+i) != 'X' && *(s+i) != 'x'){
		*(n+i) = *(s+i);
		i++;
	}
	
	*(n+i) = '\0';
	
	if(*(s+i) == '\0'){
		if(escolha == 'P'){
			if(positivo == true)
				*(P) = atof(n);
			else
				*(P) = -(atof(n));
		}
		else if(escolha == 'Q'){
			if(positivo == true)
				*(Q) = atof(n);
			else
				*(Q) = -(atof(n));
		}
	}
	else{
		if(*(s+i+1) == '\0'){
			if(escolha == 'P'){
				if(positivo == true)
					*(P+1) = atof(n);
				else
					*(P+1) = -(atof(n));
			}
			else if(escolha == 'Q'){
				if(positivo == true)
					*(Q+1) = atof(n);
				else
					*(Q+1) = -(atof(n));
			}
		}
		else{
			if(escolha == 'P'){
				if(positivo == true)
					*(P+ *(s+i+1)- 48) = atof(n);
				else
					*(P+ *(s+i+1)- 48) = -(atof(n));
			}
			else if(escolha == 'Q'){
				if(positivo == true)
					*(Q+ *(s+i+1)- 48) = atof(n);
				else
					*(Q+ *(s+i+1)- 48) = -(atof(n));
			}
		}	
	}
}

void escreve_polinomio(char s[100], float aux[10], int tam, char escolha){
	int i = 0, j = 0, x;
	char a[100], b;
	float auxiliar[10];
	bool positivo;

    for(i = 0; i <= tam; i++){
    	b = *(s+i);
        
        if(*(s+i) != '+' && *(s+i) != '-'){
			*(a+j) = b;
			j++;
        }
        
        else{
        	if(*(a+j) >= 0)
        		positivo = true;
        	else
        		positivo = false;
        	*(a+j) = '\0';
        	quebra(a, escolha, positivo);
        	j = 0;
        }
    }
    if(*(a+j) >= 0)
    	positivo = true;
    else
    	positivo = false;
    	
    quebra(a, escolha, positivo);
}

void substituicao(float x, FILE* arq){
	float Px = 0, Qx = 0;
	int i = 0;
	
	for(i = 0; i < 10; i++){
		Px = Px + (*(P+i) * pow(x, i));
		Qx = Qx + (*(Q+i) * pow(x, i));
	}
	fprintf(arq, "\nP(%.2f) = %.2f", x, Px);
	fprintf(arq, "\nQ(%.2f) = %.2f", x, Qx);
}

void soma(float x, FILE* arq){
	float soma[10], somax = 0;
	int i;
	
	fprintf(arq, "\nSoma P+Q =");
	
	for(i = 9; i >= 0; i--){
		*(soma+i) = *(P+i) + *(Q+i);
		if(*(soma+i) != 0){
			if(*(soma+i) >= 0)
				fprintf(arq, " +");
			else
				fprintf(arq, " ");
			
			fprintf(arq, "%.2fX%d", *(soma+i), i);	
		}
	}
	for(i = 0; i < 10; i++){
		somax = somax + (*(P+i) * pow(x, i)) + (*(Q+i) * pow(x, i));
	}
		
	fprintf(arq, "\nSoma(%.2f) = %f", x, somax);
}

void subtracao(float x, FILE* arq){
	float subtracao[10], subtracaox = 0;
	int i, cont = 0;
	
	fprintf(arq, "\nSubtracao P-Q =");
	
	for(i = 9; i >= 0; i--){
		*(subtracao+i) = *(P+i) - *(Q+i);
		if(*(subtracao+i) != 0){
			if(*(subtracao+i) >= 0)
				fprintf(arq, " +");
			else
				fprintf(arq, " ");
			
			fprintf(arq, "%.2fX%d", *(subtracao+i), i);	
		}
		else{
			cont++;
		}
		
		if(cont == 10)
			fprintf(arq, "0");
	}
	for(i = 0; i < 10; i++){
		subtracaox = subtracaox + (*(P+i) * pow(x, i)) - (*(Q+i) * pow(x, i));
	}
		
	fprintf(arq, "\nSubtracao(%.2f) = %f", x, subtracaox);
}

void derivada(float x, FILE* arq){
	float derivada[10], derivadax = 0;
	int i, cont = 0;
	
	fprintf(arq, "\nDerivada Q =");
	for(i = 9; i >= 1; i--){
		*(derivada+i) = i * *(Q+i);
		derivadax = derivadax + (*(derivada+i) * pow(x, i-1));
		if(*(derivada+i) != 0){
			if(*(derivada+i) >= 0)
				fprintf(arq, " +");
			else
				fprintf(arq, " ");
			
			fprintf(arq, "%.2fX%d", *(derivada+i), i-1);	
		}
		else{
			cont++;
		}
		if(cont == 10)
			fprintf(arq, "0");
	}
	
	fprintf(arq, "\nDerivada Q(%.2f) = %.2f", x, derivadax);
}

void integral(float x, FILE* arq){
	float integral[10], integralx = 0;
	int i, cont = 0;
	
	fprintf(arq, "\nIntegral P =");
	for(i = 9; i >= 0; i--){
		*(integral+i) = *(P+i) / (i+1);
		integralx = integralx + (*(integral+i) * pow(x, i+1));
		if(*(integral+i) != 0){
			if(*(integral+i) >= 0)
				fprintf(arq, " +");
			else
				fprintf(arq, " ");
			
			fprintf(arq, "%.2fX%d", *(integral+i), i+1);	
		}
		else{
			cont++;
		}
		
		if(cont == 10)
			fprintf(arq, "0");
	}
	fprintf(arq, " + C");
	
	fprintf(arq, "\nIntegral P(%.2f) = %.2f", x, integralx);
}

void converte(){
	char pp[100], qq[100], xx[100], leitura, s[100];
	FILE* arq1;
	FILE* arq2;
	double x;
	int ch, cont, i=0, j=0;
	
	arq1 = fopen("f-input.txt", "r");

	arq2 = fopen("f-output.txt", "w+");

	while((leitura=fgetc(arq1)) != EOF){
		*(s+i) = leitura;
		i++;
	}
	*(s+i) = '\0';

	i = 0;

	while(*(s+i) != '\n'){
		if(*(s+i) != 'P' && *(s+i) != '='){
			*(pp+j) = *(s+i);
			i++;
			j++;
		}
		else{
			i++;
		}
	}
	
	if((*(pp+i)-2) != 'x'|| (*(pp+i)-2) != 'X' || (*(pp+i)-1) != 'x' || (*(pp+i)-1) != 'X'){
		*(pp+j) = 'x';
		*(pp+j+1) = '0';
		*(pp+j+2) = '\0';
	}
	else{
		*(pp+j) = '\0';	
	}
	
	++i;
	j = 0;

	while(*(s+i) != '\n'){
		if(*(s+i) != 'Q' && *(s+i) != '='){
			*(qq+j) = *(s+i);
			i++;
			j++;
		}
		else{
			i++;
		}
	}
	if((*(qq+i)-2) != 'x'|| (*(qq+i)-2) != 'X' || (*(qq+i)-1) != 'x' || (*(qq+i)-1) != 'X'){
		*(qq+j) = 'x';
		*(qq+j+1) = '0';
		*(qq+j+2) = '\0';
	}
	else{
		*(qq+j) = '\0';	
	}

	++i;
	j = 0;

	while(*(s+i) != '\0'){
		if(*(s+i) != 'x' && *(s+i) != '='){
			*(xx+j) = *(s+i);
			i++;
			j++;
		}
		else{
			i++;
		}
	}
	*(xx+j) = '\0';

	x = atof(xx);

	fprintf(arq2, "%s", s, pp, qq, xx, x);

   	escreve_polinomio(pp, P, strlen(pp), 'P');
    escreve_polinomio(qq, Q, strlen(qq), 'Q');

	substituicao(x, arq2);

	soma(x, arq2);
	
	subtracao(x, arq2);
	
	derivada(x, arq2);
	
	integral(x, arq2);
	
	fprintf(arq2, "\nFim");
	
	fclose(arq1);
	fclose(arq2);
	
	system("f-output.txt");
}

int main(){
	converte();
	
	printf("\nFim");

	return 0;
}
