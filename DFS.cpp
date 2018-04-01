#include <stdio.h>
#include <stdlib.h>


 struct nod{
	int k;
	int viz;
	struct nodList *lista;
};

 struct nodList{
	struct nod *v;
	struct nodList *next;
};
 typedef struct nod nod;
 typedef struct Node Node;
 int j = 5;
int l[10000];

nod* newNod(int key){
	nod *p = (nod*)malloc(sizeof(nod));
	p->k = key;
	p->viz = 0;
	p->lista = NULL;
	return p;
}

void newMuchie(nod *a, nod *b){
	nodList *p = (nodList*)malloc(sizeof(nodList));
	p->v = b;
	p->next = a->lista;
	a->lista = p;
}


void connect(nod *a, nod* b){
	newMuchie(a, b);
	//newMuchie(b, a);
}

void dfs_visit(nod *v, int* count){
	nodList *p = v->lista;

	v->viz = ++(*count);
	printf("Nod vizitat = %d\n",v->k);
	while(p){
		if(!p->v->viz){
			dfs_visit(p->v, count);
		}
		p = p->next;

	}

}

void dfs_visit_top(nod *v, int* count){
	nodList *p = v->lista;
	
	
	v->viz = ++(*count);
	//printf("Nod vizitat = %d\n",v->k);
	while(p){
		if(!p->v->viz){
			dfs_visit_top(p->v, count);
		}
		p = p->next;
	
	}
//	printf("%d ",j);
	l[j] = v->k;
	j--;

}

void dfs(nod *G[], int n){
	int i;
	int count = 0;

	for(i = 0; i < n; i++){
		G[i]->viz = 0;
	}

	for (i = 0; i < n; i++){
		if (G[i]->viz == 0)
			dfs_visit(G[i], &count);
	}
}

void dfs1(nod *G[], int n){
	int i;
	int count = 0;

	for(i = 0; i < n; i++){
		G[i]->viz = 0;
	}

	for (i = 0; i < n; i++){
		if (G[i]->viz == 0)
			dfs_visit_top(G[i], &count);
	}
}

int main(){

	nod *G[6] = {newNod(1),newNod(2),newNod(3),newNod(4),newNod(5),newNod(6)};
	/*
	connect(G[0],G[2]);
	connect(G[0],G[1]);
	connect(G[1],G[2]);
	connect(G[2],G[3]);
	connect(G[4],G[3]);
	connect(G[4],G[5]);
	connect(G[5],G[5]);
	connect(G[3],G[1]);
	*/
	connect(G[0],G[3]);
	connect(G[0],G[4]);
	connect(G[4],G[2]);
	connect(G[2],G[1]);
	connect(G[5],G[5]);
	connect(G[4],G[5]);
	
	printf("DFS:\n");
	dfs(G,6);
	printf("\n\n\n");
	printf("Sortare topologica\n");
	dfs1(G,6);
	for(int i =0;i < 6; i++){
		printf("%d   ",l[i]);
	}
	
	getchar();
	return 0;
}
