
#ifndef __ASTREE_H__
#define __ASTREE_H__

#include "hash.h"

#define MAX_SONS 4

typedef struct ASTreeNode {
    int type;
    HashNode *symbol;
    struct ASTreeNode *son[MAX_SONS];
} AST;

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void printAST(AST *node);

#endif // __ASTREE_H__
