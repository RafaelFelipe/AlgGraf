//Rafael Felipe Dias dos Santos
//726582
#include <stdlib.h>
#include <stdio.h>

typedef struct adj{
	int pos;
	struct adj *prox;
} Adj;

typedef enum {false, true} bool;

typedef struct no{
	int price, total;
	bool done;
	struct adj *P, *last;
} No;

/*
Retorna 
*Srch é o nó que será investigado
type indica se é busca por unlockers(pais) ou unlockeds(filhos) 
*/
int HvrSearch(No *works, int n, int Srch);
void InitAdjv(No *works, int m);
void Clean(No *works, int n);

int main(){
	No works[6000];
	int i, n, m;

	scanf("%d %d", &n, &m);

	while(!(n==0 && m==0)){

		for(i=0;i<n;i++){
			scanf("%d ", &works[i].price);
			works[i].P = (Adj *) malloc(sizeof (Adj));
			works[i].P->pos = -1;
			works[i].P->prox = NULL;
			works[i].last = works[i].P;
			works[i].total = 0;
			works[i].done = false;
		}

		InitAdjv(works, m);

		printf("%d\n",HvrSearch(works, n, -1));

		scanf("%d %d", &n, &m);		
	}
}

void InitAdjv(No *works, int m){
	int i, u, v;
	Adj *aux;

	for(i=0; i<m; i++){
		scanf("%d %d", &u, &v);		
		//inserindo o pai de v
		if(works[v].P->pos == -1)//caso seja o primeiro pai
			works[v].P->pos = u;
		else{
			aux = works[v].last;
			aux->prox = (Adj *) malloc(sizeof (Adj));
			aux->prox->pos = u;
			aux->prox->prox = NULL;
			works[v].last = aux->prox;
		}
	}
}

int HvrSearch(No *works, int n, int Srch){
	int i, max=0;
	Adj *aux;

	//caso seja o inicio da busca
	if(Srch == -1){
		for(i=0; i<n; i++)
			if(works[i].done == false)
				max = (max < (HvrSearch(works, n, i))) ? (HvrSearch(works, n, i)) : max;					

		return max;
	}

	else{
		//caso esse trabalho já esteja concluido
		if(works[Srch].done == true){
			return works[Srch].total;
		}
		//caso não tenha pai
		if(works[Srch].P->pos == -1){
			works[Srch].done = true;
			works[Srch].total = works[Srch].price; 
			return works[Srch].total;
		}
		//caso tenha pelo menos um pai
		else{
			aux = works[Srch].P;
			max = HvrSearch(works, n, aux->pos)+works[Srch].price;
			if(aux->prox != NULL){
				do{
					aux = aux->prox;
					i = aux->pos;
					max = (max < (HvrSearch(works, n, i)+works[Srch].price)) ? (HvrSearch(works, n, i)+works[Srch].price) : max;		
				}while(aux!=works[Srch].last);
			}
			works[Srch].total = max;
			works[Srch].done = true;
			return max;
		}
	}
}

void Clean(No *works, int n){
	int i;
	Adj *aux1, *aux2;

	for(i=0; i<n; i++){
		aux1 = works[i].P;
		if(works[i].P->pos != -1){
			aux2 = aux1->prox;
			while(aux2 != NULL){
				free(aux1);
				aux1 = aux2;
				aux2 = aux1->prox;
			}
		}
		free(aux1);
	}
		
}