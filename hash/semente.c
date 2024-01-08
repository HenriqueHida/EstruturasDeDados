#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SEEDS 100000

// Estrutura para representar as sementes
typedef struct {
    int codigo;
    int nota;
} Semente;

typedef struct {
    int maiorCodigo;
    int maiorNota;
} MaiorSemente;

void merge(Semente* V, int l, int m, int r)
{
  Semente* R = malloc(sizeof(Semente)*(r-l+1));
  int i=l,j=m+1,k=0;

  while(i<=m && j<=r)
  {
    if(V[i].nota <= V[j].nota)
      R[k++]=V[i++];
    else
      R[k++]=V[j++];
  }

  while(i<=m)
      R[k++]=V[i++];
  while(j<=r)
      R[k++]=V[j++];


  k=0;
  for(i=l;i<=r;i++)
    V[i]=R[k++];
  free(R);
}

void mergesort(Semente *V,int l, int r)
{
  if (l>= r) return;
  int meio=(l+r)/2;
  mergesort(V,l,meio);
  mergesort(V,meio+1,r);
  merge(V,l,meio,r);
}




int troca(int a, int b) {
    int t;
    t = a;
    a = b;
    b = t;
    return a, b;
}

// Função de comparação para qsort
//int compararSementes(const void* a, const void* b) {
//    Semente* s1 = (Semente*)a;
//    Semente* s2 = (Semente*)b;
//    if (s1->nota != s2->nota) {
//        return s1->nota - s2->nota; // Ordena por nota (menor nota primeiro)
//    } else {
//        return s1->codigo - s2->codigo; // Desempate pelo menor código de semente
//    }
//}
//
//int compararMelhor (const void* a, const void* b){
//    Semente* s1 = (Semente*)a;
//    Semente* s2 = (Semente*)b;
//    return s1->codigo - s2->codigo;
//}

int main() {
    int n,c=1;
    scanf("%d", &n);
    Semente* sementes = (Semente*)malloc(sizeof(Semente)*MAX_SEEDS);
    scanf("%d %d", &sementes[0].codigo, &sementes[0].nota);
    while (scanf("%d %d", &sementes[c].codigo, &sementes[c].nota) != EOF) {
        c++;
    }

    // Ordena as sementes usando a função de comparação
    mergesort(sementes,0, c);

    // Imprime as melhores sementes
    Semente* melhores = (Semente*) malloc(sizeof(Semente)* 2*n); // Melhor nota encontrada
    int temp;
    for (int i = 0; i < n; i++) {
        melhores[i].codigo = sementes[i].codigo;
        melhores[i].nota = sementes[i].nota;
    }
    mergesort(melhores,0, n);
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", melhores[i].codigo, melhores[i].nota);
    }

   // Libera a memória alocad
    free(melhores);
    free(sementes);
    return 0;
}
