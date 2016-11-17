#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DIM 11

/*-----------------------------------------------------------------------------------------------------
---------------------------------------------ESTRUTURA-------------------------------------------------
------------------------------------------------------------------------------------------------------*/

/*estrutura referente aos clientes, sendo ref, a referencia, nche, o numero de cheques emitidos, 
vche, o valor de cheques emitido, nchb, o número de cheques de que foi beneficiario, vchb, o 
valor dos cheques de que foi beneficiario*/

typedef struct {                  
	long int ref;
	int nche, vche, nchb, vchb;
}clientes;

/*Ponteiro para a estrutura node*/

typedef struct node* link;

/*estrutura que contem a informacao do cliente, a profundidade da arvore e os ponteiros que apontam
para o proximo no filho (direita e esquerda)*/

struct node{
	int height;
	clientes client;
	struct node *l;
	struct node *r;
};

/*estrutura referente as cheques, sendo refc, a referencia do cheque, refe, a referencia do emissor, 
refb a referencia do benificiario e valor, o valor do cheque */

typedef struct {
	long int refc, refe, refb;
	int valor;
}cheques;

/*Ponteiro para a estrutura queueCh*/

typedef struct fc* queueCh;

/*estrutura como o ponteiro que aponta para o proximo cheque da fila de ponteiros e o cheque*/

struct fc{
	queueCh next;
	cheques cheque;
};

/*-----------------------------------------------------------------------------------------------------
-----------------------------------------VARIAVEIS-----------------------------------------------------
------------------------------------------------------------------------------------------------------*/

/*Variaveis globais referentes a cabeca e a cauda da fila de cheques e a cabeca da arvore*/

static queueCh head, tail;
static link arv;

/*--------------------------------------------CODIGO---------------------------------------------*/

/*inicializacao da arvore de procura e respetivamente cabeca e cauda*/

void init(){
	head = NULL;
	tail = NULL;
	arv = NULL;
}

/*funcao que calcula a altura do no da arvore*/ 

int height(link h){						
	if (h == NULL) 
		return 0;
	return h->height;
}

/*rotação da arvore para a esquerda*/ 

link rotL(link h){ 					
	int height_left, height_right;
	link x = h->r;
	h->r = x->l;
	x->l = h;
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x;
}

/*rotação da arvore para a  direita*/ 

link rotR(link h){ 					
	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x;
}

/*rotação dupla esquerda direita*/

