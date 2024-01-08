#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXN 2005
#define INF INT_MAX

int **graph, V;
typedef struct {
    int vertex;
    int key;
} Node;

Node* heap[MAXN];
int heapSize = 0;

void swap(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void heapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heapSize && heap[left]->key < heap[smallest]->key)
        smallest = left;

    if (right < heapSize && heap[right]->key < heap[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        swap(&heap[idx], &heap[smallest]);
        heapify(smallest);
    }
}

Node* extractMin() {
    if (heapSize <= 0)
        return NULL;

    if (heapSize == 1) {
        heapSize--;
        return heap[0];
    }

    Node* root = heap[0];
    heap[0] = heap[heapSize-1];
    heapSize--;
    heapify(0);

    return root;
}

void decreaseKey(int v, int key) {
    heap[v]->key = key;
    while (v != 0 && heap[(v - 1) / 2]->key > heap[v]->key) {
        swap(&heap[v], &heap[(v - 1) / 2]);
        v = (v - 1) / 2;
    }
}

int* primMST() {
    Node nodes[MAXN];
    bool inMST[MAXN];
    int* parent = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        nodes[i].vertex = i;
        nodes[i].key = INF;
        inMST[i] = false;
        heap[i] = &nodes[i];
        parent[i] = -1; // Initialize parent array
    }

    heap[0]->key = 0;
    heapSize = V;
    decreaseKey(0, 0);

    while (heapSize != 0) {
        Node* u = extractMin();
        inMST[u->vertex] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u->vertex][v] && !inMST[v] && graph[u->vertex][v] < nodes[v].key) {
                parent[v] = u->vertex;
                decreaseKey(v, graph[u->vertex][v]);
            }
        }
    }

    return parent;
}
bool isPath(int parent[], int src, int dest) {
    if (src == dest)
        return true;
    if (parent[dest] == -1)
        return false;
    return isPath(parent, src, parent[dest]);
}


int main() {
    int v,w,d,t,x;
    scanf("%d", &V);
    graph = (int**) malloc(V * sizeof(int*) + 1);
    memset(graph, 0, sizeof(graph));

    while(scanf("%d %d %d", &v, &w, &d) == 3 && v != 0 && w != 0 && d != 0) {
        if (d == 1) {
            graph[v][w] = 1;
        } else if (d == 2) {
            graph[v][w] = 1;
            graph[w][v] = 1;

        }
    }

    while (scanf("%d %d", &t, &x) != EOF){
        int* parent = primMST();
        bool ida = isPath(parent, t, x);
        bool volta = isPath(parent, x, t);
        free(parent);
        
        if (ida && volta) {
            printf("\nIda e Volta");
        } else if (ida) {
            printf("\nApenas Ida");
        } else if (volta) {
            printf("\nApenas Volta");
        } else {
            printf("\nImpossibru");
        }    
    }
    
    return 0;
}