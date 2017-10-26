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
			case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL: "); break;
			case AST_ADD: fprintf(stderr, "AST_ADD: "); break;
			case AST_SUB: fprintf(stderr, "AST_SUB: "); break;
			case AST_MUL: fprintf(stderr, "AST_MUL: "); break;
			case AST_DIV: fprintf(stderr, "AST_DIV: "); break;
			case AST_LESS: fprintf(stderr, "AST_LESS: "); break;
			case AST_GREATER: fprintf(stderr, "AST_GREATER: "); break;
			case AST_NOT: fprintf(stderr, "AST_NOT: "); break;
			case AST_LE: fprintf(stderr, "AST_LE: "); break;
			case AST_GE: fprintf(stderr, "AST_GE: "); break;
			case AST_EQ: fprintf(stderr, "AST_EQ: "); break;
			case AST_NE: fprintf(stderr, "AST_NE: "); break;
			case AST_AND: fprintf(stderr, "AST_AND: "); break;
			case AST_OR: fprintf(stderr, "AST_OR: "); break;
			case AST_LIST: fprintf(stderr, "AST_LIST: "); break;
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
