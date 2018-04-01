/*
Heapsort:defav,fav,mediu -> O(nlog n)
Quicksort:defav -> O(n^2)
fav si mediu -> O(nlog n)
in afara de cazul defavorabil,quicksort e cam de 2-3 ori mai rapid decat heapsortul
in cazul defavorabil sirul este ordonat crescator iar pivotul este prima pozitie sau invers(desc si pivot ultim)
in cazul favorabil sirul este partitionat egal(part sunt eegale) iar pivotul este direct mediana

Quickselect defav -> O(n^2)
fav si mediu O(n)





*/




#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("hsqs");

void maxheapify(int *a, int i, int n,int s)
{
	int l, r, largest, aux;
	l = 2 * i + 1;
	r = 2 * i + 2;
	profiler.countOperation("Comparatii heapsort", s, 1);
	profiler.countOperation("Total heapsort", s, 1);
	if (l<n && a[l]>a[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	profiler.countOperation("Comparatii heapsort", s, 1);
	profiler.countOperation("Total heapsort", s, 1);
	if (r<n && a[r]>a[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		profiler.countOperation("Atribuiri heapsort", s, 3);
		profiler.countOperation("Total heapsort", s, 3);
		aux = a[i];
		a[i] = a[largest];
		a[largest] = aux;
		maxheapify(a, largest, n,s);
	}
}

void buildmaxheap(int *a, int n) {

	for (int i = (n / 2); i >= 0; i--)
	{
		maxheapify(a, i, n, n);
	}
}

void heapsort(int *a,int n, int s) {
	buildmaxheap(a,n);
	for (int i = n - 1; i >= 0; i--) {
		profiler.countOperation("Atribuiri heapsort", s, 3);
		int aux = a[0];
		a[0] = a[i];
		a[i] = aux;
		maxheapify(a, 0, i, s);
	}
}
int partition(int *a, int  p, int r,int n) {
	int x = a[r];
	//int x = a[0];
	//int x = a[(r + p) / 2];
	profiler.countOperation("Atribuiri quicksort", n, 1);
	profiler.countOperation("Total quicksort", n, 1);
	int i = p - 1;
	int j;
	for (j = p; j < r; j++) {
		profiler.countOperation("Comparatii quicksort", n, 1);
		profiler.countOperation("Total quicksort", n, 1);
		if (a[j] <= x) {
			i++;
			profiler.countOperation("Atribuiri quicksort", n, 3);
			profiler.countOperation("Total quicksort", n, 3);
			int aux = a[i];
			a[i] = a[j];
			a[j] = aux;
		}
		
	}
	profiler.countOperation("Atribuiri quicksort", n, 3);
	profiler.countOperation("Total quicksort", n, 3);
	int aux = a[i + 1];
	a[i + 1] = a[r];
	a[r] = aux;
	return i + 1;
}

void quicksort(int *a, int p, int r,int n) {
	if (p < r) {
		int q = partition(a, p, r,n);
		quicksort(a, p, q - 1,n);
		quicksort(a, q + 1, r, n);
	}
}

int quickselect(int *a, int p, int r, int i) {
	if (p == r)
		return a[p];
	int q = partition(a, p, r, 10);
	int k = q - p + 1;
	if (i == k)
		return a[q];
	else if (i < k)
		return quickselect(a, p, q - 1, i);
	else
		return quickselect(a, q + 1, r, i-k);
}

int main()
{
	int a[10] = { 4,1,3,2,16,9,10,14,8,7 };
	int a1[10] = { 4,1,3,2,16,9,10,14,8,7 };
	int a2[10] = { 4,1,3,2,16,9,10,14,8,7 };
	printf("\nInainte de heapsort:\n");
	for (int i = 0; i < 10; i++) {
		printf("%d  ", a[i]);
	}

	heapsort(a, 10,10);

	printf("\nDupa heapsort:\n");
	for (int i = 0; i<10; i++)
	{
		printf("%d  ", a[i]);
	}

	printf("\nInainte de quicksort:\n");
	for (int i = 0; i < 10; i++) {
		printf("%d  ", a1[i]);
	}

	quicksort(a1, 0, 9,10);

	printf("\nDupa quicksort:\n");
	for (int i = 0; i<10; i++)
	{
		printf("%d  ", a1[i]);
	}

	printf("\ncel mai mic elem din sir:%d\n", quickselect(a2, 0, 9, 0));

	/*int t1[10000];
	int t2[10000];
	int size;
	//caz mediu
	/*for (int j = 0; j < 5; j++) {
		for (size = 100; size < 10000; size += 100) {
			FillRandomArray(t1, size);
			for (int i = 0; i < size; i++) {
				t2[i] = t1[i];
			}
			printf("heap sort pt size=%d\n", size);
			heapsort(t1, size,size);
			printf("quick sort pt size=%d\n", size);
			quicksort(t2, 0, size-1, size);
			printf("iteratia=%d\n", j);
		}
	}
	//caz defavorabil
	for (int size = 100; size < 10000; size += 100) {
		FillRandomArray(t1, size, 10, 50000, false, 1);
		printf("quicks pt size=%d\n", size);
		quicksort(t1,0, size - 1, size);

	}

	profiler.createGroup("Quick sort", "Comparatii quicksort", "Atribuiri quicksort");
	//profiler.createGroup("Heap sort", "Comparatii heapsort", "Atribuiri heapsort");
	//profiler.createGroup("Operatii toatale impreuna", "Total heapsort", "Total quicksort");
	profiler.showReport();*/
	system("pause");
    return 0;
}

