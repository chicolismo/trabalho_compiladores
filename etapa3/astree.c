#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3) {
    AST *newNode;
    newNode = (AST *)calloc(1, sizeof(AST));
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->son[0] = son0;
    newNode->son[1] = son1;
    newNode->son[2] = son2;
    newNode->son[3] = son3;
    return newNode;
}

void printAST(AST *node) {
    if(node) {
        printf("%s\n", node->symbol->string);
        printAST(node->son[0]);
        printAST(node->son[1]);
        printAST(node->son[2]);
        printAST(node->son[3]);
    }
}
