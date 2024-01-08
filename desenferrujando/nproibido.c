#include <stdio.h>
#include <stdlib.h>

//HT = HashTable = Tabela Hash
// para um vetor o intervalo fechado é [0,262143]
#define HTSIZE 140000
#define HTNULL -1

typedef struct no
{
  int Pi;
  struct no *prox;
} no;

typedef struct lista_st
{
  no *head;
  int count;
} lista_st;

void LEinit(lista_st *lista)
{
  lista->head=NULL;
  lista->count=0;
}

void LEinsert(lista_st *lista, int Pi)
{
  no *l=malloc(sizeof(no));
  l->Pi=Pi;
  l->prox=lista->head;
  lista->head=l;
  lista->count++;
}

int LEsearch(lista_st *lista,int x)
{
  no *aux=lista->head;
  while(aux!=NULL)
  {
    if(aux->Pi==x)
      return 1;
    aux=aux->prox;
  }
  return 0;

}

typedef struct HT_st
{
  lista_st *ht;
  int count;
} HT_st;

int hash(int Pi)
{
  return Pi%HTSIZE;
}

void HTinit(HT_st *HT)
{
  HT->ht=malloc(sizeof(lista_st)*HTSIZE);
  HT->count=0;

  //elemento vazio da tabela hash será o -1
  for(int i=0;i<HTSIZE;i++)
    LEinit(&HT->ht[i]);
}

void HTinsert(HT_st *HT,int x)
{
  int hashv=hash(x);
  LEinsert(&HT->ht[hashv],x);
  HT->count++;
}

int HTsearch(HT_st *HT, int x)
{
  int hashv=hash(x);

  return LEsearch(&HT->ht[hashv],x);

}

int main(void)
{
  HT_st hashtable;
  HTinit(&hashtable);

  //Os números proibidos variam entre [0,2^31]
  int N;
  scanf("%d",&N);
  for(int i=0;i<N;i++)
  {
    int Pi;
    scanf("%d",&Pi);
    HTinsert(&hashtable,Pi);
  }
  #if 0
  for(int i=0;i<HTSIZE;i++)
    if(hashtable.ht[i].count>=2)
      printf("Colisao em %d, temos %d elementos\n",i,hashtable.ht[i].count);
  #endif

  int pergunta;
  while(scanf("%d",&pergunta)==1)
  {
    if(HTsearch(&hashtable,pergunta))
      printf("sim\n");
    else
      printf("nao\n");
  }
}