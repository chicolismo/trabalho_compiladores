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

void printAST(AST *node, int level) {
	int i;

    if(node) {
		// Identacao
		for(i=0; i<level; i++)
			fprintf(stderr, "  ");

		// Tipo do nodo
		switch(node->type) {
			case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL:"); break;
			case AST_ADD: fprintf(stderr, "AST_ADD:"); break;
			case AST_MULT: fprintf(stderr, "AST_MULT:"); break;
			default: fprintf(stderr, "UNKNOWN\n"); break;
		}

		// Simbolo do nodo
		if(node->symbol)
			fprintf(stderr, "%s\n", node->symbol->string);
		else
			fprintf(stderr, "0\n");

		// Aplica recursao para filhos do nodo
		for(i=0; i<MAX_SONS; i++)
			printAST(node->son[i], ++level);
    }
}
