#include <stdio.h>
#include <stdlib.h>

typedef struct adj{
	int id;
	struct adj *prox;
} Adj;

void build_adj(Adj *vet_adj, int u, int v, int p);
void build_adj_t(Adj *vet_adj1, Adj *vet_adj2, int n);
int dfs(Adj *vet_adj, int n, int r, char *cor, int *pred, int *d, int *f);
void dfs_aux(int v, int *tempo, Adj *vet_adj, char *cor, int *pred, int *d, int *f);
void free_adj(Adj* adj);
void print(Adj *vet_adj, int n);

int main(){
	int i, n, m, u, v, p, fort_conex;
	Adj vet_adj1[2000], vet_adj2[2000]; //vet_adj1 = Grafo    vet_adj2 = Grafo transposto
	
	while(1){
		char cor[2000];
		int pred[2000], d[2000], f[2000];
		
		scanf("%d %d", &n, &m);

		if(n==0 && m==0)
			break;
		
		for (i = 0; i < n; i++){
			vet_adj1[i].id = i;
			vet_adj1[i].prox = NULL;
			vet_adj2[i].id = i;
			vet_adj2[i].prox = NULL;
		}	
		
		for (i = 0; i < m; i++){
			scanf("%d %d %d", &u, &v, &p);
			build_adj(vet_adj1, u-1, v-1, p);
		}

		fort_conex = dfs(vet_adj1, n, 0, cor, pred, d, f);
		
		if (fort_conex == 1){
			build_adj_t(vet_adj1, vet_adj2, n);
			fort_conex = dfs(vet_adj2, n, 0, cor, pred, d, f);
		}
			
			
		printf("%d\n", fort_conex);
		
		for (i = 0; i < n; i++){
			if(vet_adj1[i].prox != NULL)				
				free_adj(vet_adj1[i].prox);
				
			if(vet_adj2[i].prox != NULL)				
				free_adj(vet_adj2[i].prox);
		}
	}
	
	return (0);
}


void build_adj(Adj *vet_adj1, int u, int v, int p){
	Adj *vaux;
	
	/************ u para v ************/
	/***** vet_adj1 *****/
	vaux = &(vet_adj1[u]);
	while (vaux->prox != NULL){
		vaux = vaux->prox;
	}
	
	vaux->prox = (Adj *) malloc(sizeof(Adj));
	vaux->prox->id = v;
	vaux->prox->prox = NULL;
	
	/************ v para u ************/
	if(p == 2){
		/***** vet_adj1 *****/
		vaux = &(vet_adj1[v]);
		while (vaux->prox != NULL){
			vaux = vaux->prox;
		}
	
		vaux->prox = (Adj *) malloc(sizeof(Adj));
		vaux->prox->id = u;
		vaux->prox->prox = NULL;
	}
}

void build_adj_t(Adj *vet_adj1, Adj *vet_adj2, int n){
	int i;
	Adj *vaux, *vaux2;

	for (i = 0; i < n; i++){
		vaux = vet_adj1[i].prox;
		while (vaux != NULL){
			vaux2 = &(vet_adj2[vaux->id]);
			while (vaux2->prox != NULL){
				vaux2 = vaux2->prox;
			}
			
			vaux2->prox = (Adj *) malloc(sizeof(Adj));
			vaux2->prox->id = vet_adj1[i].id;
			vaux2->prox->prox = NULL;
			
			vaux = vaux->prox;
		}
	}
}

void print(Adj *vet_adj, int n){
	int i;
	Adj *aux;
	
	for(i = 0; i < n; i++){
		printf("No %d: ", i);
		aux = vet_adj[i].prox;
		while(aux != NULL){
			printf("%d ", aux->id);
			aux = aux->prox;
		}
		printf("\n");
	}
}


int dfs(Adj *vet_adj, int n, int r, char *cor, int *pred, int *d, int *f){
	int v, tempo = 0;

	/************ INICIALIZACOES ************/
	for(v = 0; v < n; v++){
		cor[v] = 'b';
		pred[v] = -1;
	}
	
	dfs_aux(0, &tempo, vet_adj, cor, pred, d, f);
	
	for (v = 0; v < n; v++)
		if (cor[v] == 'b')
			return 0;
					
	return 1;
}

void dfs_aux(int v, int *tempo, Adj *vet_adj, char *cor, int *pred, int *d, int *f){
	Adj *aux;
	
	cor[v] = 'c';
	d[v] = *tempo;
	(*tempo)++;
	
	aux = vet_adj[v].prox;
	
	while(aux != NULL){
		if(cor[aux->id] == 'b'){
			pred[aux->id] = v;
			dfs_aux(aux->id, tempo, vet_adj, cor, pred, d, f);	
		}
		aux = aux->prox;
	}
	
	cor[v] = 'p';
	f[v] = *tempo;
	(*tempo)++;
}

void free_adj(Adj* adj){
	if (adj->prox != NULL)
		free_adj(adj->prox);
	
	free(adj);
}
