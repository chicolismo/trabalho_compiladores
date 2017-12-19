#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Globais
static int label_counter = 0; // Contador dos rótulos já criados
static int temp_counter = 0;  // Contador dos valores temporários
static int string_counter = 0;

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
    node->string[size - 1] = '\0';
    node->type = type;
    node->next = NULL;
    
    switch (node->type) {
        case SYMBOL_LIT_INTEGER:
        case SYMBOL_LIT_REAL:
            node->asm_string = malloc(sizeof(char) * 20);
            strcpy(node->asm_string, "__\0");
            strcat(node->asm_string, node->string);
            break;
            
        case SYMBOL_LIT_CHAR:
            node->asm_string = malloc(sizeof(char) * 4);
            node->asm_string[0] = '_';
            node->asm_string[1] = '_';
            node->asm_string[2] = node->string[1];
            node->asm_string[3] = '\0';
            break;
            
        default:
            node->asm_string = NULL;
            break;
    }
    
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

HashNode *makeLabel() {
    char label_name[LABEL_SIZE];
    sprintf(label_name, "__label_%d__", label_counter++);
    return setHashNode(label_name, SYMBOL_LABEL);
}

HashNode *makeTemp() {
    char temp_name[TEMP_SIZE];
    sprintf(temp_name, "__temp_%d__", temp_counter++);
    return setHashNode(temp_name, SYMBOL_IDENTIFIER_SCALAR);
}
