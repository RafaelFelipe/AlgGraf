#include<stdio.h>
#include <stdlib.h>
typedef struct listaAdj {
	int *adj;
	int numAdj;
	int pred;
	int dist;
	int visit;	
}ListaAdj;

int buscaProfundidade(ListaAdj grafo[], int n, int u, int time);

int main(){
	int n, m, i, u, v, max = 0;
	while(1){
		max = 0;
		scanf("%d %d", &n, &m);
		if(m == 0 && n == 0){
			return 0;
		}
		ListaAdj *grafo =  (ListaAdj *) malloc(sizeof(ListaAdj)*n);
		for(i = 0; i < n; i++){
			grafo[i].adj = (int *) malloc (sizeof(int)*(n-1));
			//grafo[i].pred = i;
			grafo[i].numAdj = 0;
			grafo[i].dist = -1;
			grafo[i].visit = 0;
		}
		for(i = 0; i < m; i++){
			scanf("%d %d", &u, &v);
			grafo[u].adj[grafo[u].numAdj] = v;
			grafo[u].numAdj++;
			grafo[v].adj[grafo[v].numAdj] = u;
			grafo[v].numAdj++;

		}
		//for(i = 0 ; i < n; i++){
		//	if(grafo[i].visit == 0)
		buscaProfundidade(grafo, n, 0,0);		
		//}
		for(i = 0; i < n; i++){
			if(grafo[i].dist > max){
				max = grafo[i].dist;
			}
			if(grafo[i].dist == -1){
				max = -1;
				break;
			}
			//printf("%d, ", grafo[i].dist);
		}
		//printf("\n");
		if(max == -1){
			printf("infinito\n");
		}else{
			printf("%d\n", max);
		}
		for(i = 0; i < n; i++){
			free(grafo[i].adj);
		}
		free(grafo);

	}
	return 0;
}
int buscaProfundidade(ListaAdj grafo[], int n, int u, int time){
	int v;
	grafo[u].visit = 1;
	grafo[u].dist = time;
	time++;
	
	for(int i = 0; i < grafo[u].numAdj ;i++){
		v = grafo[u].adj[i];
		if(grafo[v].visit == 0){
			grafo[v].pred = u;
			buscaProfundidade(grafo, n, v, time);
		}else{
			if(time < grafo[v].dist){
				//printf("v = %d time = %d dist = %d\n", v, time, grafo[v].dist);
				grafo[v].dist = time;
				buscaProfundidade(grafo, n, v, time);
			}
		}
	}
	grafo[u].visit++;

	return 1;
}