
#ifndef __ASTREE_H__
#define __ASTREE_H__

#include "hash.h"

#define MAX_SONS           4

#define AST_INTEGER        1
#define AST_REAL           2
#define AST_CHAR           3
#define AST_STRING         4
#define AST_IDENTIFIER     5
#define AST_ADD            6
#define AST_SUB            7
#define AST_MUL            8
#define AST_DIV            9
#define AST_LT             10
#define AST_GT             11
#define AST_NOT            12
#define AST_LE             13
#define AST_GE             14
#define AST_EQ             15
#define AST_NE             16
#define AST_AND            17
#define AST_OR             18
#define AST_LIST           19

#define AST_TYPE_BYTE      20
#define AST_TYPE_SHORT     21
#define AST_TYPE_LONG      22
#define AST_TYPE_FLOAT     23
#define AST_TYPE_DOUBLE    24

#define AST_DECL_LIST      25
#define AST_EXPR_LIST      26

#define AST_VAR_DECL       27
#define AST_ARY_DECL       28
#define AST_VAR_ASSIGN     29
#define AST_ARY_ASSIGN     30

#define AST_WHILE          31
#define AST_IF_ELSE        32
#define AST_IF             33
#define AST_RETURN         34
#define AST_PRINT          35
#define AST_READ           36
#define AST_BLOCK          37
#define AST_PARAM          38
#define AST_FUNC_HEADER    39
#define AST_FUNC_DECL      40
#define AST_CMD_LIST       41
#define AST_PARAM_LIST     42
#define AST_ARY_INDEX      43
#define AST_FUNC_CALL      44
#define AST_PARENS_EXPR    45
#define AST_LIT_LIST       46
#define AST_EMPTY_LIT_LIST 47

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

void printNode(AST *node);

void printAST(AST *node, int level);

void generateCode(FILE *output_file, AST *node);

#endif // __ASTREE_H__
