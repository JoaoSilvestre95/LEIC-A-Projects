#include <stdio.h>
#include <stdlib.h>
#define DIM 1000 		/*Dimensao maxima da matriz com os dados referentes aos bancos*/
#define NOME_MAX 41		/*Constante com o numero maximo de caracteres do nome do banco*/
#define MAU 0			/*Classificacao de banco mau*/
#define BOM 1 			/*Classificacao de banco bom*/

/* estrutura com informacoes a cerca de cada banco, numero de bancos com divida ao
 respetivo banco (inP), numero de bancos com quem o banco tem divida (outP) , valor emprestado 
 a outros bancos (outV), valor emprestado a bancos maus (outVM), valor emprestado por outros bancos (inV) 
 e valor emprestado por bancos maus (inVM) e o numero de parceiros de cada banco */

typedef struct {                                                                    
	char nome[NOME_MAX]; 
	int classificacao, referencia, inP, outP, outV, outVM, inV, inVM, parceiros;
} banco;

/**************Variaveis***************/

int dados[DIM][DIM]; 	/* Matriz com os emprestimos entre os bancos */
banco bancos[DIM]; 		/* Vetor com os dados dos bancos */
int posi = 0; 			/* Variavel global com a posicao do ultimo banco no vetor */

/**************Prototipos**************/

void criaBanco();
void promove();
void despromove();
void maiorDificuldade();
int procuraBanco();
void emprestimo();
void amortizacao();
void transacoes();
void list();
void saida();

/* funcao principal que recebe um comando e seleciona o que efetuar consoante o comando recebido */

int main(){              
	char command;
	while (1) {
		command = getchar(); /* le o comando */
		switch (command) {
		case 'a':
			criaBanco();
			break;
		case 'k':
			despromove();
			break;
		case 'l':
			list();
			break;
		case 'r':
			promove();
			break;
		case 'e':
			emprestimo();
			break;
		case 'p':
			amortizacao();
			break;
		case 'K':
			maiorDificuldade();
			break;
		case 'x':
			saida();
			return EXIT_SUCCESS; /* Termina o programa com sucesso */
		default:
			printf("ERRO: Comando desconhecido\n");
		}
		getchar(); /* le o '\n' introduzido pelo utilizador */
	}
	return EXIT_FAILURE; 
}


void criaBanco(){ /* funcao selecionada pelo comando a, que recebe um nome, uma classificacao e uma referencia e cria o respetivo banco */  
	banco a;
	scanf("%s %d %d", a.nome, &a.classificacao, &a.referencia);
	bancos[posi]=a;
	posi++;
}

void despromove() { /* funcao selecionada pelo comando k, que recebe uma referencia e despromove a 'banco mau' o respetivo banco */
	int ref;
	scanf("%d", &ref);
	bancos[procuraBanco(ref)].classificacao = MAU;  /* procura o banco com a referencia introduzida e efetua a despromocao */
}

void promove() {  /* funcao selecionada pelo comando r, que recebe uma referencia e promove a 'banco bom' o respetivo banco */
	int ref;
	scanf("%d", &ref);
	bancos[procuraBanco(ref)].classificacao = BOM;  /* procura o banco com a referencia introduzida e efetua a promocao */
}

void maiorDificuldade() {  /* funcao selecionada pelo comando K, que procura o banco com maior valor emprestado a 'bancos maus' e despromove esse banco, se existir mais do que um, depromove o mais recente */
	int i, max=0, mau;
	transacoes();
	for(i=0; i<posi; i++) {
		if (bancos[i].classificacao == BOM){
			if (bancos[i].outVM >= max){		/*Se houver mais do que um banco na mesma situacao o mais recente e que e despromovido*/
				mau = i;
				max = bancos[i].outVM;
			}
		}
	}
	if (max != 0){		/*Verifica se ha alguma banco em condicoes de ser despromovido*/
		bancos[mau].classificacao = MAU;
		printf("*%d %s %d %d %d %d %d %d %d\n", bancos[mau].referencia, bancos[mau].nome,
												 bancos[mau].classificacao, bancos[mau].inP, bancos[mau].outP, 
												 bancos[mau].outV, bancos[mau].outVM, bancos[mau].inV, bancos[mau].inVM);
	}
	saida();
}

int procuraBanco(int ref) {  /* funcao auxiliar que recebe uma referencia e procura o banco com a respetiva referencia e retorna a posicao em que o banco se encontra no vetor */
	int i;
	for (i=0; i<posi; i++){
		if(bancos[i].referencia == ref)
			return i;
	}
	return 0;
}

