#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Profiler.h"
#define SIZE 20
#define N 10007

Profiler profiler("hash");

struct hash {
	int val;
	char s[3];
};


int functie_hash(int k, int size,int i){
	return (k%size + i*i) % size;

}


int cautare_hash(struct hash *T, int k, int size,int *c, int *tem){
	int i = 0;
	int j;
	*c = *c + 1;
	*tem = *tem + 1;
	do{
		j = functie_hash(k,size,i);
		
		if (strcmp(T[j].s,"FIL") == 0 && T[j].val == k){
			return j;
		}
		else {
			i++;
	*c = *c + 1;
	*tem = *tem + 1;
		}
	}while(i < size && strcmp(T[j].s,"NIL") != 0);
	return -1;
}

void stergere_hash(struct hash *T, int k, int size){
	int j;

	j = cautare_hash(T, k, size,NULL,NULL);
	if (j != -1) {
	strcpy(T[j].s,"DEL");
	T[j].val = 0;
	return;
	}

}

void inserare_hash(struct hash *T, int k, int size){
	int i;
	int j;

	i = 0;
	do{
		j = functie_hash(k,size,i);
		if (strcmp(T[j].s, "NIL") == 0 || strcmp(T[j].s,"DEL") == 0){
			T[j].val = k;
			strcpy(T[j].s,"FIL");
			return;
		}
		else 
			i++;
	}while (i != size);

}

int main(){
	/*
	struct hash T[SIZE];
	float alfa = 0.95;
	int n = 0;
	int temp[100];

	FillRandomArray(temp,SIZE,1,30,true);

	for(int i = 0;i<SIZE;i++){
		strcpy(T[i].s, "NIL");
		T[i].val = 0;
	}


	//Pentru inserare cu factor de umplere de 0.95
	
	while((n/SIZE) <= alfa){
	printf("\nInserez elementul %d\n",temp[n]);
	inserare_hash(T,temp[n],SIZE);
	for(int i = 0;i<SIZE;i++){
		printf("%d  ", T[i].val);
	}
	printf("\n");
	n++;
	}
	
	//Pentru cautare cu factor de umplere de 0.95
	printf("\n\n\n\n\n\n");
	printf("Elementul cu cheia 5 este la indicele:%d\n",cautare_hash(T,5,SIZE,NULL,NULL));
	printf("Elementul cu cheia 25 este la indicele:%d\n",cautare_hash(T,25,SIZE,NULL,NULL));
	printf("Elementul cu cheia 28 este la indicele:%d\n",cautare_hash(T,28,SIZE,NULL,NULL));
	
	*/

	//Evaluare pentru cazul mediu statistic
	
	
	struct hash T[N];
	float alfa[5] = {0.8,0.85,0.9,0.95,0.99};
	int temp[N];
	int cautare;
	int poz[1500];
	int c1 = 0;
	int c2 = 0;
		int n ;
		int max1;
		int max2;
		float mediu1;
		float mediu2;
		int temp1;
		int temp2;
	
	printf("F. umplere|Ef mediu gasite|Ef maxim gasite|Ef mediu negasite|Ef maxim negasite|\n");
	for(int i=0;i<4;i++){
		n = 0;
		max1 = 0;
		max2 = 0;
		mediu1 = 0;
		mediu2 = 0;
		temp1 = 0;
		temp2 = 0;
		int j1 = 0;
		int j2 = 0;
		float rap = 0;
		FillRandomArray(temp,N,1500,200000,true);
	    
		for (int b=0;b < N;b++){
			T[b].val = 0;
			strcpy(T[b].s,"NIL");
		}

		while(rap < alfa[i]){
			inserare_hash(T,temp[n],N);
	
			n++;
			rap = (float)n/(float)N;
			
		}
		FillRandomArray(poz,1500,0,n,true);
		
		for(int j=0;j<1500;j++){
			temp1 = 0;
			temp2 = 0;
			j1 =cautare_hash(T,temp[poz[j]],N,&c1,&temp1);
			j2 =cautare_hash(T,j,N,&c2,&temp2);
		
			if (temp1 > max1)
				max1 = temp1;
			if (temp2 > max2)
				max2 = temp2;
		}
	
		mediu1 = (float)c1/(float)n;
		mediu2 = (float)c2/(float)n;
		
		printf("  %.2f    |    %.2f       |     %d       |     %.2f         |     %d    |\n",alfa[i],mediu1,max1,mediu2,max2);
	}

	

	printf("\n");
	getchar();

	return 0;
}