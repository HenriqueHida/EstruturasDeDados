#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int code;
    int votes;
} Candidate;

int is_valid(int voto) {
    return voto >= 0;
}

int compare_candidates(const void *a, const void *b) {
    const Candidate *candidateA = (const Candidate *)a;
    const Candidate *candidateB = (const Candidate *)b;

    if (candidateA->votes != candidateB->votes) {
        return candidateB->votes - candidateA->votes;
    } else {
        return candidateB->code - candidateA->code;
    }
}

int main() {
    int S, F, E;
    scanf("%d %d %d", &S, &F, &E);

    Candidate* president_votes = malloc(sizeof(Candidate) * 100);
    Candidate* senator_votes = malloc(sizeof(Candidate) * 1000);
    Candidate* dep_fed_votes = malloc(sizeof(Candidate) * 10000);
    Candidate* dep_est_votes = malloc(sizeof(Candidate) * 100000);
    int valid_votes = 0;
    int invalid_votes = 0;

    memset(president_votes, 0, sizeof(Candidate) * 100);
    memset(senator_votes, 0, sizeof(Candidate) * 1000);
    memset(dep_fed_votes, 0, sizeof(Candidate) * 10000);
    memset(dep_est_votes, 0, sizeof(Candidate) * 100000);

    int voto;
    while (scanf("%d", &voto) != EOF) {
        if (is_valid(voto)) {
            valid_votes++;

            if (voto >= 10 && voto < 100) {
                president_votes[voto - 10].code = voto;
                president_votes[voto - 10].votes++;
            } else if (voto >= 100 && voto < 1000) {
                senator_votes[voto - 100].code = voto;
                senator_votes[voto - 100].votes++;
            } else if (voto >= 1000 && voto < 10000) {
                dep_fed_votes[voto - 1000].code = voto;
                dep_fed_votes[voto - 1000].votes++;
            } else if (voto >= 10000 && voto < 100000) {
                dep_est_votes[voto - 10000].code = voto;
                dep_est_votes[voto - 10000].votes++;
            }
        } else {
            invalid_votes++;
        }
    }

    int max_president_votes = 0;
    int president_winner = -1;
    float qtd_votes_pres = 0;
    for (int i = 0; i < 100; i++) {
        if (president_votes[i].votes > 0) {
            qtd_votes_pres += president_votes[i].votes;
        }
        
        if (president_votes[i].votes > max_president_votes) {
            max_president_votes = president_votes[i].votes;
            president_winner = president_votes[i].code;
        }

    }

    Candidate* senator_winners = malloc(sizeof(Candidate) * 1000);
    Candidate* dep_fed_winners = malloc(sizeof(Candidate) * 10000);
    Candidate* dep_est_winners = malloc(sizeof(Candidate) * 100000);

    int num_senator_winners = 0;
    int num_dep_fed_winners = 0;
    int num_dep_est_winners = 0;

    for (int i = 0; i < 1000; i++) {
        if (senator_votes[i].votes > 0) {
            senator_winners[num_senator_winners] = senator_votes[i];
            num_senator_winners++;
        }
    }

    qsort(senator_winners, num_senator_winners, sizeof(Candidate), compare_candidates);

    for (int i = 0; i < 10000; i++) {
        if (dep_fed_votes[i].votes > 0) {
            dep_fed_winners[num_dep_fed_winners] = dep_fed_votes[i];
            num_dep_fed_winners++;
        }
    }

    qsort(dep_fed_winners, num_dep_fed_winners, sizeof(Candidate), compare_candidates);

    for (int i = 0; i < 100000; i++) {
        if (dep_est_votes[i].votes > 0) {
            dep_est_winners[num_dep_est_winners] = dep_est_votes[i];
            num_dep_est_winners++;
        }
    }

    qsort(dep_est_winners, num_dep_est_winners, sizeof(Candidate), compare_candidates);

    printf("%d %d\n", valid_votes, invalid_votes);
    if (president_winner != -1 && (max_president_votes * 2 > qtd_votes_pres)) {
        printf("%d\n", president_winner);
    } else {
        printf("Segundo turno\n");
    }

    for (int i = 0; i < S; i++) {
        if (i < num_senator_winners) {
            printf("%d ", senator_winners[i].code);
        }
    }
    printf("\n");

    for (int i = 0; i < F; i++) {
        if (i < num_dep_fed_winners) {
            printf("%d ", dep_fed_winners[i].code);
        }
    }
    printf("\n");

    for (int i = 0; i < E; i++) {
        if (i < num_dep_est_winners) {
            printf("%d ", dep_est_winners[i].code);
        }
    }
    printf("\n");

    free(president_votes);
    free(senator_votes);
    free(dep_fed_votes);
    free(dep_est_votes);
    free(senator_winners);
    free(dep_fed_winners);
    free(dep_est_winners);

    return 0;
}
