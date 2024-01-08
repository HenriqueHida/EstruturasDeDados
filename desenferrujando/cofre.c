#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int items[100];
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
        int item = s->items[s->top];
        for (int i = s->top - 1; i >= 0; i--) {
            s->items[i+1] = s->items[i];
        }
        s->top--;
        return item;
    }
}


int main () {
    int n, j, z, diff, cont = 0;
    Stack s = { .top = -1 };
    while (scanf("%d", &n) != 0) { 
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &j, &z);
            diff = j - z;
            push(&s, diff);
        }
        cont++;
        printf("Teste %d:\n", cont); 
        int saldo = 0;
        for (int j = 0; j < n; j++) {
            int var = popr(&s);
            saldo += var;
            printf("%d\n", saldo);
        }
    }
    return 0;
}
