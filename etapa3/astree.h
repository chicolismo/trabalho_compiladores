
#ifndef __ASTREE_H__
#define __ASTREE_H__

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL	1
#define AST_ADD		2
#define AST_MULT	3

typedef struct ASTreeNode {
    int type;
    HashNode *symbol;
    struct ASTreeNode *son[MAX_SONS];
} AST;

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void printAST(AST *node, int level);

#endif // __ASTREE_H__
