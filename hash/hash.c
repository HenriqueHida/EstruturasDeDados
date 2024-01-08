#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000

struct Individuo {
    int id;
    char nome[15]; 
    char sobrenome[15];
    char birthday[10];
    char telefone[16];
    struct Individuo* next;
};

struct hashTable {
    struct Individuo* table[SIZE];     
};

void initialize(struct hashTable* ht) {
    for (int i =0; i < SIZE; i++){
        ht->table[i] = NULL;
    }
}

int hash (int key){
    return key % SIZE;
}

void insert(struct hashTable* ht, int id, char nome, 
            char sobrenome, char birthday, char telefone) {
    int index = hash(id);
    
}
