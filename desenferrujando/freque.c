#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () {
    int n, pres = 0;
    scanf("%d", &n);
    int *alunos = malloc(sizeof(int)*n+1);
    int *freq = malloc(sizeof(int)*n+1);
    for(int j=0; j<n; j++){
        scanf("%d", &alunos[j]);
        freq[alunos[j]]++;
        if(freq[alunos[j]] == 1){
            pres++;
        }
    }
    printf("%d\n", pres);
    free(alunos);
    free(freq);
    return 0;
}