link rotLR(link h){ 				
	if (h==NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}

/*rotação dupla direita esquerda*/

link rotRL(link h){ 				
	if (h == NULL) 
		return h;
	h->r = rotR(h->r);
	return rotL(h);
}

/*Balance factor da arvore*/

int Balance(link h) {				
	if(h == NULL) 
		return 0;
	return height(h->l) - height(h->r);
}

/*verifica qual e o banco com a maior referencia*/ 

link max(link h){ 						
	if(h == NULL || h->r==NULL)
		return h;
	else
		return max(h->r);
}

/*verifica qual e o banco com a menor referencia*/

link min(link h) { 						
	if (h==NULL || h->l==NULL) return h;
		else return min(h->l);
}

/*Equilibra a arvore*/

link AVLbalance(link h) {  			
	int balanceFactor;
	if (h==NULL) 
		return h;
	balanceFactor = Balance(h);
	if(balanceFactor>1) {
		if (Balance(h->l)>0) 
			h=rotR(h);
		else
			h=rotLR(h);
	}
	else if(balanceFactor<-1){
		if (Balance(h->r)<0) 
			h = rotL(h);
		else
			h = rotRL(h);
	}
	else{
		int height_left = height(h->l);
		int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	}
return h;
}

/*cria um cliente*/

link newCl(clientes client, link l, link r){      
	link x = (link)malloc(sizeof(struct node));   /*alocacao de memoria para um novo no*/
	x->client = client;
	x->l = l;
	x->r = r;
	x->height=1;
	return x;
}

/*cria um cheque e alocacao de memoria para um novo "bloco" da fila do cheque*/

queueCh newCh(cheques cheque, queueCh next){       
	queueCh x = (queueCh) malloc(sizeof(struct fc));
 	x->cheque = cheque;
	x->next = next;
	return x;
}

/*inicializa a cabeca da fila de cheques a NULL*/

int queueChEmpty(){                                  
	return head == NULL;
}

/*insere o cheque na fila de cheques pelo fim(tail)*/

void insertCh(cheques cheque){                       
	if (queueChEmpty()){
 		queueCh x = newCh(cheque, NULL);
 		x->next = head;
 		head=x;
 		tail=x;
 	}
	else{
		tail->next = newCh(cheque, NULL);
		tail = tail->next;
	}
}

/*remove o cheque da da fila de cheques dependendo da posicao onde esta*/

void removeCh(queueCh check){                         
	queueCh t, prev, aux;
	if((check->cheque).refc == (head->cheque).refc){
		aux = head->next;
		free(head);
		head = aux;
	}
	else{
		for(t = head, prev = NULL; t != NULL; prev = t, t = t->next){
			if((check->cheque).refc == (t->cheque).refc){
				if((check->cheque).refc == (tail->cheque).refc){
					free(tail);
					tail=prev;
					tail->next=NULL;
				}
				else{
					prev->next= t->next;
					free(t);
					return;
				}
			}
		}
	}
}

/*funcao que insere um cliente na arvore*/

link insertR(link h, clientes client){   
	if (h == NULL)
		return newCl(client, NULL, NULL);
	if ((client.ref) < ((h->client).ref))
		h->l = insertR(h->l, client);
	else
		h->r = insertR(h->r, client);
	h = AVLbalance(h);
	return h;
}

/*Funcao que apaga o no da arvore e o free da memoria alocada do mesmo*/

link deleteTree(link h, long int k){
	clientes cliente = h->client;
	if (h == NULL) 
		return h;
	else if (k < (cliente.ref)) 
		h->l = deleteTree(h->l,k);
	else if ((cliente.ref) < k)
		h->r = deleteTree(h->r,k) ;
	else{
		if (h->l !=NULL && h->r !=NULL){
			link aux = max(h->l);
			{clientes x; x = h->client; h->client = aux->client; aux->client = x;}
			h->l = deleteTree(h->l, (aux->client).ref);
		}
		else {
			link aux = h;

			if (h->l == NULL && h->r == NULL) 
				h=NULL;
			else if (h->l == NULL) 
				h = h->r;
			else 
				h = h->l;
			free(aux);
		}
	}
	h = AVLbalance(h);
	return h;
}

/*Remove completamente a arvore libertando toda a memoria alocada*/

link freeTree (link h)
{
  if (h==NULL)
    return h;
  h->l=freeTree(h->l);
  h->r=freeTree(h->r);
  return deleteTree (h,(h->client).ref);
}

/*funcao que procura um cliente atraves da referencia*/

link searchCl(link h, long int ref) {     
 	if (h == NULL)
 		return NULL;
 	if (ref == (h->client).ref)
 		return h;
 	if (ref < (h->client).ref)
 		return searchCl(h->l, ref);
 	else
 		return searchCl(h->r, ref);
}

/*funcao que procura um cheque atraves da referencia*/

queueCh searchCh(long int n){        
 	queueCh t;
 	for(t = head; t!=NULL; t = t->next){
 		if((t->cheque).refc == n)
 			return t;
 	}
 	return NULL;
}

/*conta o numero de clientes activos*/

int count_act(link h) {				
	if (h==NULL) 
		return 0;
	else{
		if((h->client).nche !=0 || (h->client).nchb !=0)
			return count_act(h->r) + count_act(h->l) + 1;
		else
			return count_act(h->r) + count_act(h->l);
	}
}

/*funcao que actualiza a arvore ou cria um novo cliente*/

void verify_add(long int refe, long int refb, cheques cheque){    
	link noemissor, nobenif;
	clientes cliente1, cliente2;
	noemissor=searchCl(arv, refe);
	if(noemissor == NULL){
		cliente1.ref = cheque.refe;
		cliente1.nche = 1;
		cliente1.vche = cheque.valor;
		cliente1.nchb = 0;
		cliente1.vchb = 0;
		arv=insertR(arv, cliente1);
	}
	else{
		(noemissor->client).nche++;
		(noemissor->client).vche += cheque.valor;
	}
	nobenif=searchCl(arv, refb);
	if(nobenif == NULL){
		cliente2.ref = cheque.refb;
		cliente2.nche = 0;
		cliente2.vche = 0;
		cliente2.nchb = 1;
		cliente2.vchb = cheque.valor;
		arv=insertR(arv, cliente2);
	}
	else{
		(nobenif->client).nchb++;
		(nobenif->client).vchb += cheque.valor;
	}
}

/*funcao que recebe a referencia do cliente emissor e beneficiario
 e actualiza e possivelmente "remove" da arvore o cliente*/

void verify_remove(long int refe, long int refb, cheques cheque){ 
	link noemissor, nobenif;
	noemissor=searchCl(arv, refe);
	(noemissor->client).nche--;
	(noemissor->client).vche -= cheque.valor;
	nobenif=searchCl(arv, refb);
	(nobenif->client).nchb--;
	(nobenif->client).vchb -= cheque.valor;
}

/* funcao que recebe valor refe refb refc e adiciona um novo cheque à pool de cheques
 a processR e posteriormente atualiza a arvore dos clientes*/
	
void cheque(){    
	cheques cheque;
	int valor;
	long int refe, refb, refc;
	scanf("%d %ld %ld %ld", &valor, &refe, &refb, &refc);
	cheque.valor = valor;
	cheque.refe = refe;
	cheque.refb = refb;
	cheque.refc = refc;
	insertCh(cheque);
	verify_add(refe, refb, cheque);
}

/*processa o cheque emitido há mais tempo, e remove o da pool de cheques a processR*/

void process(){ 
	/*queueCh aux;*/
	if(head != NULL){
		/*aux=head;*/
		verify_remove((head->cheque).refe, (head->cheque).refb, head->cheque);
		removeCh(head);
	}
	else
		printf("Nothing to process\n");
}

/*processa o cheque com a referência refc, e remove o cheque da pool de cheques a processR*/

void processR(){ 

	long int ref;
	queueCh check;
	cheques cheque;
	scanf("%ld", &ref);
	check = searchCh(ref);
	if(check != NULL){
		cheque = check->cheque;
		verify_remove(cheque.refe, cheque.refb, cheque);
		removeCh(check);
	}
	else
		printf("Cheque %ld does not exist\n", ref);
}

/*imprime informação referente ao cheque com a referência refc*/

void infocheque(){ 
	long int ref;
	cheques cheque;
	queueCh check;
	scanf("%ld", &ref);
	check = searchCh(ref);
	if(check != NULL){
		cheque=check->cheque;
		printf("Cheque-info: %ld %d %ld --> %ld\n", cheque.refc, cheque.valor, cheque.refe, cheque.refb);
	}
}

/*Imprime a informação (sumarizada) referente ao cliente com a referência ref*/

void infocliente(){ 
	long int ref;
	link no;
	clientes cliente;
	scanf("%ld", &ref);
	no=searchCl(arv, ref);
	if(no != NULL){
		cliente=no->client;
		printf("Cliente-info: %ld %d %d %d %d\n", cliente.ref, cliente.nche, cliente.vche, cliente.nchb, cliente.vchb);
	}	
}

/*imprime a informacao de todos os clientes activos*/

void printTree(link h){
	if (h == NULL)
		return;
	printTree(h->l);
	if((h->client).nche !=0 || (h->client).nchb !=0)
		printf("*%ld %d %d %d %d\n", (h->client).ref, (h->client).nche, (h->client).vche, (h->client).nchb, (h->client).vchb);
	printTree(h->r);
}

/*Verifica se existe algum cliente ativo na arvore e impreme a informacao (sumarizada) de todos os clientes*/

void info(){ 
	if(count_act(arv) == 0)
		printf("No active clients\n");
	else
		printTree(arv);
}


/*Sai do programa e apaga toda a informação sobre o sistema*/ 

void sair(){ 
	int ncl, nch=0, vch=0;
	queueCh t = head, aux;
	ncl = count_act(arv);
	
	while(t != NULL){
		nch++;
		vch += (t->cheque).valor;
		aux = t;
		t = t -> next;
		free(aux);
	}
	printf("%d %d %d\n",ncl, nch, vch);
	freeTree(arv);
}

/*-----------------------------------------------------------------------------------------------------
-------------------------------------------------MAIN--------------------------------------------------
------------------------------------------------------------------------------------------------------*/

int main(){
	char command[DIM];
	scanf("%s", command);
	init();
	while (1) {
		
		if (strcmp("cheque", command) == 0){
			cheque();
		}
		else if(strcmp("processa", command) == 0){
			process();
		}
		else if(strcmp("processaR", command) == 0){
			processR();
		}
		else if(strcmp( "infocheque", command) == 0){
			infocheque();
		}
		else if( strcmp("infocliente", command) == 0){
			infocliente();
		}
		else if( strcmp("info", command) == 0){
			info();
		}
		else if(strcmp("sair", command) == 0){
			sair();
			return 0; 
		}
		else{
			printf("ERRO: Comando desconhecido\n");
		}
		scanf("%s", command);  
	}
	return 0; 
}

