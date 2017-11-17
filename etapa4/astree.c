#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "y.tab.h"

extern int getLineNumber();

AST *createAST(int type, HashNode *symbol, AST *son0, AST *son1, AST *son2, AST *son3) {
    AST *newNode;
    //newNode = (AST *) calloc(1, sizeof(AST));
    newNode = malloc(sizeof(AST));
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->lineNumber = getLineNumber();
    newNode->son[0] = son0;
    newNode->son[1] = son1;
    newNode->son[2] = son2;
    newNode->son[3] = son3;
    return newNode;
}

void printNode(AST *node) {
    switch (node->type) {
    case AST_SYMBOL:
        fprintf(stdout, "AST_SYMBOL: ");
        break;

    case AST_ADD:
        fprintf(stdout, "AST_ADD: ");
        break;

    case AST_SUB:
        fprintf(stdout, "AST_SUB: ");
        break;

    case AST_MUL:
        fprintf(stdout, "AST_MUL: ");
        break;

    case AST_DIV:
        fprintf(stdout, "AST_DIV: ");
        break;

    case AST_LT:
        fprintf(stdout, "AST_LESS: ");
        break;

    case AST_GT:
        fprintf(stdout, "AST_GREATER: ");
        break;

    case AST_NOT:
        fprintf(stdout, "AST_NOT: ");
        break;

    case AST_LE:
        fprintf(stdout, "AST_LE: ");
        break;

    case AST_GE:
        fprintf(stdout, "AST_GE: ");
        break;

    case AST_EQ:
        fprintf(stdout, "AST_EQ: ");
        break;

    case AST_NE:
        fprintf(stdout, "AST_NE: ");
        break;

    case AST_AND:
        fprintf(stdout, "AST_AND: ");
        break;

    case AST_OR:
        fprintf(stdout, "AST_OR: ");
        break;

    case AST_LIST:
        fprintf(stdout, "AST_LIST: ");
        break;

    case AST_VAR_DECL:
        fprintf(stdout, "AST_VAR_DECL: ");
        break;

    case AST_ARY_DECL:
        fprintf(stdout, "AST_ARY_DECL: ");
        break;

    case AST_DECL_LIST:
        fprintf(stdout, "AST_DECL_LIST: ");
        break;

    case AST_EXPR_LIST:
        fprintf(stdout, "AST_DECL_LIST: ");
        break;

    case AST_VAR_ASSIGN:
        fprintf(stdout, "AST_VAR_ASSIGN: ");
        break;

    case AST_ARY_ASSIGN:
        fprintf(stdout, "AST_ARY_ASSIGN: ");
        break;

    case AST_WHILE:
        fprintf(stdout, "AST_WHILE: ");
        break;

    case AST_IF_ELSE:
        fprintf(stdout, "AST_IF_ELSE: ");
        break;

    case AST_IF:
        fprintf(stdout, "AST_IF: ");
        break;

    case AST_RETURN:
        fprintf(stdout, "AST_RETURN: ");
        break;

    case AST_PRINT:
        fprintf(stdout, "AST_PRINT: ");
        break;

    case AST_READ:
        fprintf(stdout, "AST_READ: ");
        break;

    case AST_BLOCK:
        fprintf(stdout, "AST_BLOCK: ");
        break;

    case AST_PARAM:
        fprintf(stdout, "AST_PARAM: ");
        break;

    case AST_FUNC_DECL:
        fprintf(stdout, "AST_FUNC_DECL: ");
        break;

    case AST_CMD_LIST:
        fprintf(stdout, "AST_CMD_LIST: ");
        break;

    case AST_PARAM_LIST:
        fprintf(stdout, "AST_PARAM_LIST: ");
        break;

    case AST_ARY_INDEX:
        fprintf(stdout, "AST_ARY_INDEX: ");
        break;

    case AST_FUNC_CALL:
        fprintf(stdout, "AST_FUNC_CALL: ");
        break;

    case AST_TYPE_BYTE:
        fprintf(stdout, "AST_TYPE_BYTE: ");
        break;

    case AST_TYPE_SHORT:
        fprintf(stdout, "AST_TYPE_SHORT: ");
        break;

    case AST_TYPE_LONG:
        fprintf(stdout, "AST_TYPE_LONG: ");
        break;

    case AST_TYPE_FLOAT:
        fprintf(stdout, "AST_TYPE_FLOAT: ");
        break;

    case AST_TYPE_DOUBLE:
        fprintf(stdout, "AST_TYPE_DOUBLE: ");
        break;

    case AST_LIT_LIST:
        fprintf(stdout, "AST_LIT_LIST: ");
        break;

    case AST_EMPTY_LIT_LIST:
        fprintf(stdout, "AST_EMPTY_LIT_LIST: ");
        break;

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
}

// printAST {{{
void printAST(AST *node, int level) {
    int i;

    if (node) {
        // Indentação
        for (i = 0; i < level; i++) {
            fprintf(stdout, "  ");
        }

        printNode(node);

        // Aplica recursao para filhos do nodo
        for (i = 0; i < MAX_SONS; i++) {
            printAST(node->son[i], level + 1);
        }
    }
}
// }}}

/*#define d(text) printf("%s\n", (text))*/
#define d(text)

void generateCode(FILE *out, AST *node) {
    // TODO: Implementar a geração de código.

    if (out == NULL) {
        fprintf(stderr, "Arquivo de saída é inválido\n");
        return;
    }

    if (node == NULL) {
        return;
    }

    switch (node->type) {
    case AST_SYMBOL:
        d("symbol");

        if (node->symbol) {
            fprintf(out, "%s", node->symbol->string);
        }
        else {
            fprintf(out, "<<Erro ao ler o símbolo no nodo>>");
        }
        break;

    case AST_ADD:
        d("add");

        generateCode(out, node->son[0]);
        fprintf(out, " + ");
        generateCode(out, node->son[1]);
        break;

    case AST_SUB:
        d("sub");

        generateCode(out, node->son[0]);
        fprintf(out, " - ");
        generateCode(out, node->son[1]);
        break;

    case AST_MUL:
        d("mul");

        generateCode(out, node->son[0]);
        fprintf(out, " * ");
        generateCode(out, node->son[1]);
        break;

    case AST_DIV:
        d("div");

        generateCode(out, node->son[0]);
        fprintf(out, " / ");
        generateCode(out, node->son[1]);
        break;

    case AST_LT:
        d("less than");

        generateCode(out, node->son[0]);
        fprintf(out, " < ");
        generateCode(out, node->son[1]);
        break;

    case AST_GT:
        d("greater than");

        generateCode(out, node->son[0]);
        fprintf(out, " > ");
        generateCode(out, node->son[1]);
        break;

    case AST_NOT:
        d("not");

        fprintf(out, "!");
        generateCode(out, node->son[0]);
        break;

    case AST_LE:
        d("less than or equal to");

        generateCode(out, node->son[0]);
        fprintf(out, " <= ");
        generateCode(out, node->son[1]);
        break;

    case AST_GE:
        d("greater than or equal to");

        generateCode(out, node->son[0]);
        fprintf(out, " >= ");
        generateCode(out, node->son[1]);
        break;

    case AST_EQ:
        d("equal");

        generateCode(out, node->son[0]);
        fprintf(out, " == ");
        generateCode(out, node->son[1]);
        break;

    case AST_NE:
        d("not equal");

        generateCode(out, node->son[0]);
        fprintf(out, " != ");
        generateCode(out, node->son[1]);
        break;

    case AST_AND:
        d("and");

        generateCode(out, node->son[0]);
        fprintf(out, " && ");
        generateCode(out, node->son[1]);
        break;

    case AST_OR:
        d("or");

        generateCode(out, node->son[0]);
        fprintf(out, " || ");
        generateCode(out, node->son[1]);
        break;

    case AST_LIST:
        d("ast_list");

        generateCode(out, node->son[0]);
        fprintf(out, ", ");
        generateCode(out, node->son[1]);
        break;

    case AST_VAR_DECL:
        d("ast_var_decl");

        generateCode(out, node->son[0]);
        fprintf(out, " : ");
        generateCode(out, node->son[1]);
        fprintf(out, " = ");
        generateCode(out, node->son[2]);
        fprintf(out, ";\n");
        break;

    case AST_ARY_DECL:
        d("ast_ary_decl");

        generateCode(out, node->son[0]);
        fprintf(out, " : ");
        generateCode(out, node->son[1]);
        fprintf(out, "[");
        generateCode(out, node->son[2]);
        if (node->son[3]->type == AST_EMPTY_LIT_LIST) {
            fprintf(out, "]");
        }
        else {
            fprintf(out, "] ");
        }
        generateCode(out, node->son[3]);
        fprintf(out, ";\n");
        break;

    case AST_DECL_LIST:
        d("ast_decl_list");

        generateCode(out, node->son[0]);
        generateCode(out, node->son[1]);
        break;

    case AST_EXPR_LIST:
        d("ast_expr_list");

        generateCode(out, node->son[0]);
        fprintf(out, ", ");
        generateCode(out, node->son[1]);
        break;

    case AST_VAR_ASSIGN:
        d("ast_var_assign");

        generateCode(out, node->son[0]);
        fprintf(out, " = ");
        generateCode(out, node->son[1]);
        break;

    case AST_ARY_ASSIGN:
        d("ast_ary_assign");

        generateCode(out, node->son[0]);
        fprintf(out, "[");
        generateCode(out, node->son[1]);
        fprintf(out, "] = ");
        generateCode(out, node->son[2]);
        break;

    case AST_WHILE:
        d("ast_while");

        fprintf(out, "while (");
        generateCode(out, node->son[0]);
        fprintf(out, ") ");
        generateCode(out, node->son[1]);
        break;

    case AST_IF_ELSE:
        d("ast_if_else");

        fprintf(out, "if (");
        generateCode(out, node->son[0]);
        fprintf(out, ") then\n"); // Precisa do "\n"
        generateCode(out, node->son[1]);
        fprintf(out, " else\n");  // Idem
        generateCode(out, node->son[2]);
        break;

    case AST_IF:
        d("ast_if");

        fprintf(out, "if (");
        generateCode(out, node->son[0]);
        fprintf(out, ") then\n"); // Precisa do "\n"
        generateCode(out, node->son[1]);
        break;

    case AST_RETURN:
        d("ast_return");

        fprintf(out, "return ");
        generateCode(out, node->son[0]);
        break;

    case AST_PRINT:
        d("ast_print");

        fprintf(out, "print ");
        generateCode(out, node->son[0]);
        break;

    case AST_READ:
        d("ast_read");

        fprintf(out, "read > ");
        generateCode(out, node->son[0]);
        break;

    case AST_BLOCK:
        d("ast_block");

        fprintf(out, "{ ");
        generateCode(out, node->son[0]);
        fprintf(out, " }");
        break;

    case AST_PARAM:
        d("ast_param");

        generateCode(out, node->son[0]);
        fprintf(out, " : ");
        generateCode(out, node->son[1]);
        break;

    case AST_FUNC_DECL:
        d("ast_func_decl");

        fprintf(out, "(");
        generateCode(out, node->son[0]);
        fprintf(out, ") ");
        generateCode(out, node->son[1]);
        fprintf(out, "(");
        generateCode(out, node->son[2]);
        fprintf(out, ")");
        generateCode(out, node->son[1]);
        break;

    case AST_LIT_LIST:
        generateCode(out, node->son[0]);
        if (node->son[1]->type != AST_EMPTY_LIT_LIST) {
            fprintf(out, " ");
        }
        generateCode(out, node->son[1]);
        break;

    case AST_CMD_LIST:
        d("ast_cmd_decl");
        generateCode(out, node->son[0]);
        fprintf(out, ";\n");
        generateCode(out, node->son[1]);
        break;

    case AST_PARAM_LIST:
        d("ast_param_decl");

        generateCode(out, node->son[0]);
        fprintf(out, ", ");
        generateCode(out, node->son[1]);
        break;

    case AST_ARY_INDEX:
        d("ast_ary_index");

        generateCode(out, node->son[0]);
        fprintf(out, "[");
        generateCode(out, node->son[1]);
        fprintf(out, "]");
        break;

    case AST_FUNC_CALL:
        d("ast_func_call");

        generateCode(out, node->son[0]);
        fprintf(out, "(");
        generateCode(out, node->son[1]);
        fprintf(out, ")");
        break;

    case AST_PARENS_EXPR:
        d("ast_parens_expr");

        fprintf(out, "(");
        generateCode(out, node->son[0]);
        fprintf(out, ")");
        break;

    case AST_TYPE_BYTE:
        d("ast_type_byte");

        fprintf(out, "byte");
        break;

    case AST_TYPE_SHORT:
        d("ast_type_short");

        fprintf(out, "short");
        break;

    case AST_TYPE_LONG:
        d("ast_type_long");

        fprintf(out, "long");
        break;

    case AST_TYPE_FLOAT:
        d("ast_type_float");

        fprintf(out, "float");
        break;

    case AST_TYPE_DOUBLE:
        d("ast_type_double");

        fprintf(out, "double");
        break;
    }
}
