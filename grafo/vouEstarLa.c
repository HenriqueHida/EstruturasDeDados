'''
Código em C para verificar se existe um caminho entre dois nós em um grafo direcionado.
Exemplo de input para teste:
5
0 1 1
1 2 1
2 3 1
3 4 1
0 0 0
0 4
1 3
4 0

Inicialmente se passa o numero de vertices do grafo, depois são adicionados as arestas
num formato (aresta1 aresta2 direção), sendo que essa direção pode ser 1 (apenas ida) ou 2 (ida e volta).
e por fim são passados os nós que se deseja verificar se existe um caminho entre eles.

'''



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOS 200

// Estrutura que representa o grafo
typedef struct Grafo {
    int** matriz;
    int numVertices;
} Grafo;

void inicializarGrafo(Grafo* grafo, int numVertices) {
    grafo->numVertices = numVertices;
    grafo->matriz = malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        grafo->matriz[i] = malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            grafo->matriz[i][j] = 0;
        }
    }
}

// Função para adicionar uma aresta direcionada entre dois nós
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    grafo->matriz[origem][destino] = 1;
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se existe um caminho entre dois nós usando busca em largura
bool verificarCaminho(Grafo* grafo, int inicio, int destino) {
    bool visitados[MAX_NOS] = { false };
    int fila[MAX_NOS];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitados[inicio] = true;

    while (frente != tras) {
        int noAtual = fila[frente++];
        if (noAtual == destino) {
            return true; // Caminho encontrado
        }

        for (int i = 0; i < grafo->numVertices; i++) {
            if (grafo->matriz[noAtual][i] == 1 && !visitados[i]) {
                fila[tras++] = i;
                visitados[i] = true;
            }
        }
    }

    return false; // Caminho não encontrado
}

// Função principal
int main() {
    Grafo grafo;
    int numVertices, v, w, d;

    scanf("%d", &numVertices);
    inicializarGrafo(&grafo, numVertices);

    while((scanf("%d %d %d", &v, &w, &d) != EOF) && ((v != 0) || (w != 0)  || (d != 0))){
        if (v < numVertices && w < numVertices) {
            if(d == 1){
                adicionarAresta(&grafo, v, w);
            }
            else if(d == 2){
                adicionarAresta(&grafo, v, w);
                adicionarAresta(&grafo, w, v);
            }
            else {
                printf("insira um valor válido para D\n");
            }
        }
        else {
            printf("insira um valor válido para v e w\n");
        }
    }
    int t,x;
    while(scanf("%d %d", &t, &x) != EOF){
        if(t < numVertices && x < numVertices) {
            if((verificarCaminho(&grafo, t, x) == true) && verificarCaminho(&grafo, x, t) == true) {
                printf("Ida e volta\n");
            }
            else if(verificarCaminho(&grafo, t, x) == true) {
                printf("Apenas ida\n");
            }
            else if(verificarCaminho(&grafo, x, t) == true) {
                printf("Apenas volta\n");
            }
            else {
                printf("Não existe caminho\n");
            }
        }
        else {
            printf("insira um valor válido, segfault\n");
        }
    }
}

