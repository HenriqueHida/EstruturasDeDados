#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de nó para a tabela de hash
typedef struct Node {
    int color;
    int count;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(int color) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->color = color;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um nó na tabela de hash
void insert(Node** hashTable, int color) {
    int index = color % 5003; // Um número primo próximo a 5000
    if (hashTable[index] == NULL) {
        hashTable[index] = createNode(color);
    } else {
        Node* current = hashTable[index];
        while (current != NULL) {
            if (current->color == color) {
                current->count++;
                return;
            }
            if (current->next == NULL) break;
            current = current->next;
        }
        current->next = createNode(color);
    }
}

// Função para encontrar a cor majoritária
int findMajorityColor(Node** hashTable) {
    int majorityColor = -1;
    int maxCount = 0;

    for (int i = 0; i < 5003; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            if (current->count > maxCount) {
                maxCount = current->count;
                majorityColor = current->color;
            }
            current = current->next;
        }
    }

    return majorityColor;
}

int main() {
    int N;
    while (1) {
        scanf("%d", &N);
        if (N == 0) break;
        Node* hashTable[5003] = {NULL}; // Usando um número primo próximo a 5000 como tamanho da tabela de hash
        for (int i = 0; i < N; i++) {
            int color;
            scanf("%d", &color);
            insert(hashTable, color);
        }
        int majorityColor = findMajorityColor(hashTable);
        printf("%d\n", majorityColor);
        memset(hashTable, 0, sizeof(hashTable));
    }
    return 0;
}
