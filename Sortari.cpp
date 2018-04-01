#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#define MAX_SIZE 10000
Profiler profiler("Sortari");
/*
1.Bubble sort
Functioneaza prin parcurgerea sirului si compararea a cate 2 elemente invecinate.In cazul in care nu sunt
in ordinea buna le schimba intre ele.Sirul este parcurs de atatea ori pana cand nu se mai face nici o
interschimibare,moment in care sirul este sortat.

Cazul favorabil:sirul este sortat,complexitate O(n)
 Numarul de atribuiri este 0 deoarece nu se face nici o interschimbare
 Numarul de comparatii este (n-1)

 Cazul defavorabil:Sirul este sortat descrescator,deoarece ca principiu minimul aflat la finalul sirului va ajunge
 cel mai greu in locul lui la inceputul sirului
 Numarul de atribuiri este 3*(n*n-1)/2
 Numarul de comparatii este (n*n-1)/2

 Cazul mediu statistic:depinde de grafic
 Comparatiile cresc ca o curba,la fel si atribuirile.
 
 Algoritmul este stabil 
 
 2.Insertion sort:sorteaza element cu element,incepand cu un sir ordonat de un element iar apoi
 ia cate un element din sirul nesortat si il introduce la pozitia corecta.eficient pentru siruri de
 marime relativ mica
 Cazul favorabil : sirul este sortat
 Numarul de atribuiri : 2*(n-1) 
 Numarul de comparatii: are o forma de curba usoara???

 Caz defavorabil : sirul este descrescator

 Cazul mediu:
 Numarul de comparatii este o curba foarte larga??? aproape de liniar
 Numarul de atriburi este o curba


 3.Selection sort:imparte sirul in 2 parti:sortat si nesortat.initial partea sortata este 0.se incepe prin
 a cauta minimul din partea nesortata si mutarea lui in prima pozitie din lista nesortata.se repeta acest
 proces de pana la pozitia n-1

 Caz favorabil:sirul este sortat
 Nr atribuiri: 0
 Nr comparatii : (n*n-1)/2 pt ca se vor compara secvential elem de la stanga la dreapta

 Caz nefavorabil: sirul este ordonat crescator iar minimul din sir este pus la sfarsit.astfel dupa fiecare
 interschimbare minimul va fi la sfarsitul sirului si va trebui cautat prin tot sirul din nou

 Caz mediu:
 Interpretarea graficului.
*/

void bubblesort(int *a, int size) {
	printf("\nBubble sort pentru lungime = %d ", size);
	bool ok;
	int k = 0;
	do {
		ok = false;
		for (int i = 0; i < size - 1 - k; i++) {
			profiler.countOperation("Bubble sort comp", size);
			profiler.countOperation("Total op on bubble sort", size);
			if (a[i] > a[i + 1]) {
				int aux = a[i];
				a[i] = a[i + 1];
				a[i + 1] = aux;
				profiler.countOperation("Total op on bubble sort", size, 3);
				profiler.countOperation("Access mem op on bubble sort", size, 3);
				ok = true;
			}
		}
		k++;
	} while (ok);
}

int cautarebinara(int *a, int el, int min, int max, int size) {
	if (min > max)
		return min;
	else {
		int m = (min + max) / 2;
		profiler.countOperation("Total op on insertion sort", size, 1);
		profiler.countOperation("Insertion sort comp", size);
		if (a[m] == el) {

			return m;
		}
		else {
			profiler.countOperation("Total op on insertion sort", size, 1);
			profiler.countOperation("Insertion sort comp", size);
			if (el < a[m]) {
				return cautarebinara(a, el, min, m - 1, size);
			}
			else
				return cautarebinara(a, el, m + 1, max, size);
		}

	}
}
void insertionsort(int *a, int size){
	printf("\nInsertion sort pentru lungime = %d ", size);
	int aux;
	for (int i = 1; i < size; i++) {
		aux = a[i];
		int poz = cautarebinara(a, a[i], 0, i - 1, size);

		for (int j = i; j >= poz + 1; j--) {
			profiler.countOperation("Insertion sort mem acces", size);
			profiler.countOperation("Total op on insertion sort", size);
			a[j] = a[j - 1];
		}
		a[poz] = aux;
		profiler.countOperation("Total op on insertion sort", size, 2);
		profiler.countOperation("Insertion sort mem acces", size, 2);

	}

}

