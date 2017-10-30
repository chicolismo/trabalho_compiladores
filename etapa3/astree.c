#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3) {
    AST *newNode;
    newNode = (AST *) calloc(1, sizeof(AST));
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

    if (node) {
        // Identacao
        for (i = 0; i < level; i++) {
            fprintf(stdout, "  ");
        }

        // Tipo do nodo
        switch (node->type) {
        case AST_SYMBOL: fprintf(stdout, "AST_SYMBOL: "); break;

        case AST_ADD: fprintf(stdout, "AST_ADD: "); break;

        case AST_SUB: fprintf(stdout, "AST_SUB: "); break;

        case AST_MUL: fprintf(stdout, "AST_MUL: "); break;

        case AST_DIV: fprintf(stdout, "AST_DIV: "); break;

        case AST_LT: fprintf(stdout, "AST_LESS: "); break;

        case AST_GT: fprintf(stdout, "AST_GREATER: "); break;

        case AST_NOT: fprintf(stdout, "AST_NOT: "); break;

        case AST_LE: fprintf(stdout, "AST_LE: "); break;

        case AST_GE: fprintf(stdout, "AST_GE: "); break;

        case AST_EQ: fprintf(stdout, "AST_EQ: "); break;

        case AST_NE: fprintf(stdout, "AST_NE: "); break;

        case AST_AND: fprintf(stdout, "AST_AND: "); break;

        case AST_OR: fprintf(stdout, "AST_OR: "); break;

        case AST_LIST: fprintf(stdout, "AST_LIST: "); break;

        case AST_VAR_DECL: fprintf(stdout, "AST_VAR_DECL: "); break;

        case AST_ARY_DECL: fprintf(stdout, "AST_ARY_DECL: "); break;

        case AST_DECL_LIST: fprintf(stdout, "AST_DECL_LIST: "); break;

        case AST_EXPR_LIST: fprintf(stdout, "AST_DECL_LIST: "); break;

        case AST_VAR_ASSIGN: fprintf(stdout, "AST_VAR_ASSIGN: "); break;

        case AST_ARY_ASSIGN: fprintf(stdout, "AST_ARY_ASSIGN: "); break;

        case AST_WHILE: fprintf(stdout, "AST_WHILE: "); break;

        case AST_IF_ELSE: fprintf(stdout, "AST_IF_ELSE: "); break;

        case AST_IF: fprintf(stdout, "AST_IF: "); break;

        case AST_RETURN: fprintf(stdout, "AST_RETURN: "); break;

        case AST_PRINT: fprintf(stdout, "AST_PRINT: "); break;

        case AST_READ: fprintf(stdout, "AST_READ: "); break;

        case AST_BLOCK: fprintf(stdout, "AST_BLOCK: "); break;

        case AST_PARAM: fprintf(stdout, "AST_PARAM: "); break;

        case AST_FUNC_HEADER: fprintf(stdout, "AST_FUNC_HEADER: "); break;

        case AST_FUNC_DECL: fprintf(stdout, "AST_FUNC_DECL: "); break;

        case AST_CMD_LIST: fprintf(stdout, "AST_CMD_LIST: "); break;

        case AST_PARAM_LIST: fprintf(stdout, "AST_PARAM_LIST: "); break;

        case AST_ARY_INDEX: fprintf(stdout, "AST_ARY_INDEX: "); break;

        case AST_FUNC_CALL: fprintf(stdout, "AST_FUNC_CALL: "); break;

        case AST_TYPE_BYTE: fprintf(stdout, "AST_TYPE_BYTE: "); break;

        case AST_TYPE_SHORT: fprintf(stdout, "AST_TYPE_SHORT: "); break;

        case AST_TYPE_LONG: fprintf(stdout, "AST_TYPE_LONG: "); break;

        case AST_TYPE_FLOAT: fprintf(stdout, "AST_TYPE_FLOAT: "); break;

        case AST_TYPE_DOUBLE: fprintf(stdout, "AST_TYPE_DOUBLE: "); break;

        default:
            fprintf(stdout, "UNKNOWN\n");
            break;
        }

        // Simbolo do nodo
        if (node->symbol) {
            fprintf(stdout, "%s\n", node->symbol->string);
        }
        else {
            /*fprintf(stdout, "0\n");*/
            fprintf(stdout, "\n");
        }

        // Aplica recursao para filhos do nodo
        for (i = 0; i < MAX_SONS; i++) {
            printAST(node->son[i], level + 1);
        }
        //++level;
    }
}

void generateCode(FILE *output_file, AST *node) {
    // TODO: Implementar a geração de código.

}
