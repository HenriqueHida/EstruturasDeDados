#include <stdio.h>
#include <stdlib.h>

#ifndef QUEUE
#define QUEUE
typedef int QueueItem;
typedef struct Queue_Node {
  QueueItem value;
  Queue_Node *next;
} Queue_Node;

typedef struct {
  Queue_Node *head, *last;
} Queue;

Queue *Queue_New() {
  Queue *q = calloc(1, sizeof(Queue));
  return q;
}

void Queue_Push(Queue *q, QueueItem item) {
  Queue_Node *newNode = malloc(sizeof(Queue_Node));
  newNode->next = NULL;
  newNode->value = item;
  if (q->last) {
    q->last->next = newNode;
  } else {
    q->head = newNode;
  }

  q->last = newNode;
}

QueueItem Queue_Front(Queue *q) { return q->head->value; }

void Queue_Pop(Queue *q) {
  Queue_Node *toFree = q->head;

  if (q->head == q->last) {
    q->last = NULL;
  }

  q->head = q->head->next;
  free(toFree);
}

int Queue_Empty(Queue *q) { return q->head == NULL; }
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
  int edgesSize;
  Edge *edgesOf;
} Graph;

Graph *Graph_New(int size) {
  Graph *g = malloc(sizeof(Graph));
  g->size = size;
  g->edgesOf = calloc(size, sizeof(Edge));
  g->edgesSize = 0;
  return g;
}

void Graph_Destroy(Graph *g) {
  for (int i = 0; i < g->size; i++) {
    Edge *actual = g->edgesOf[i].next;
    Edge *tmp;

    while (actual) {
      tmp = actual->next;
      free(actual);
      actual = tmp;
    }
  }
  free(g->edgesOf);
  free(g);
}

void Graph_Insert(Graph *g, int u, int v, long long w) {
  Edge *newEdge = malloc(sizeof(Edge));
  newEdge->u = u;
  newEdge->v = v;
  newEdge->w = w;
  newEdge->next = g->edgesOf[u].next;
  g->edgesSize++;
  g->edgesOf[u].next = newEdge;
}
#endif

int bellmanfordBFS(Graph *g, int src, int *pa, long long *dist) {
  char *onQueue = calloc(g->size, 1);
  for (int i = 0; i < g->size; i++) {
    pa[i] = -1;
    dist[i] = __LONG_LONG_MAX__;
  }
  pa[src] = src;
  dist[src] = 0;

  Queue *q = Queue_New();
  Queue_Push(q, src);
  onQueue[src] = 1;

  Queue_Push(q, g->size);

  int k = 0;
  while (1) {
    int v = Queue_Front(q);
    Queue_Pop(q);

    if (v == g->size) {
      if (Queue_Empty(q)) {
        return 1;
      }
      if (++k >= g->size) {
        return 0;
      }

      for (int i = 0; i < g->size; i++) {
        onQueue[i] = 0;
      }
      Queue_Push(q, g->size);
    } else {
      for (Edge *edge = g->edgesOf[v].next; edge != NULL; edge = edge->next) {
        if (dist[v] + edge->w < dist[edge->v]) {
          dist[edge->v] = dist[v] + edge->w;
          if (!onQueue[edge->v]) {
            Queue_Push(q, edge->v);
          }
        }
      }
    }
  }
}

int bellmanfordEdges(Graph *g, int src, int *pa, long long *dist) {
  Edge *edges = malloc(sizeof(Edge) * g->edgesSize);
  int edgesLen = 0;
  for (int i = 0; g->size; i++) {
    dist[i] = __LONG_LONG_MAX__;
    pa[i] = -1;

    for (Edge *e = g->edgesOf[i].next; e != NULL; e = e->next) {
      edges[edgesLen++] = *e;
    }
  }

  for (int i = 0; i < g->size; i++) {
    for (int j = 0; j < edgesLen; j++) {
      Edge e = edges[j];
      if (dist[e.u] != __LONG_LONG_MAX__ && dist[e.u] + e.w < dist[e.v]) {
        dist[e.v] = dist[e.u] + e.w;
      }
    }
  }

  for (int j = 0; j < edgesLen; j++) {
    Edge e = edges[j];
    if (dist[e.u] != __LONG_LONG_MAX__ && dist[e.u] + e.w < dist[e.v]) {
      return 0;
    }
  }

  return 1;
}
