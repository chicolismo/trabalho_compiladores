#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

// A tabela hash
HashNode *hashTable[HASH_SIZE];


void initializeHashTable() {
    int i;
    for (i = 0; i < HASH_SIZE; ++i) {
        hashTable[i] = NULL;
    }
}


int generateHash(const char *string) {
    int hash, i;
    size_t stringLength;

    hash = 1;
    stringLength = strlen(string);

    for (i = 0; i < stringLength; ++i) {
        hash = ((hash * (int) string[i]) % HASH_SIZE) + 1;
    }

    return hash - 1;
}


HashNode *createHashNode(const char *string, int type) {
    HashNode *node = malloc(sizeof(HashNode));
    size_t size = strlen(string) + 1;
    node->string = malloc(sizeof(char) * size);
    strcpy(node->string, string);
    node->type = type;
    node->next = NULL;
    return node;
}


HashNode *destroyHashNode(HashNode **node) {
    HashNode *n = *node;
    if (n != NULL)
    free(n->string);
    free(n);
    n = NULL;
    *node = n;
    return n;
}


HashNode *getHashNode(const char *string) {
    int hash;
    HashNode *hashNode;

    hash = generateHash(string);
    hashNode = hashTable[hash];

    // Caso haja colisão, temos que percorrer a lista encadeada
    while (hashNode != NULL) {
        if (strcmp(hashNode->string, string) == 0) {
            return hashNode;
        }
        else {
            hashNode = hashNode->next;
        }
    }

    return hashNode; // Será NULL se não houver
}


HashNode *setHashNode(const char *string, int type) {
    int hash = generateHash(string);
    HashNode *newNode, *node;

    node = hashTable[hash];

    // Evita duplicatas na tabela.
    if (node != NULL) {
        HashNode *current = node;
        while (current != NULL) {
            // Se for a mesma string, atualiza o tipo
            if (strcmp(current->string, string) == 0) {
                current->type = type;
                return current;
            }
            node = current;
            current = current->next;
        }
        newNode = createHashNode(string, type);
        node->next = newNode;
        return newNode;
    }
    else {
        newNode = createHashNode(string, type);
        hashTable[hash] = newNode;
        return newNode;
    }
}


void printHashTable() {
    HashNode *node;
    int i;
    for (i = 0; i < HASH_SIZE; ++i) {
        node = hashTable[i];
        while (node != NULL) {
            printf("%d => %s, %d\n", i, node->string, node->type);
            node = node->next;
        }
    }
}


/* Para fins de teste */
// int main() {
//     initializeHashTable();
//     setHashNode("João", 1);
//     setHashNode("João", 2);
//     setHashNode("João", 3);
//     setHashNode("\"Esta eh \"uma\"\"", 34);
//
//     printHashTable();
//
//     return EXIT_SUCCESS;
// }
