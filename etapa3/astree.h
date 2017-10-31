
#ifndef __ASTREE_H__
#define __ASTREE_H__

#include "hash.h"

#define MAX_SONS    4

#define AST_SYMBOL  1
#define AST_ADD     2
#define AST_SUB     3
#define AST_MUL     4
#define AST_DIV     5
#define AST_LT      6
#define AST_GT      7
#define AST_NOT     8
#define AST_LE      9
#define AST_GE      10
#define AST_EQ      11
#define AST_NE      12
#define AST_AND     13
#define AST_OR      14
#define AST_LIST    15

#define AST_TYPE_BYTE 16
#define AST_TYPE_SHORT 17
#define AST_TYPE_LONG 18
#define AST_TYPE_FLOAT 19
#define AST_TYPE_DOUBLE 20

#define AST_DECL_LIST 21
#define AST_EXPR_LIST 22

#define AST_VAR_DECL 23
#define AST_ARY_DECL 24
#define AST_VAR_ASSIGN 25
#define AST_ARY_ASSIGN 26

#define AST_WHILE 27
#define AST_IF_ELSE 28
#define AST_IF 29
#define AST_RETURN 30
#define AST_PRINT 31
#define AST_READ 32
#define AST_BLOCK 33
#define AST_PARAM 34
#define AST_FUNC_HEADER 35
#define AST_FUNC_DECL 36
#define AST_CMD_LIST 37
#define AST_PARAM_LIST 38
#define AST_ARY_INDEX 40
#define AST_FUNC_CALL 41
#define AST_PARENS_EXPR 42
#define AST_LIT_LIST 43
#define AST_EMPTY_LIT_LIST 44

typedef struct ASTreeNode {
    int type;
    HashNode *symbol;
    struct ASTreeNode *son[MAX_SONS];
} AST;

AST *createAST(
    int type,
    HashNode *symbol,
    AST *son0,
    AST *son1,
    AST *son2,
    AST *son3
);

void printAST(AST *node, int level);

void generateCode(FILE *output_file, AST *node);

#endif // __ASTREE_H__
