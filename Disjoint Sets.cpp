#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("asdf");

typedef struct node{
	int val;
	int rank;
	struct node *p;
}nod;


typedef struct m{
	int s,d;
	int cost;
}muchie;


void make_set(nod *x){
	x->rank = 0;
	x->p = x;
	
}

void link(nod *x, nod *y,int n){
	profiler.countOperation("Total",n,1);
	if (x->rank > y->rank)
		y->p = x;
	else{
		profiler.countOperation("Total",n,2);
		x->p = y;
		if (x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}

nod* find_set(nod *x, int n){
	profiler.countOperation("Total",n,1);
	if (x->p != x){
		profiler.countOperation("Total",n,1);
		x->p = find_set(x->p,n);
	}

	return x->p;
}

void unionn(nod *x, nod *y,int n){
	link(find_set(x,n),find_set(y,n),n);
}

muchie* generare_muchii(int n){
	int i;
	int j;
	int nu_muchie = 0;
	int b[2];
	int dreapta,stanga;

	int  *c = (int*) malloc(sizeof(int) * n * 3 + 4);

	muchie *m = (muchie*)malloc(sizeof(muchie) * n * 4);

	int **mat_adiac = (int**)malloc(sizeof(int*) * n);

	for (int i = 0 ; i < n; i++)
		mat_adiac[i] = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			mat_adiac[i][j] = 0;
	
	int *v = (int*)malloc(sizeof(int) * n);
	FillRandomArray(v,n,1,100,false,0);
	for (i = 0; i < n-1; i++){
		m[i].d = i;
		m[i].s = i + 1;
		m[i].cost = v[i];
		mat_adiac[i][i+1] = v[i];
		
		mat_adiac[i+1][i] = v[i];
	}
	m[n-1].d = n-1;
	m[n-1].s = 0;
	m[n-1].cost = v[n-1];

	mat_adiac[0][n-1] = v[n-1];
	
	mat_adiac[n-1][0] = v[n-1];
	
	FillRandomArray(c,3*n + 1, 1, 100, false, 0);
	
	for(i = 0; i <= n*3; i++){
		nu_muchie = 0;
		while(nu_muchie == 0){
			
			FillRandomArray(b, 2, 0, n-1, true, 0);
			
			
			if (mat_adiac[b[0]][b[1]] == 0 && mat_adiac[b[1]][b[0]] == 0){
				
				nu_muchie = 1;
				
				if (b[0] < b[1]){
					dreapta = b[0];
					stanga = b[1];
				}
				else{
					dreapta = b[1];
					stanga = b[0];
				}
				
				mat_adiac[dreapta][stanga] = c[i];
				mat_adiac[stanga][dreapta] = c[i];
				m[n-1+i].d = dreapta;
				m[n-1+i].s = stanga;
				m[n-1+i].cost = c[i];
			}

		}
	}

	//pt demo
	/*
	for (i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			printf("%d ", mat_adiac[i][j]);
		printf("\n");	
	}
printf("\n\n\n");
*/

	for (int i = 0; i < n; i++)
		free(mat_adiac[i]);
	free(mat_adiac);
	free(v);
	free(c);
	return m;
}

int partition(muchie *a, int st, int dr,int n) {
	profiler.countOperation("Total",n,1);
	muchie pivot = a[dr];
	muchie aux;
	int i = st - 1;
	for (int j = st; j < dr; j++) {
	profiler.countOperation("Total",n,1);
		if (a[j].cost <= pivot.cost) {
			profiler.countOperation("Total",n,3);
			i++;
			aux = a[i];
			a[i] = a[j];
			a[j] = aux;
		}
	}
	profiler.countOperation("Total",n,3);
	aux = a[dr];
	a[dr] = a[i + 1];
	a[i + 1] = aux;
	return i + 1;
}

void quick_sort(muchie *a, int st, int dr,int n) {
	profiler.countOperation("Total",n,1);
	if (st < dr) {
		int q = partition(a, st, dr,n);
		quick_sort(a, st, q - 1,n);
		quick_sort(a, q + 1, dr,n);
	}
}

void mst_kruskal(int n, muchie *m){
	node **k = (node**)malloc(sizeof(node) * n);
	
	int j = 0;
	int i;
	for(i = 0; i < n; i++){
		k[i] = (node*)malloc(sizeof(node));
		k[i]->val = i;
		make_set(k[i]);
	}
	quick_sort(m, 0, 4*n - 1, n);
	
	

	for(i = 0; i < 4*n; i++){
		//profiler.countOperation("Total",n,1);

		if(find_set(k[m[i].d],n) != find_set(k[m[i].s],n)){
			unionn(k[m[i].d],k[m[i].s],n);
			//pt demo
			printf("%d  %d  %d\n",k[m[i].d]->val,k[m[i].s]->val,m[i].cost);
		}
	}
	
	
	for(i = 0; i < n; i++)
		free(k[i]);

}


int main(){
	
	muchie *muc;
	node **m;
/*	
	for(int i = 100; i < 10000; i=i+100){
		printf("%d\n",i);
		muc = generare_muchii(i);
		mst_kruskal(i,muc);
		free(muc);
	}
	profiler.showReport();
*/
	//pt demo

	muc = generare_muchii(10);
	 mst_kruskal(10,muc);
	

	getchar();



return 0;
}