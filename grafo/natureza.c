#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um grafo
typedef struct Grafo {
    int numVertices;
    int** matrizAdjacencia;
} Grafo;

// Função para criar um grafo com um número específico de vértices
Grafo* criarGrafo(int numVertices) {
    Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
    novoGrafo->numVertices = numVertices;

    // Alocar memória para a matriz de adjacência
    novoGrafo->matrizAdjacencia = (int**)malloc(numVertices * sizeof(int*));
    int i, j;
    for (i = 0; i < numVertices; i++) {
        novoGrafo->matrizAdjacencia[i] = (int*)malloc(numVertices * sizeof(int));
        for (j = 0; j < numVertices; j++) {
            // Inicializar todos os elementos com 0 (sem aresta)
            novoGrafo->matrizAdjacencia[i][j] = 0;
        }
    }

    return novoGrafo;
}

// Função para adicionar uma aresta entre dois vértices do grafo
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    // Verificar se os vértices são válidos
    if (origem >= 0 && origem < grafo->numVertices && destino >= 0 && destino < grafo->numVertices) {
        // Adicionar a aresta na matriz de adjacência
        grafo->matrizAdjacencia[origem][destino] = 1;
        grafo->matrizAdjacencia[destino][origem] = 1;
    }
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    int i, j;
    for (i = 0; i < grafo->numVertices; i++) {
        for (j = 0; j < grafo->numVertices; j++) {
            printf("%d ", grafo->matrizAdjacencia[i][j]);
        }
        printf("\n");
    }
}

// Função para comparar strings 0 diferente 1 igual
int compareStrings(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]){
            return 0; 
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return 1; 
    else
        return 0;
}

// Função auxiliar para encontrar a maior cadeia de vértices a partir de um vértice específico
void encontrarMaiorCadeiaAux(Grafo* grafo, int vertice, int* visitados, int* cadeiaAtual, int* maiorCadeia, int tamanhoCadeia) {
    visitados[vertice] = 1; // Marcar o vértice como visitado
    cadeiaAtual[tamanhoCadeia++] = vertice; // Adicionar o vértice atual à cadeia

    // Verificar se a cadeia atual é maior que a maior cadeia encontrada até agora
    if (tamanhoCadeia > *maiorCadeia) {
        *maiorCadeia = tamanhoCadeia;
    }

    int i;
    for (i = 0; i < grafo->numVertices; i++) {
        // Verificar se há uma aresta entre o vértice atual e o vértice i e se o vértice i não foi visitado ainda
        if (grafo->matrizAdjacencia[vertice][i] && !visitados[i]) {
            encontrarMaiorCadeiaAux(grafo, i, visitados, cadeiaAtual, maiorCadeia, tamanhoCadeia);
        }
    }

    visitados[vertice] = 0; // Marcar o vértice como não visitado (para outras possíveis cadeias)
    tamanhoCadeia--;
}

// Função para encontrar a maior cadeia de vértices no grafo
int maiorCadeiaVertices(Grafo* grafo) {
    int* visitados = (int*)malloc(grafo->numVertices * sizeof(int));
    int* cadeiaAtual = (int*)malloc(grafo->numVertices * sizeof(int));
    int maiorCadeia = 0;
    int i;
    for (i = 0; i < grafo->numVertices; i++) {
        // Inicializar o vetor de visitados para cada iteração
        memset(visitados, 0, grafo->numVertices * sizeof(int));
        encontrarMaiorCadeiaAux(grafo, i, visitados, cadeiaAtual, &maiorCadeia, 0);
    }
    free(visitados);
    free(cadeiaAtual);
    return maiorCadeia;
}




// Função principal
int main() {
	int vertices, arestas;
	while((scanf("%d %d", &vertices, &arestas) != EOF) && (vertices != 0) && (arestas != 0)){
        printf("entrei no while com verticie: %d e aresta: %d \n", vertices, arestas);
        Grafo* grafo;
        grafo = criarGrafo(vertices);
        int aresta1, aresta2;
        char criatura[vertices][30], compara1[30], compara2[30], relacao[61];
        for(int j=0; j < vertices; j++){
            scanf("%s", criatura[j]);
        }
        //alocar arestas
        for(int i=0; i < arestas; i++){
            printf("entrei alocar aresta\n");
            fgets(relacao, sizeof(relacao), stdin);
            sscanf(relacao, "%s %s", compara1, compara2);    
            for(int i=0; i < vertices; i++){
                if((compareStrings(compara1, criatura[i]) == 1)){
                    //adicionar comparação valor da comparação  para aresta1 e aresta 2 e alocar aresta
                    aresta1 = i;
                }; 
                if((compareStrings(compara2, criatura[i]) == 1)){
                    aresta2 = i;
                }
            }
            adicionarAresta(grafo,aresta1, aresta2);
            getchar();
        }
        int maior;
        maior = maiorCadeiaVertices(grafo);
        printf("%d\n", maior);
    }


    
	return 0;
}

    
