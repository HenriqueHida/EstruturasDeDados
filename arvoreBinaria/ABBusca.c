#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó em uma árvore binária de busca
struct Node* insertNode(struct Node* root, int key) {
    if (root == NULL) {
        // Árvore vazia, cria o nó raiz
        return createNode(key);
    }

    // Caso contrário, percorre a árvore recursivamente
    if (key < root->key) {
        // Inserção na subárvore esquerda
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        // Inserção na subárvore direita
        root->right = insertNode(root->right, key);
    }

    // Retorna o ponteiro para a raiz atualizada
    return root;
}

// Função para buscar um valor em uma árvore binária de busca
struct Node* searchNode(struct Node* root, int key) {
    if (root == NULL || root->key == key) {
        // Nó encontrado ou árvore vazia
        return root;
    }

    // Caso contrário, percorre a árvore recursivamente
    if (key < root->key) {
        // Busca na subárvore esquerda
        return searchNode(root->left, key);
    } else {
        // Busca na subárvore direita
        return searchNode(root->right, key);
    }
}

// Função para percorrer a árvore em ordem (inorder traversal)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        // Visita os nós em ordem
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Função principal
int main() {
    struct Node* root = NULL;
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    printf("Árvore em ordem (inorder): ");
    inorderTraversal(root);
    printf("\n");

    int key = 1000;
    struct Node* searchResult = searchNode(root, key);
    if (searchResult != NULL) {
        printf("Valor %d encontrado na árvore.\n", key);
    } else {
        printf("Valor %d não encontrado na árvore.\n", key);
    }

    // Libera a memória alocada pela árvore
    // ...

    return 0;
}

