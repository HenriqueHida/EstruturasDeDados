#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure to represent a weighted graph
typedef struct {
    int vertices;
    int edges;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} WeightedGraph;

// Function to initialize the graph
void initializeGraph(WeightedGraph* graph, int vertices) {
    graph->vertices = vertices;
    graph->edges = 0;

    // Initialize all elements of the adjacency matrix to 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(WeightedGraph* graph, int source, int destination, int weight) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        // Update the adjacency matrix with the weight
        graph->matrix[source][destination] = weight;
        graph->matrix[destination][source] = weight; // If the graph is undirected
        graph->edges++;
    }
}

// Function to print the graph
void printGraph(WeightedGraph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    WeightedGraph graph;
    int vertices, edges;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    initializeGraph(&graph, vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(&graph, source, destination, weight);
    }

    printf("\nGraph representation:\n");
    printGraph(&graph);

    return 0;
}

