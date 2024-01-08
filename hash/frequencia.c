#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARAC 1000

#define less(A, B) ((A) < (B))
#define lesseq(A, B) ((A) <= (B))
#define exch(A, B) { Caractere t; t = A; A = B; B = t; }
#define cmpexch(A, B) { if (less(B, A)) exch(A, B); }

typedef struct Caractere {
    char letra;
    int ascii;
    int count;
} Caractere;

// Função de comparação para ordenar por 'count' e 'vote'
int compare(const void *a, const void *b) {
    const Caractere *CaractereA = (const Caractere *)a;
    const Caractere *CaractereB = (const Caractere *)b;
    if (CaractereA->count < CaractereB->count)
      return -1;
    else if (CaractereA->count > CaractereB->count)
      return 1;
    if (CaractereA->ascii > CaractereB->ascii)
      return 1;
    else if (CaractereA->ascii < CaractereB->ascii)
      return -1;

    return 0;
}

void merge(Caractere *V, int l, int m, int r) {
    Caractere *R = malloc(sizeof(Caractere) * (r - l + 1));
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

void mergesort(Caractere *V, int l, int r) {
    if (l >= r)
        return;
    int meio = (l + r) / 2;
    mergesort(V, l, meio);
    mergesort(V, meio + 1, r);
    merge(V, l, meio, r);
}


int main() {
    char c;
    int cont=0;    
    
    Caractere* tabela = malloc(sizeof(Caractere)*MAX_CARAC);
    memset(tabela, 0, sizeof(Caractere)*MAX_CARAC);


    while (scanf("%c", c) != EOF) {
        if (c == '\n') break;

        cont++;
    }
    printf("%s\n" ,c);
    return 0;
}
