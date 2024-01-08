#include <stdio.h>
#include <limits.h>

#define MAX_V 2000
#define INF INT_MAX

int min(int a, int b) {
    return (a < b) ? a : b;
}

void floydWarshall(int V, int graph[MAX_V][MAX_V]) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (graph[i][k] != INF && graph[k][j] != INF)
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
    int V, v, w, c, t, o, x;
    int graph[MAX_V][MAX_V], super_graph[MAX_V][MAX_V];

    scanf("%d", &V);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = super_graph[i][j] = (i == j) ? 0 : INF;

    while (scanf("%d %d %d %d", &v, &w, &c, &t) == 4 && !(v == 0 && w == 0 && c == 0 && t == 0)) {
        graph[v][w] = graph[w][v] = c;
        if (t == 1) super_graph[v][w] = c;
    }

    floydWarshall(V, graph);
    floydWarshall(V, super_graph);

    while (scanf("%d %d", &o, &x) == 2) {
        if (graph[o][x] == INF && super_graph[o][x] == INF)
            printf("Impossibru\n");
        else
            printf("%d %d\n", graph[o][x], super_graph[o][x]);
    }

    return 0;
}
