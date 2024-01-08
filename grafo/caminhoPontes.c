#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 1005
#define INF INT_MAX

typedef struct {
    int v, w;
} Node;

Node make_node(int v, int w) {
    Node node = {v, w};
    return node;
}

Node adj[MAXN][MAXN];
int size[MAXN];
int dist[MAXN];
bool visitado[MAXN];
int n, m;

void addEdge(int u, int v, int w) {
    adj[u][size[u]++] = make_node(v, w);
    adj[v][size[v]++] = make_node(u, w);
}

void dijkstra(int src) {
    for (int i = 0; i <= n+1; i++) {
        dist[i] = INF;
        visitado[i] = false;
    }
    dist[src] = 0;
    for (int i = 0; i <= n+1; i++) {
        int u = -1;
        for (int j = 0; j <= n+1; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == INF) {
            break;
        }
        visitado[u] = true;
        for (int j = 0; j < size[u]; j++) {
            int v = adj[u][j].v;
            int w = adj[u][j].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }
    dijkstra(0);
    printf("%d\n", dist[n+1]);
    return 0;
}