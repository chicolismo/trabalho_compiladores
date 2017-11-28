#include "code.h"
#include <stdlib.h>

TAC *generate_code(AST *node) {

    if (node == NULL) {
        return NULL;
    }

    TAC *code[MAX_SONS];
    HashNode *label;

    int i;
    for (i = 0; i < MAX_SONS; ++i) {
        if (node->son[i] != NULL) {
            code[i] = generate_code(node->son[i]);
        }
        else {
            code[i] = NULL;
        }
    }

    // TODO: Falta descobrir como faz isso.
    switch (node->type) {
    case AST_SYMBOL:
        ;
        break;
    case AST_ADD:
        ;
        break;
    case AST_SUB:
        ;
        break;
    case AST_MUL:
        ;
        break;
    case AST_DIV:
        ;
        break;
    case AST_LT:
        ;
        break;
    case AST_GT:
        ;
        break;
    case AST_NOT:
        ;
        break;
    case AST_LE:
        ;
        break;
    case AST_GE:
        ;
        break;
    case AST_EQ:
        ;
        break;
    case AST_NE:
        ;
        break;
    case AST_AND:
        ;
        break;
    case AST_OR:
        ;
        break;
    case AST_LIST:
        ;
        break;
    case AST_TYPE_BYTE:
        ;
        break;
    case AST_TYPE_SHORT:
        ;
        break;
    case AST_TYPE_LONG:
        ;
        break;
    case AST_TYPE_FLOAT:
        ;
        break;
    case AST_TYPE_DOUBLE:
        ;
        break;
    case AST_DECL_LIST:
        ;
        break;
    case AST_EXPR_LIST:
        ;
        break;
    case AST_VAR_DECL:
        ;
        break;
    case AST_ARY_DECL:
        ;
        break;
    case AST_VAR_ASSIGN:
        ;
        break;
    case AST_ARY_ASSIGN:
        ;
        break;
    case AST_WHILE:
        ;
        break;
    case AST_IF_ELSE:
        ;
        break;
    case AST_IF:
        ;
        break;
    case AST_RETURN:
        ;
        break;
    case AST_PRINT:
        ;
        break;
    case AST_READ:
        ;
        break;
    case AST_BLOCK:
        ;
        break;
    case AST_PARAM:
        ;
        break;
    case AST_FUNC_DECL:
        ;
        break;
    case AST_CMD_LIST:
        ;
        break;
    case AST_PARAM_LIST:
        ;
        break;
    case AST_ARY_INDEX:
        ;
        break;
    case AST_FUNC_CALL:
        ;
        break;
    case AST_PARENS_EXPR:
        ;
        break;
    case AST_LIT_LIST:
        ;
        break;
    case AST_EMPTY_LIT_LIST:
        ;
        break;
    }
}
