#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SWITCHES 2000

typedef struct {
    int cost;
    int isSuperConnection;
} Edge;

typedef struct {
    int vertex;
    int cost;
} Node;

void dijkstra(int graph[MAX_SWITCHES][MAX_SWITCHES], Edge edges[MAX_SWITCHES][MAX_SWITCHES], int numSwitches, int source, int destination) {
    int visited[MAX_SWITCHES] = {0};
    int distance[MAX_SWITCHES];
    int superDistance[MAX_SWITCHES];
    int i;

    for (i = 0; i < numSwitches; i++) {
        distance[i] = INT_MAX;
        superDistance[i] = INT_MAX;
    }

    distance[source] = 0;
    superDistance[source] = 0;

    while (!visited[destination]) {
        int minDistance = INT_MAX;
        int minIndex = -1;
        
        // Find the vertex with minimum distance
        for (i = 0; i < numSwitches; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            break; // No more reachable vertices
        }

        visited[minIndex] = 1;

        for (i = 0; i < numSwitches; i++) {
            if (graph[minIndex][i]) {
                int newDistance = distance[minIndex] + edges[minIndex][i].cost;
                int newSuperDistance = superDistance[minIndex] + edges[minIndex][i].cost;

                if (newDistance < distance[i]) {
                    distance[i] = newDistance;
                }

                if (newSuperDistance < superDistance[i] && !edges[minIndex][i].isSuperConnection) {
                    superDistance[i] = newSuperDistance;
                }
            }
        }
    }

    if (distance[destination] == INT_MAX) {
        printf("Impossibru\n");
    } else {
        printf("%d %d\n", distance[destination], superDistance[destination]);
    }
}

int main() {
    int numSwitches;
    int graph[MAX_SWITCHES][MAX_SWITCHES];
    Edge edges[MAX_SWITCHES][MAX_SWITCHES];

    // Read the number of switches
    scanf("%d", &numSwitches);

    int i, j;

    // Initialize the graph and edges
    for (i = 0; i < numSwitches; i++) {
        for (j = 0; j < numSwitches; j++) {
            if (i != j) {
                graph[i][j] = 0;
                edges[i][j].cost = 0;
                edges[i][j].isSuperConnection = 0;
            }
        }
    }

    int x, y, cost, isSuperConnection;

    // Read the connections and costs
    while (scanf("%d %d %d %d", &x, &y, &cost, &isSuperConnection) == 4) {
        if (x == 0 && y == 0 && cost == 0 && isSuperConnection == 0) {
            break;
        }

        if (x >= 0 && x < numSwitches && y >= 0 && y < numSwitches) {
            graph[x][y] = 1;
            graph[y][x] = 1;
            edges[x][y].cost = cost;
            edges[x][y].isSuperConnection = isSuperConnection;
        }
    }

    int source, destination;

    // Read the queries
    while (scanf("%d %d", &source, &destination) == 2) {
        if (source >= 0 && source < numSwitches && destination >= 0 && destination < numSwitches) {
            dijkstra(graph, edges, numSwitches, source, destination);
        }
    }

    return 0;
}

