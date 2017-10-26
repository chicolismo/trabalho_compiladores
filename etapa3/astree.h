
#ifndef __ASTREE_H__
#define __ASTREE_H__

#include "hash.h"

#define MAX_SONS    4

#define AST_SYMBOL  1
#define AST_ADD     2
#define AST_SUB     3
#define AST_MUL     4
#define AST_DIV     5
#define AST_LESS    6
#define AST_GREATER 7
#define AST_NOT     8
#define AST_LE      9
#define AST_GE      10
#define AST_EQ      11
#define AST_NE      12
#define AST_AND     13
#define AST_OR      14
#define AST_LIST    15

typedef struct ASTreeNode {
    int type;
    HashNode *symbol;
    struct ASTreeNode *son[MAX_SONS];
} AST;

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3);
void printAST(AST *node, int level);

#endif // __ASTREE_H__
