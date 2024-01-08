#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>


#define V 5 

int minDistance(int dist[], bool visitado[]) {
    int min = INT_MAX, min_index;
    for (int i=0; i < V; i++) {
        if(!visitado[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visitado[V];

    for (int i=0; i < V; i++) {
        dist[i] = INT_MAX;
        visitado[i] = false;
    }

    dist[src] = 0;

    for (int count=0; count < V-1; count++) {
        int u = minDistance(dist, visitado);
        visitado[u] = true;

        for (int v=0; v < V; v++) {
            if(!visitado[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
        printf("Vertex   Distance from Source\n");
        for (int i = 0; i < V; i++) {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}

int main () {
    int graph[V][V] = {
        {0, 4, 0, 0, 0},
        {4, 0, 8, 0, 0},
        {0, 8, 0, 7, 0},
        {0, 0, 7, 0, 9},
        {0, 0, 0, 9, 0}
    };

    dijkstra(graph, 0);

    return 0;
}