#define MAX 30

/* definicao de tipos e variaveis globais       */

struct agenda{
    char	apelido[10];
    char    nome[30];
    char    telefone[12];
	int		idade;
} a[MAX], *PA;

int ind_apelido[MAX];
