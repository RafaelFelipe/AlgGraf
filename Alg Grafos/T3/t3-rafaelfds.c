//Rafael Felipe Dias dos Santos
//726582
#include <stdlib.h>
#include <stdio.h>

#define BRANCO	0
#define CINZA	1
#define PRETO	2

typedef struct adj{
	int pos, con;
	struct adj *prox;
} Adj;

typedef struct adjaux{
	Adj *first, *last;
} AdjAux;

int DFS(Adj *adj, int n);
void DFSLoop(int *cor, int *d, int *f, int *pred, Adj *adj, int n, int *clock, int r);
int DFSCheck(Adj *adj, int n);
void InitAdjv(Adj *adj, int m, AdjAux *adjx);
void Clean(Adj *adj, int n);

void printAdj(Adj *adj, int n);

int main(){
	int n, m, i;
	Adj adj[2000];
	AdjAux adjx[2000];


	scanf("%d %d", &n, &m);

	while(!(n==0 && m==0)){

		for(i=0;i<n;i++){
			adj[i].pos = -1;
			adj[i].prox = NULL;
			adjx[i].first = &(adj[i]);
			adjx[i].last = adjx[i].first;
		}

		InitAdjv(adj, m, adjx);

		//printf("%d \n", m);
		//printAdj(adj, n);

		if(DFS(adj, n))	
			printf("%d\n", DFSCheck(adj, n));
		else
			printf("0\n");
		Clean(adj, n);

		scanf("%d %d", &n, &m);
	}
	return 0;
}

void InitAdjv(Adj *adj, int m, AdjAux *adjx){
	int i, u, v, p;
	Adj *aux;

	for(i=0; i<m; i++){
		scanf("%d %d %d", &u, &v, &p);
		//ajustando os valores
		u--;
		v--;
		//a posição u já tem adjacente
		if(adj[u].pos != -1){
			//caso tenha mais de um adjacente
			aux = adjx[u].last;
			aux->prox = (Adj *) malloc(sizeof (Adj));
			aux->prox->pos = v;
			aux->prox->con = p;
			aux->prox->prox = NULL;	
			adjx[u].last = aux->prox;
		}
		//a posição u ainda não tinha adjacente
		else{
			adj[u].pos = v;
			adj[u].con = p;
			adj[u].prox = NULL;
		}
		// caso seja uma via de duas mão
		if(p == 2){
			//a posição v já tem adjacente
			if(adj[v].pos != -1){
				aux= adjx[v].last;
				aux->prox = (Adj *) malloc(sizeof (Adj));
				aux->prox->pos = u;
				aux->prox->con = p;
				aux->prox->prox = NULL;
				adjx[v].last = aux->prox;	
			}
			//a posição v ainda não tinha adjacente
			else{
				adj[v].pos = u;
				adj[v].con = p;
				adj[v].prox = NULL;
			}
		}
	}
}

int DFS(Adj *adj, int n){
	int i, clock=0;
	int cor[2000], d[2000], f[2000], pred[2000];
	
	for(i=0; ++i<n;){
			cor[i] = BRANCO;
			pred[i] = -1;
	}

	DFSLoop(cor, d, f, pred, adj, n, &clock, 0);

	for(i=0; i<n; i++)
		if(cor[i] == BRANCO)
			return 0;
	return 1;						
}

int DFSCheck(Adj *adj, int n){
	int i, atual;
	Adj adj2[2000], *aux, *aux2;
	//inicializando o grafo T
	for(i=0; i<n; i++){
		adj2[i].pos = -1;
		adj2[i].prox = NULL;
	}
	//populando o grafo T EEEEERRROOOOOOOOOO
	for(i=0; ++i<n;){
		for(aux2 = &(adj[i]); aux2 != NULL; aux2 = aux2->prox){
			atual = aux2->pos;
			if(adj2[atual].pos != -1){
				//caso tenha mais de um adjacente
				if(adj2[atual].prox != NULL){
					aux = adj2[atual].prox;
					while(aux->prox != NULL)
						aux = aux->prox;
					aux->prox = (Adj *) malloc(sizeof (Adj));
					aux->prox->pos = i;
					aux->prox->con = aux2->con;
					aux->prox->prox = NULL;	
				}
				else{
					adj2[atual].prox = (Adj *) malloc(sizeof (Adj));
					adj2[atual].prox->pos = i;
					adj2[atual].prox->con = aux2->con;
					adj2[atual].prox->prox = NULL;	
				}
			}
			//a posição atual ainda não tinha adjacente
			else{
				adj2[atual].pos = i;
				adj2[atual].con = aux2->con;
			}
		}
	}
	i = DFS(adj2, n);
	Clean(adj2, n);
	return i;
}

void DFSLoop(int *cor, int *d, int *f, int *pred, Adj *adj, int n, int *clock, int r){
	int i;
	Adj *aux;

	cor[r] = CINZA;
	d[r] = *clock;
	*clock = *clock + 1;

	//caso tenha adjacentes
	for(aux = &(adj[r]); aux!=NULL && aux->pos != -1; aux = aux->prox)
		if(cor[aux->pos] == BRANCO){
			pred[aux->pos] = r;
			DFSLoop(cor, d, f, pred, adj, n, clock, aux->pos);
		}
	//terminado a busca nos adjacentes
	cor[r] = PRETO;
	f[r] = *clock;
	*clock = *clock + 1;
}

void Clean (Adj *adj, int n){
	int i;
	Adj *aux1, *aux2;

	for(i=0; i<n; i++)
		if(adj[i].prox != NULL){
			aux1 = adj[i].prox;
			aux2 = aux1->prox;

			while(aux2 != NULL){
				free(aux1);
				aux1 = aux2;
				aux2 = aux1->prox;
			}
			free(aux1);
		}
}

void printAdj(Adj *adj, int n){
	int i;
	Adj *aux;

	for(i=0; i<n; i++){
		printf("\n%d -> ", i);

		if(adj[i].pos != -1){
			printf("%d-%d ; ", adj[i].pos, adj[i].con);
			aux = adj[i].prox;
			while(aux != NULL){
				printf("%d-%d ;", aux->pos, aux->con);
				aux = aux->prox;
			}
		}
	}
	printf("\n");
}