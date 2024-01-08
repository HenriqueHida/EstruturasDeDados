#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int contIlhas;

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    bool* visited;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));
    graph->visited = (bool*)malloc(numVertices * sizeof(bool));

    for (int i = 0; i < numVertices; ++i) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(struct Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    //printf("%d ", vertex);

    struct Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->data;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

void connectedComponents(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        if (!graph->visited[i]) {
            DFS(graph, i);
            contIlhas++;
          //printf("\n");
        }
    }
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d:\n", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int numVertices = 0;
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    int tempA, tempB;

    while (scanf("%d %d", &tempA, &tempB) != EOF) {
        addEdge(graph, tempA, tempB);
    }
    connectedComponents(graph);

    printf("%d\n", contIlhas);

    return 0;
}