void selectionsort(int *a, int size) {
	printf("\nSelection sort pentru lungime = %d ", size);
	int poz, aux;
	for (int i = 0; i < size - 1; i++) {
		poz = i;
		for (int j = i + 1; j < size; j++) {
			profiler.countOperation("Comparations on selection sort", size);
			profiler.countOperation("Total op on selection sort", size);
			if (a[j] < a[poz])
				poz = j;
		}
		if (i != poz) {
			profiler.countOperation("Attributions on selection sort", size, 3);
			profiler.countOperation("Total op on selection sort", size, 3);
			aux = a[i];
			a[i] = a[poz];
			a[poz] = aux;
		}

	}

}

int main() {
	/*int a[10] = { 7,3,21,56,1,10,31,90,5,3 };
	int a1[10] = { 7,3,21,56,1,10,31,90,5,3 };
	int a2[10] = { 7,3,21,56,1,10,31,90,5,3 };
	printf("Sirul nesortat: ");
	for (int i = 0; i < 10; i++) {
	printf("%d  ", a[i]);
	}
	bubblesort(a, 10);
	printf("\nSirul sortat cu bubble sort: ");
	for (int i = 0; i < 10; i++) {
	printf("%d  ", a[i]);
	}

	insertionsort(a1, 10);
	printf("\nSirul sortat cu insertion sort: ");
	for (int i = 0; i < 10; i++) {
	printf("%d  ", a1[i]);
	}

	selectionsort(a2, 10);
	printf("\nSirul sortat cu selection sort: ");
	for (int i = 0; i < 10; i++) {
	printf("%d  ", a2[i]);
	}*/
	printf("\n");

	int t1[MAX_SIZE];
	int t2[MAX_SIZE];
	int t3[MAX_SIZE];

	//cazul favorabil
	/*for (int size = 100; size < MAX_SIZE; size += 100) {
		FillRandomArray(t1, size, 10, 50000, false, 1);
		for (int i = 0; i < size; i++) {
			t2[i] = t1[i];
			t3[i] = t1[i];
		}
		selectionsort(t1, size);
		insertionsort(t2, size);
		bubblesort(t3, size);
	}*/

	//caz defavorabil
	for (int size = 100; size < MAX_SIZE; size += 100) {
		FillRandomArray(t1, size, 10, 50000, false, 1);
		int aux = t1[0];

		printf_s("\n\n");
		for (int i = 0; i < size - 1; i++) {
			t1[i] = t1[i + 1];
		}
		t1[size - 1] = aux;
		FillRandomArray(t2, size, 10, 50000, false, 2);
		for (int i = 0; i < size; i++) {
			t3[i] = t2[i];
		}

		selectionsort(t1, size);
		insertionsort(t2, size);
		bubblesort(t3, size);
	}
	
	//caz mediu statistic
	/*for (int j = 0; j < 5; j++) {
		for (int size = 100; size < MAX_SIZE; size += 100) {
			FillRandomArray(t1, size);
			for (int i = 0; i < size; i++) {
				t2[i] = t1[i];
				t3[i] = t1[i];
			}
			selectionsort(t1, size);
			insertionsort(t2, size);
			bubblesort(t3, size);
		}
	}*/
	profiler.createGroup("Selection sort", "Comparations on selection sort", "Total op on selection sort");
	profiler.createGroup("Comparatii", "Bubble sort comp", "Comparations on selection sort");
	profiler.createGroup("Total", "Total op on insertion sort", "Total op on bubble sort", "Total op on selection sort");
	profiler.createGroup("Atribuiri", "Insertion sort mem acces", "Access mem op on bubble sort");
	profiler.showReport();

	getchar();
	return 0;
}