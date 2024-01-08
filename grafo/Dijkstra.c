#include <stdlib.h>
#include <stdio.h>

#ifndef HEAP_INDEX
#define HEAP_INDEX

typedef struct {
  int u, v;
  long long w;
} HeapItem;

typedef struct {
  int *pq;
  HeapItem *items;
  int *hash;
  int size;
} HeapIndex;

#define exch(A, B) {int t = A; A = B; B = t; t = h->hash[A]; h->hash[A] = h->hash[B]; h->hash[B] = t;}
#define less(A, B) (h->items[A].w < h->items[B].w)

HeapIndex *HeapIndex_New(HeapItem *items, int size) {
  HeapIndex* h = malloc(sizeof(HeapIndex));
  h->items = items;
  h->pq = ((int*)malloc(sizeof(int) * size)) - 1;
  h->hash = malloc(sizeof(int) * size);
  h->size = 0;

  return h;
}

void HeapIndex_Destroy(HeapIndex *h) {
  h->pq++;
  free(h->pq);
  free(h->items);
  free(h->hash);
  free(h);
}

void HeapIndex_FixUp(HeapIndex *h, int k) {
  int i = h->hash[k];
  while (i > 1 && less(h->pq[i], h->pq[i / 2])) {
    exch(h->pq[i], h->pq[i / 2]);
    i /= 2;
  }
}

void HeapIndex_FixDown(HeapIndex *h, int k) {
  int i = h->hash[k];
  while (i * 2 <= h->size) {
    int j = i * 2;
    if (j != h->size && less(h->pq[j + 1], h->pq[j])) {
      j++;
    }

    if (less(h->pq[j], h->pq[i])) {
      exch(h->pq[i], h->pq[j]);
      i = j;
    } else {
      return;
    }
  }
}

void HeapIndex_Insert(HeapIndex *h, int k) {
  h->pq[++h->size] = k;
  h->hash[k] = h->size;
  HeapIndex_FixUp(h, k);
}

void HeapIndex_Pop(HeapIndex *h) {
  exch(h->pq[h->size], h->pq[1]);
  h->size--;
  HeapIndex_FixDown(h, h->pq[1]);
}

int HeapIndex_Top(HeapIndex *h) {
  return h->pq[1];
}

int HeapIndex_Empty(HeapIndex *h) {
  return h->size == 0;
}

void HeapIndex_Update(HeapIndex *h, int k, HeapItem newValue) {
  h->items[k] = newValue;
  HeapIndex_FixUp(h, k);
  HeapIndex_FixDown(h, k);
}

#endif

#ifndef GRAPH
#define GRAPH
typedef struct Edge {
  int u, v;
  long long w;
  struct Edge *next;
} Edge;

typedef struct {
  int size;
  Edge *edgesOf;
} Graph;


Graph* Graph_New(int size) {
  Graph* g = malloc(sizeof(Graph));
  g->size = size;
  g->edgesOf = calloc(size, sizeof(Edge));

  return g;
}

void Graph_Destroy(Graph *g) {
  for(int i = 0; i < g->size; i++) {
    Edge* actual = g->edgesOf[i].next;
    Edge* tmp;
    
    while(actual) {
      tmp = actual->next;
      free(actual);
      actual = tmp;
    }
  }
  free(g->edgesOf);
  free(g);
}

void Graph_Insert(Graph* g, int u, int v, long long w) {
  Edge* newEdge = malloc(sizeof(Edge));
  newEdge->u = u;
  newEdge->v = v;
  newEdge->w = w;
  newEdge->next = g->edgesOf[u].next;
  g->edgesOf[u].next = newEdge;
}
#endif

// O(E*Log(V))
long long* Dijkstra(Graph *g, int source, int *pa, long long *dist) {
  HeapIndex *h = HeapIndex_New(malloc(sizeof(HeapItem) * g->size), g->size);
  for(int i = 0; i < g->size; i++) {
    h->items[i] = (HeapItem){0, i, __LONG_LONG_MAX__};
    h->pq[i+1] = i;
    h->hash[i] = i+1;
    dist[i] = __LONG_LONG_MAX__;
    pa[i] = -1;
  }
  h->size = g->size;
  HeapIndex_Update(h, source, (HeapItem){source, source, 0});

  while(!HeapIndex_Empty(h)) {
    HeapItem path = h->items[HeapIndex_Top(h)];
    HeapIndex_Pop(h);
    if(path.w == __LONG_LONG_MAX__) {
      break;
    }

    dist[path.v] = path.w;
    pa[path.v] = path.u;
    Edge *actual = g->edgesOf[path.v].next;
    while(actual) {
      if(
        h->hash[actual->v] <= h->size // Verificar se o elemento ainda está na heap
        && path.w + actual->w < h->items[actual->v].w // A distância é menor
      ) {
        HeapIndex_Update(h, actual->v, (HeapItem){actual->u, actual->v, actual->w + path.w});
      }

      actual = actual->next;
    }

  }

  return dist;
}