void emprestimo() {  /* funcao selecionada pelo comando e, que recebe a referencia do banco que fornece o credito (ref1), referencia do banco que recebe o emprestimo (ref2) e o valor do emprestimo */  
	int ref1, ref2, valor;
	scanf("%d %d %d", &ref1, &ref2, &valor);
	dados[procuraBanco(ref1)][procuraBanco(ref2)] += valor; /* procura os respetivos bancos e efetua o emprestimo */ 
}

void amortizacao() {  /* funcao selecionada pelo comando p, que recebe a referencia do banco pagador (ref1), referencia do banco que recebe o valor (ref2) e o valor (inteiro positivo, menor ou igual ao valor em divida) */
	int ref1, ref2, valor;
	scanf("%d %d %d", &ref1, &ref2, &valor);
	if((valor <= dados[procuraBanco(ref2)][procuraBanco(ref1)]) && (dados[procuraBanco(ref2)][procuraBanco(ref1)] !=0))
		dados[procuraBanco(ref2)][procuraBanco(ref1)] -= valor; /* procura os bancos atraves da referencia e amortiza a divida */ 
}

void transacoes(){  		/*Calcula as transacoes efetuadas por cada banco (inP, outP, inV, outV, inVM, outVM) e o numero de parceiros de cada banco*/
	int i, j, k;
	for(i=0; i<posi; i++){		/*Coloca os valores das transacoes a 0*/
		bancos[i].inP=0, bancos[i].outP=0, bancos[i].outV=0, bancos[i].inV=0, bancos[i].outVM=0, bancos[i].inVM=0, bancos[i].parceiros=0;
	}	
	for(i=0; i<posi; i++){		/*Percorre a matriz e calcula as transacoes efetuadas por cada banco*/
		for(j=0; j<posi; j++){
			if(dados[i][j] != 0){
				bancos[i].outP++;
				bancos[j].inP++;
				bancos[i].outV += dados[i][j];
				bancos[j].inV += dados[i][j];
				if (bancos[j].classificacao == MAU) 
					bancos[i].outVM += dados[i][j];
				if (bancos[i].classificacao == MAU)
				 	bancos[j].inVM += dados[i][j];
			}
		}
	}
	for(i=0; i<posi; i++){			/* Calcula o numero de parceiros de cada banco */
	bancos[i].parceiros = bancos[i].inP + bancos[i].outP;
		for(k=0; k<posi; k++){    			
			if((dados[i][k] != 0) && (dados[k][i]!=0))
				bancos[i].parceiros--;
		}
	}
}

void list() {  /*funcao selecionada pelo comando l, que recebe um tipo, que vai dizer como a lista de bancos deve ser ordenada */
	int tipo, j, i;
	scanf("%d", &tipo);
	if(tipo == 0){   /* se o tipo for 0 os bancos serao ordenados pela ordem de introducao no sistema com o respetivo nome e classificacao */
		for(j=0; j<posi; j++){
			printf("%d %s %d\n", bancos[j].referencia, bancos[j].nome, bancos[j].classificacao);
		}
	}
	else if (tipo == 1) {  /* se o tipo for 1 os bancos serao ordenados pela ordem de introducao no sistema com o respetivo nome e classificacao inP outP outV outVM inV e inVM */
		transacoes();
		for(i=0; i<posi; i++)
			printf("%d %s %d %d %d %d %d %d %d\n", bancos[i].referencia, bancos[i].nome,
												 	bancos[i].classificacao, bancos[i].inP, bancos[i].outP, 
												 	bancos[i].outV, bancos[i].outVM, bancos[i].inV, bancos[i].inVM);
		}
	else if (tipo == 2){  /* se o tipo for 2 o devera escrever a distribuicao do numero de bancos com exatamente k parceiros comerciais */
		int dk=0, k = 0, nbancos=0, i;		
		transacoes();			
		while(nbancos < posi){		/*executa o ciclo ate todos os bancos serem contados */
			dk=0;
			for (i=0; i<posi; i++){
				if(bancos[i].parceiros == k){		/*Calcula quantos bancos tem k parceiros*/
					dk++;
					nbancos++;
				}
			}
			if(dk!=0)		/*Se dk for diferente de 0 faz print do histograma*/
				printf("%d %d\n", k, dk);	
			k++;
		}
	}	
}

void saida(){  /* funcao selecionada pelo comando x, que escreve o numero de bancos registados seguido do numero total de 'bancos bons' */
	int i, bons = 0;
	for (i=0; i<posi ; i++)
		if (bancos[i].classificacao == BOM)
			bons++;
	printf("%d %d\n", posi, bons);
}
