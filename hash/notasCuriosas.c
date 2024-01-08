#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTA 1000
#define MAX_ALUNO  128000

typedef struct Notas{
    int nota;
    int cont;  
}Notas;

int compare(const void *a, const void *b) {
    const Notas *NotasA = (const Notas *)a;
    const Notas *NotasB = (const Notas *)b;
    if (NotasA->cont < NotasB->cont)
      return 1;
    else if (NotasA->cont > NotasB->cont)
      return -1;
    if (NotasA->nota > NotasB->nota)
      return -1;
    else if (NotasA->nota < NotasB->nota)
      return 1;

    return 0;
}

void merge(Notas *V, int l, int m, int r) {
    Notas *R = malloc(sizeof(Notas) * (r - l + 1));
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (compare(&V[i], &V[j]) <= 0)
            R[k++] = V[i++];
        else
            R[k++] = V[j++];
    }

    while (i <= m)
        R[k++] = V[i++];
    while (j <= r)
        R[k++] = V[j++];

    k = 0;
    for (i = l; i <= r; i++)
        V[i] = R[k++];
    free(R);
}

void mergesort(Notas *V, int l, int r) {
    if (l >= r)
        return;
    int meio = (l + r) / 2;
    mergesort(V, l, meio);
    mergesort(V, meio + 1, r);
    merge(V, l, meio, r);
}



int main() {
    int N, valorNota;
    Notas* nota = malloc(sizeof(Notas)*MAX_NOTA);
    memset(nota, 0, sizeof(nota));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
            scanf("%d", &valorNota);
            nota[valorNota].nota = valorNota;
            nota[valorNota].cont++;
    }
    
    mergesort(nota,0,MAX_NOTA);
    //for(int i=0; i<MAX_NOTA; i++) {
    //}
    printf("%d\n", nota[0].nota);
    return 0;
}


//10
//114
//750
//502
//902
//702
//823
//554
//582
//801
//872
