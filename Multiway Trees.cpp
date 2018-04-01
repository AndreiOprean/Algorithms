
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int root;

typedef struct nod1{
		int key;
		int nr_copii;
		struct nod1** copii;
};

typedef struct nod2{
		int key;
		struct nod2* fiu;
		struct nod2* frate;
}T_2;

nod1* T1(int *a,int size)
{ 
	nod1* root1;
  root1 =(nod1 *)malloc(size*sizeof(nod1));
  for (int i=0;i < size;i++)
  {
	  root1[i].key=i + 1;
	  root1[i].nr_copii=0;
	  
	  if (a[i] != -1) 
		  root1[a[i]].nr_copii++;
	  else 
		  root=i+1;
  }
  
  for (int i = 0;i < size;i++)
  {
	  root1[i].copii=(nod1**)malloc(root1[i].nr_copii*sizeof(nod1*));
	  root1[i].nr_copii = -1;
  }
  for (int i=0;i < size;i++)
  {
	  int j = a[i];
	  if (j != -1)
	  { 
		  root1[j-1].nr_copii++;
	      root1[j-1].copii[root1[j-1].nr_copii]=&root1[i];		  
	  }
  }  
  return root1;
}

nod2* T2(nod1 *parinte,nod1 *r,int k)
{ 
  nod2* p=(nod2*)malloc(sizeof(nod2));
  p->key=r->key;
  p->frate=0;
  p->fiu=0;

  if (r->nr_copii != -1){
	  p->fiu=T2(r, r->copii[0],0);
  }
  else 
	  p->fiu=0;
  if (parinte->nr_copii > k){
	  p->frate=T2(parinte,parinte->copii[k+1],k+1);
  }
  else 
	  p->frate=0;
  return p;
}




void pritprint(nod2* t,int nivel)
{  
	
	for (int i=0;i<nivel;i++){
		printf("  ");
	}

	printf("%d   ",t->key);
	printf("\n");

	if (t->fiu!=0) {
		pritprint(t->fiu,nivel+1);
	}
	
    if (t->frate!=0) {
		pritprint(t->frate,nivel);	
	}
}



int main()
{
	
	int a[9] = {2,7,5,2,7,7,-1,5,2};
  nod1* root1;
  nod2* root2;
  int size = 9;
 
  printf("\nT1\n");
 root1 = T1(a,size);

 for (int i = 0;i < size;i++){
	printf("nod %d cu fii:",root1[i].key);
	 for (int j = 0;j <= root1[i].nr_copii;j++){
		  printf("%d ", root1[i].copii[j]->key);
	  }
	  printf("\n");
  }
 
  nod1* p=(nod1*)malloc(sizeof (nod1));
  p->key=-1;
  p->nr_copii=0;
  p->copii=(nod1 **)malloc(sizeof(nod1));
  p->copii[0]=&root1[root-1];
  
  root2=T2(p,&root1[root-1],0);
  
   printf("\nPP\n");
   pritprint(root2,0);
  
   getch();
  
	return 0;
}