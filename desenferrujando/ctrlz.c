#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char items[50][100];
  int top;
} Stack;

void push(Stack *s, char *item) {
    s->top++;
    strcpy(s->items[s->top], item);
}

char* pop(Stack *s) {
    if (s->top == -1) {
        return NULL;
    } else {
        char *item = malloc(strlen(s->items[s->top]) + 1);
        strcpy(item, s->items[s->top]);
        s->top--;
        return item;
    }
}

int main() {
    Stack s;
    char str[100];
    s.top = -1;
    while (fgets(str, 100, stdin) != NULL) {
        if (strncmp(str, "inserir", 7) == 0) {
            char *newstr = str + 8;
            push(&s, newstr);
        } else if (strncmp(str, "desfazer", 7) == 0) {
            char *ultima = pop(&s);
            if (ultima == NULL) {
                printf("NULL\n");
            } else {
                printf("%s\n", ultima);
                free(ultima);
            }
        }
    }

    return 0;
}
