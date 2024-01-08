#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um candidato
typedef struct {
    char nome[50];
    int votos;
} Candidato;

// Função de comparação para qsort
int compararCandidatos(const void *a, const void *b) {
    return ((Candidato *)b)->votos - ((Candidato *)a)->votos;
}

int main() {
    int numCandidatos;
    printf("Digite o número de candidatos: ");
    scanf("%d", &numCandidatos);

    Candidato candidatos[numCandidatos];

    // Entrada de dados
    for (int i = 0; i < numCandidatos; i++) {
        printf("Digite o nome do candidato %d: ", i + 1);
        scanf("%s", candidatos[i].nome);
        candidatos[i].votos = 0;
    }

    int numEleitores;
    printf("Digite o número de eleitores: ");
    scanf("%d", &numEleitores);

    // Contagem de votos
    for (int i = 0; i < numEleitores; i++) {
        int voto;
        printf("Digite o número do candidato para o eleitor %d: ", i + 1);
        scanf("%d", &voto);

        // Verifica se o voto é válido
        if (voto >= 1 && voto <= numCandidatos) {
            candidatos[voto - 1].votos++;
        } else {
            printf("Voto inválido! Eleitor %d\n", i + 1);
        }
    }

    // Ordena os candidatos pelo número de votos
    qsort(candidatos, numCandidatos, sizeof(Candidato), compararCandidatos);

    // Imprime os resultados ordenados
    printf("\nResultado da eleição:\n");
    for (int i = 0; i < numCandidatos; i++) {
        printf("%s: %d votos\n", candidatos[i].nome, candidatos[i].votos);
    }

    return 0;
}
