#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura para representar um nó da lista de adjacência
typedef struct Node {
    int destino;
    struct Node* proximo;
} Node;

// Estrutura para representar um grafo
typedef struct Grafo {
    int numVertices;
    Node* listaAdj[MAX_VERTICES];
} Grafo;

// Função para inicializar o grafo
void inicializarGrafo(Grafo* grafo, int numVertices) {
    grafo->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        grafo->listaAdj[i] = NULL;
    }
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    // Cria um novo nó
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->destino = destino;
    novoNode->proximo = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNode;

    // Cria um novo nó para a aresta reversa (grafo não direcionado)
    novoNode = (Node*)malloc(sizeof(Node));
    novoNode->destino = origem;
    novoNode->proximo = grafo->listaAdj[destino];
    grafo->listaAdj[destino] = novoNode;
}

// Função para DFS (Depth-First Search) para encontrar componentes conexos
void DFS(Grafo* grafo, int vertice, int visitado[], int* tamanhoComponente) {
    visitado[vertice] = 1;
    (*tamanhoComponente)++;

    Node* atual = grafo->listaAdj[vertice];
    while (atual != NULL) {
        if (!visitado[atual->destino]) {
            DFS(grafo, atual->destino, visitado, tamanhoComponente);
        }
        atual = atual->proximo;
    }
}

// Função para encontrar o menor índice do maior componente conexo
int menorIndiceMaiorComponenteConexo(Grafo* grafo) {
    int visitado[MAX_VERTICES] = {0};
    int maiorTamanho = 0;
    int menorIndice = MAX_VERTICES;

    for (int i = 0; i < grafo->numVertices; i++) {
        if (!visitado[i]) {
            int tamanhoComponente = 0;
            DFS(grafo, i, visitado, &tamanhoComponente);

            if (tamanhoComponente > maiorTamanho) {
                maiorTamanho = tamanhoComponente;
                menorIndice = i;
            } else if (tamanhoComponente == maiorTamanho && i < menorIndice) {
                menorIndice = i;
            }
        }
    }

    return menorIndice;
}

int main() {
    int numVertices, numArestas;

    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);
    Grafo grafo;
    inicializarGrafo(&grafo, numVertices);

    int tempA, tempB;
    while (scanf("%d %d", &tempA, &tempB) != EOF) {
        adicionarAresta(&grafo, tempA, tempB);
    }

    int resultado = menorIndiceMaiorComponenteConexo(&grafo);
    printf("O menor índice do maior componente conexo é: %d\n", resultado);

    return 0;
}
