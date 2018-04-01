#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <queue>
#include "Profiler.h";

using namespace std;

Profiler profiler("Tema 9");

#define maxV 1000
#define maxE 4500

#define alb 1
#define gri 2
#define negru 3

struct nodL{
	int key;
	struct nodG *nodg;
	struct nodL *next;
};

struct nodG{
	int key;
	int dist;
	int color;
	nodG *p;
};


 
int e[190000];

nodG *vG[10000];


nodL *vL[10000];


queue<nodL*> q;

struct nodG* faNodG(int val){
	nodG* nod = (struct nodG*)malloc(sizeof(struct nodG));

	nod->key = val;
	nod->dist = -1;
	nod->color = alb;
	nod->p = NULL;

	return nod;
}

struct nodL* faNodL(int val){
	nodL* nod = (struct nodL*)malloc(sizeof(struct nodL));

	nod->key = val;
	nod->nodg = faNodG(val);
	nod->next = NULL;

	return nod;
}

void initializare(int muchii, int n){
	int i, r, m;
	m = (n*(n - 1)) / 2;

	for (i = 1; i < m + 1; i++)
		e[i] = 0;

	srand(time(NULL));
	i = 0;
	while (i < muchii){
		r = rand() % m + 1;
		if (e[r] == 0){
			e[r] = 1;
			i++;
		}
	}
}

void initializareG(int n){
	int i;
	for (i = 1; i < n + 1; i++){
		vG[i] = faNodG(i);
		vL[i] = faNodL(i);
		vL[i]->next = NULL;
	}
}

void creareListe(int n){
	int i, min, max;
	nodL*nodm = (struct nodL*)malloc(sizeof(struct nodL));
	nodL*nodM = (struct nodL*)malloc(sizeof(struct nodL));

	for (i = 1; i <= n*(n - 1) / 2; i++){
		if (e[i] == 1)
		for (min = 1; min < n; min++){
			max = i - n*(min - 1) + (min*(min - 1)) / 2 + min;
			if ((max>min) && (max < (n + 1))){
				nodm = vL[min];
				nodM = vL[max];
				
				while(1)
				{

					if (nodm->next == NULL)
					{
						nodm->next = faNodL(max);
						break;
					}

					else nodm = nodm->next;
				}

				while(1)
				{

					if (nodM->next == NULL)
					{
						nodM->next = faNodL(min);
						break;
					}

					else nodM = nodM->next;
				}
			}
		}
	}
}

void BFS(nodL *vL[], nodL *start, int n){
	nodL *u, *v;


	u = (struct nodL*)malloc(sizeof(struct nodL));
	v = (struct nodL*)malloc(sizeof(struct nodL));

	start->nodg->color = gri;
	start->nodg->dist = 0;
	start->nodg->p = NULL;
	profiler.countOperation("Total", n, 1);
	q.push(start);
	printf("Nod vizitat curent= %d\n",start->key);
	while (q.empty() == false)
	{
		profiler.countOperation("Total", n, 2);
		u = q.front();

		q.pop();

		v = vL[u->key];
		while (v != NULL)
		{
			profiler.countOperation("Total", n, 1);
			v = v->next;

			if (v != NULL)
			if (vL[v->key]->nodg->color == alb)
			{
				profiler.countOperation("Total", n, 4);
			
				printf("Nod vizitat curent= %d\n",v->key);
				vL[v->key]->nodg->color = gri;
				v->nodg->dist = u->nodg->dist + 1;
				v->nodg->p = u->nodg;
				q.push(v);
			}
		}

		profiler.countOperation("Total", n, 1);
		vL[u->key]->nodg->color = negru;
	}
}
void afisLista(nodL *vL[],int n){
		int i = 1;
		int j = 0;
		for(i = 1 ; i <= n; i++){
			nodL *p = vL[i];
			while(p != NULL){
				printf("%d  ",p->key);
				p = p->next;
		}
			printf("\n");
	}
}



void profil1(){
	initializareG(maxV);
	int i;
	for (i = 100; i <= 5000; i = i + 100){
		initializare(i, maxV);
		creareListe(maxV);
		BFS(vL, vL[5], i);
	}
}

void demo(){
	initializareG(5);
	int i;
	for (i = 5; i <= 5; i = i + 100){
		initializare(i, 5);
		creareListe(5);
		BFS(vL, vL[1], i);
	}
}

void profil2(){
	int i;
	for (i = 100; i <= 200; i = i + 10){
		initializareG(i);
		initializare(maxE, i);
		creareListe(i);
		
		BFS(vL, vL[6], i);
	}
}
void main(){
	//profil1();
	//profil2();

	demo();
	printf("\n\n\n");
	afisLista(vL,5);

	
	system("pause");
	profiler.showReport();
}