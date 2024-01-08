#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Define a structure for the linked list nodes
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Define a structure for the hash table
struct HashTable {
    struct Node* table[TABLE_SIZE];
};

// Initialize the hash table
void initialize(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Hash function (simple modulo operation)
int hash(int key) {
    return key % TABLE_SIZE;
}

// Insert a key-value pair into the hash table
void insert(struct HashTable* ht, int key, int value) {
    int index = hash(key);
    
    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    // Insert the new node at the beginning of the linked list
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

// Search for a key in the hash table and return its value
int search(struct HashTable* ht, int key) {
    int index = hash(key);
    struct Node* current = ht->table[index];

    // Traverse the linked list to find the key
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    // Key not found
    return -1;
}

// Driver program
int main() {
    struct HashTable ht;
    initialize(&ht);

    insert(&ht, 1, 42);
    insert(&ht, 11, 101);
    insert(&ht, 21, 17);

    printf("Value for key 1: %d\n", search(&ht, 1));   // Should print 42
    printf("Value for key 11: %d\n", search(&ht, 11)); // Should print 101
    printf("Value for key 21: %d\n", search(&ht, 21)); // Should print 17

    return 0;
}
