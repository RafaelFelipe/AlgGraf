//Rafael Felipe Dias dos Santos
//726582
#include <stdlib.h>
#include <stdio.h>

#define BRANCO	2
#define CINZA	3
#define PRETO	4

#define AZUL	0
#define VERDE	1

typedef struct adj{
	int pos;
	struct adj *prox;
} Adj;

void BFS(int *cor,int *dist,int *pred,int *line,Adj *adj, int n, int r);
void InitAdjv(Adj *adj, int m);
void Clean(Adj *adj, int n);

void printAdj(Adj *adj, int n);

int main(){
	int n, m, i;
	int cor[1000], dist[1000], pred[1000], line[1000];
	Adj adj[1000];

	scanf("%d %d", &n, &m);

	while(!(n==0 && m==0)){
		for(i=0; i<n; i++){
			cor[i] = BRANCO;
			dist[i] = -1;
			pred[i] = -1;
			line[i] = -1;
			adj[i].pos = -1;
			adj[i].prox = NULL;
		}

		InitAdjv(adj, m);

		//printf("%d \n", m);
		//printAdj(adj, n);

		BFS(cor, dist, pred, line, adj, n, 0);	
		Clean(adj, n);

		scanf("%d %d", &n, &m);
	}
	return 0;
}

void InitAdjv(Adj *adj, int m){
	int i, u, v;
	Adj *aux;

	for(i=0; i<m; i++){
		scanf("%d %d", &u, &v);
		//ajustando os valores
		//u--;
		//v--;
		//a posição u já tem adjacente
		if(adj[u].pos != -1){
			//caso tenha mais de um adjacente
			if(adj[u].prox != NULL){
				aux = adj[u].prox;
				while(aux->prox != NULL)
					aux = aux->prox;
				aux->prox = (Adj *) malloc(sizeof (Adj));
				aux->prox->pos = v;
				aux->prox->prox = NULL;	
			}
			else{
				adj[u].prox = (Adj *) malloc(sizeof (Adj));
				adj[u].prox->pos = v;
				adj[u].prox->prox = NULL;	
			}
		}
		//a posição u ainda não tinha adjacente
		else{
			adj[u].pos = v;
			adj[u].prox = NULL;
		}

		//a posição v já tem adjacente
		if(adj[v].pos != -1){
			//caso tenha mais de um adjacente
			if(adj[v].prox != NULL){
				aux = adj[v].prox;
				while(aux->prox != NULL)
					aux = aux->prox;
				aux->prox = (Adj *) malloc(sizeof (Adj));
				aux->prox->pos = u;
				aux->prox->prox = NULL;	
			}
			else{
				adj[v].prox = (Adj *) malloc(sizeof (Adj));
				adj[v].prox->pos = u;
				adj[v].prox->prox = NULL;	
			}
		}
		//a posição v ainda não tinha adjacente
		else{
			adj[v].pos = u;
			adj[v].prox = NULL;
		}
	}
}

void BFS(int *cor,int *dist,int *pred,int *line,Adj *adj, int n, int r){
	int i, atual, maxDist = 0;
	int first=0, next=0;
	Adj *aux;

	dist[r] = 0;
	cor[r] = CINZA;
	pred[r] = -1;

	line[next++] = r;
	//enquanto a fila estiver vazia
	while(first != next){
		atual = line[first++]; //removendo a raiz da fila
		//caso tenha adjacentes
		if(adj[atual].pos != -1){
			if(cor[adj[atual].pos] == BRANCO){
				dist[adj[atual].pos] = dist[atual]+1;
				pred[adj[atual].pos] = atual;
				cor[adj[atual].pos] = CINZA;
				line[next++] = adj[atual].pos;
			}
			for(aux = adj[atual].prox; aux!=NULL; aux = aux->prox)
				if(cor[aux->pos] == BRANCO){
					dist[aux->pos] = dist[atual]+1;
					pred[aux->pos] = atual;
					cor[aux->pos] = CINZA;
					line[next++] = aux->pos;
				}
		}
		cor[atual] = PRETO;
	}
	//verificando se todos os nós foram visitados
	for(i=0; i<n; i++)
		if(cor[i] == BRANCO){
			printf("infinito\n");
			return;		
		}
		for(maxDist = 0, i=0; i<n; i++)
			if(dist[i] > maxDist)
				maxDist = dist[i];
		printf("%d\n", maxDist);
			
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
			printf("%d ", adj[i].pos);
			aux = adj[i].prox;
			while(aux != NULL){
				printf("%d ", aux->pos);
				aux = aux->prox;
			}
		}
	}
}