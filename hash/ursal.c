#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRESIDENT_VOTES 100
#define MAX_SENATOR_VOTES 1000
#define MAX_FEDERAL_VOTES 10000
#define MAX_STATE_VOTES 100000

#define less(A, B) ((A) < (B))
#define lesseq(A, B) ((A) <= (B))
#define exch(A, B) { Candidato t; t = A; A = B; B = t; }
#define cmpexch(A, B) { if (less(B, A)) exch(A, B); }

typedef struct Candidato {
    int code;
    int count;
} Candidato;

// Função de comparação para ordenar por 'count' e 'vote'
int compare(const void *a, const void *b) {
    const Candidato *CandidatoA = (const Candidato *)a;
    const Candidato *CandidatoB = (const Candidato *)b;
    if (CandidatoA->count < CandidatoB->count)
      return -1;
    else if (CandidatoA->count > CandidatoB->count)
      return 1;
    if (CandidatoA->code > CandidatoB->code)
      return 1;
    else if (CandidatoA->code < CandidatoB->code)
      return -1;

    return 0;
}

void merge(Candidato *V, int l, int m, int r) {
    Candidato *R = malloc(sizeof(Candidato) * (r - l + 1));
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

void mergesort(Candidato *V, int l, int r) {
    if (l >= r)
        return;
    int meio = (l + r) / 2;
    mergesort(V, l, meio);
    mergesort(V, meio + 1, r);
    merge(V, l, meio, r);
}


int main() {
    int S, F, E;
    scanf("%d %d %d", &S, &F, &E);



    Candidato* president_votes = malloc(sizeof(Candidato) * MAX_PRESIDENT_VOTES);
    Candidato* senator_votes = malloc(sizeof(Candidato) * MAX_SENATOR_VOTES);
    Candidato* fed_votes = malloc(sizeof(Candidato) * MAX_FEDERAL_VOTES);
    Candidato* est_votes = malloc(sizeof(Candidato) * MAX_STATE_VOTES);
    
    // Initialize vote counts to zero
    memset(president_votes, 0, sizeof(Candidato) * MAX_PRESIDENT_VOTES);
    memset(senator_votes, 0, sizeof(Candidato) * MAX_SENATOR_VOTES);
    memset(fed_votes, 0, sizeof(Candidato) * MAX_FEDERAL_VOTES);
    memset(est_votes, 0, sizeof(Candidato) * MAX_STATE_VOTES);
    
    int valid_votes = 0;
    int invalid_votes = 0;
    int voto, votopresida = 0;

    while (scanf("%d", &voto) != EOF) {
        // Implement proper input validation
        if (voto >= 0 && voto < 99999) {
            valid_votes++;
            
            if (voto >= 10 && voto < 100) {
                president_votes[voto].code = voto;
                president_votes[voto].count++;
                votopresida++;
            }
            else if (voto >= 100 && voto < 1000) {
                senator_votes[voto].code = voto;
                senator_votes[voto].count++;
            } else if (voto >= 1000 && voto < 10000) {
                fed_votes[voto].code = voto;
                fed_votes[voto].count++;
            } else if (voto >= 10000 && voto < 100000) {
                est_votes[voto].code = voto;
                est_votes[voto].count++;
            }
        } else {
            invalid_votes++;
        }
    }
    printf("%d %d\n", valid_votes, invalid_votes);
    //presida::

    mergesort(president_votes, 0, 99);
    if(president_votes[99].count > votopresida/2){
      printf("%d\n", president_votes[99].code);
    } else printf("Segundo turno\n");

    //senador::
    mergesort(senator_votes, 100, 999);
    int gap=999;
    for(int i=0; i< S; i++){
      printf("%d ", senator_votes[gap--].code);
    }
    printf("\n");
    //federal::
    mergesort(fed_votes, 1000, 9999);
    gap=9999;
    for(int i=0; i< F; i++){
      printf("%d ", fed_votes[gap--].code);
    }
    printf("\n");
    //estadual::
    mergesort(est_votes, 10000, 99999);
    gap=99999;
    for(int i=0; i< E; i++){
      printf("%d ", est_votes[gap--].code);
    }
    printf("\n");
    //printf("\nResultado da eleição :\n");
    //for (int i = 9999; i >= 0; i--) {
    //    if (candidatos[i].count > 0) {
    //        printf("%d: %d votos posição: %d\n", candidatos[i].code, candidatos[i].count, i);
    //    }
    //}

    free(president_votes);
    free(senator_votes);
    free(fed_votes);
    free(est_votes);
    return 0;
}
