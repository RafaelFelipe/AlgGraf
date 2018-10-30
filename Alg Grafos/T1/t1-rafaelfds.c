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

void BFS(int *cor,int *dist,int *pred,int *line,int *party,Adj *adj, int n, int r);
void InitAdjv(Adj *adj, int m);
void Clean(Adj *adj, int n);

void printAdj(Adj *adj, int n);

int main(){
	int n, m, i;
	int cor[2000], dist[2000], pred[2000], line[2000], party[2000];
	Adj adj[2000];

	scanf("%d %d", &n, &m);

	while(!(n==0 && m==0)){
		for(i=0; i<n; i++){
			cor[i] = BRANCO;
			dist[i] = -1;
			pred[i] = -1;
			line[i] = -1;
			party[i] = -1;
			adj[i].pos = -1;
		}

		InitAdjv(adj, m);

		//printf("%d \n", m);
		//printAdj(adj, n);

		BFS(cor, dist, pred, line, party, adj, n, 0);		
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
		u--;
		v--;
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

void BFS(int *cor,int *dist,int *pred,int *line,int *party,Adj *adj, int n, int r){
	int i, atual, flag=0;
	int first=0, next=0;
	Adj *aux;

	dist[r] = 0;
	cor[r] = CINZA;
	pred[r] = -1;

	if(party[r] == -1)
		party[r] = AZUL;

	line[next++] = r;
	//enquanto a fila estiver vazia
	while(first != next){
		atual = line[first++]; //removendo a raiz da fila
		//caso tenha adjacentes
		if(adj[atual].pos != -1){
			if(party[adj[atual].pos] == party[atual]){//verificando bipartição
				printf("NAO\n");
				return;
			}
			if(cor[adj[atual].pos] == BRANCO){
				if(party[atual] == VERDE)
					party[adj[atual].pos] = AZUL;
				else
					party[adj[atual].pos] = VERDE;
				dist[adj[atual].pos] = dist[atual]+1;
				pred[adj[atual].pos] = atual;
				cor[adj[atual].pos] = CINZA;
				line[next++] = adj[atual].pos;
			}
			for(aux = adj[atual].prox; aux!=NULL; aux = aux->prox){
				if(party[aux->pos] == party[atual]){//verificando bipartição
					printf("NAO\n");
					return;
				}
				if(cor[aux->pos] == BRANCO){
					if(party[atual] == VERDE)
						party[aux->pos] = AZUL;
					else
						party[aux->pos] = VERDE;
					dist[aux->pos] = dist[atual]+1;
					pred[aux->pos] = atual;
					cor[aux->pos] = CINZA;
					line[next++] = aux->pos;
				}
			}
		}
		cor[atual] = PRETO;
	}
	//verificando se todos os nós foram visitados
	for(i=0; i<n && !flag; i++)
		if(cor[i] == BRANCO)
			flag = 1;
	if(flag)
		BFS(cor, dist, pred, line, party, adj, n, --i);		
	else
		printf("SIM\n");
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