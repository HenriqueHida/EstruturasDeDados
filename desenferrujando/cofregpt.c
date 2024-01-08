#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 50

typedef struct {
  int items[STACK_SIZE];
  int top;
} Stack;

void push(Stack *s, int item) {
    s->top++;
    s->items[s->top] = item;
}

int pop(Stack *s) {
    if (s->top < 0) {
        return 0;
    } else {
        int item = s->items[s->top];
        s->top--;
        return item;
    }
}

int popr(Stack *s) {
    if (s->top < 0) {
        return 0;
    } else {
        int item = s->items[0];
        for (int i = 0; i < s->top; i++) {
            s->items[i] = s->items[i+1];
        }
        s->top--; // Ajusta o índice do topo da pilha
        return item;
    }
}

int main () {
    int n, j, z, diff, cont = 0;
    Stack s = { .top = -1 };
    while (scanf("%d", &n) != EOF) { // Usa EOF como condição de parada
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &j, &z);
            diff = j - z;
            push(&s, diff);
        }
        cont++;
        printf("Teste %d:\n", cont); // Corrige a formatação da saída
        int saldo = 0; // Move a variável saldo para fora do loop externo
        for (int j = 0; j < n; j++) {
            int var = popr(&s);
            saldo += var;
            printf("%d\n", saldo);
        }
    }
    return 0;
}

