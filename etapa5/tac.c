#include "tac.h"
#include <stdlib.h>
#include <stdio.h>
// Cria um TAC
TAC *TAC_create(int type, HashNode *res, HashNode *op1, HashNode *op2) {
    TAC *tac = malloc(sizeof(TAC));
    tac->type = type;
    tac->res = res;
    tac->op1 = op1;
    tac->op2 = op2;
    return tac;
}


// Une dois TACs
TAC *TAC_join(TAC *tac1, TAC *tac2) {
    if (tac1 == NULL) {
        return tac2;
    }
    else if (tac2 == NULL) {
        return tac1;
    }

    TAC *temp = tac2;
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    temp->prev = tac1;
    tac1->next = temp; // ?
    return tac2;
}


// Imprime um TAC
void TAC_print(TAC *tac) {
    if (tac == NULL) {
        return;
    }

    fprintf(stdout, "TAC(");

    switch (tac->type) {

    case TAC_SYMBOL:
        fprintf(stdout, "TAC_SYMBOL");
        break;
    case TAC_LABEL:
        fprintf(stdout, "TAC_LABEL");
        break;
    case TAC_MOVE:
        fprintf(stdout, "TAC_MOVE");
        break;
    case TAC_ADD:
        fprintf(stdout, "TAC_ADD");
        break;
    case TAC_SUB:
        fprintf(stdout, "TAC_SUB");
        break;
    case TAC_MUL:
        fprintf(stdout, "TAC_MUL");
        break;
    case TAC_DIV:
        fprintf(stdout, "TAC_DIV");
        break;
    case TAC_LT:
        fprintf(stdout, "TAC_LT");
        break;
    case TAC_GT:
        fprintf(stdout, "TAC_GT");
        break;
    case TAC_LE:
        fprintf(stdout, "TAC_LE");
        break;
    case TAC_GE:
        fprintf(stdout, "TAC_GE");
        break;
    case TAC_EQ:
        fprintf(stdout, "TAC_EQ");
        break;
    case TAC_NE:
        fprintf(stdout, "TAC_NE");
        break;
    case TAC_AND:
        fprintf(stdout, "TAC_AND");
        break;
    case TAC_OR:
        fprintf(stdout, "TAC_OR");
        break;
    case TAC_NOT:
        fprintf(stdout, "TAC_NOT");
        break;
    case TAC_READ:
        fprintf(stdout, "TAC_READ");
        break;
    case TAC_RET:
        fprintf(stdout, "TAC_RET");
        break;
    case TAC_PRINT:
        fprintf(stdout, "TAC_PRINT");
        break;
    case TAC_BEGINFUN:
        fprintf(stdout, "TAC_BEGINFUN");
        break;
    case TAC_ENDFUN:
        fprintf(stdout, "TAC_ENDFUN");
        break;
    case TAC_JZ:
        fprintf(stdout, "TAC_IFZ");
        break;
    case TAC_JMP:
        fprintf(stdout, "TAC_JUMP");
        break;
    case TAC_CALL:
        fprintf(stdout, "TAC_CALL");
        break;
    case TAC_ARG:
        fprintf(stdout, "TAC_ARG");
        break;
    default:
        fprintf(stderr, "!!TAC NÃO RECONHECIDO!!");
        break;
    }

    // Imprime os membros do TAC, se houver
    if (tac->res != NULL) {
        fprintf(stdout, ", %s", tac->res->string);
    }
    else {
        fprintf(stdout, ", NULL");
    }

    if (tac->op1 != NULL) {
        fprintf(stdout, ", %s", tac->op1->string);
    }
    else {
        fprintf(stdout, ", NULL");
    }

    if (tac->op2 != NULL) {
        fprintf(stdout, ", %s", tac->op2->string);
    }
    else {
        fprintf(stdout, ", NULL");
    }

    fprintf(stdout, ")\n");
}

// Funções auxiliares

// Retorna o primeiro elemento da lista de TACs.
TAC *TAC_get_first(TAC *tac) {
    while (tac->prev != NULL) {
        tac = tac->prev;
    }
    return tac;
}

// Retorna o último elemento da lista de TACs
TAC *TAC_get_last(TAC *tac) {
    while (tac->next != NULL) {
        tac = tac->next;
    }
    return tac;
}

// Inverte a lista duplamente encadeada de TACs.
// Presume que o argumento seja o último elemento da lista.
TAC *TAC_reverse_list(TAC *last) {
    if (last == NULL) {
        return NULL;
    }

    /*TAC *last = tac;*/
    /*TAC *prev = tac->prev;*/
    TAC *prev = last->prev;

    last->prev = NULL;
    /*last->next = NULL;*/

    if (prev == NULL) {
        return last;
    }
    else {
        return TAC_join(last, TAC_reverse_list(prev));
    }
}

void TAC_print_forward(TAC *tac) {
    fprintf(stdout, "Printing Forward\n");

    while (tac != NULL) {
        fprintf(stdout, "Printing TAC\n");
        TAC_print(tac);
        tac = tac->next;
    }
}

void TAC_print_backward(TAC *tac) {
    fprintf(stdout, "Printing Backward\n");

    while (tac != NULL) {
        TAC_print(tac);
        tac = tac->prev;
    }
}

// Cria TACs de instruções de operações binárias (e unária)
TAC *TAC_make_binary_operator(AST *node, TAC *op1, TAC *op2) {
    int type;
    switch (node->type) {
    case AST_ADD: type = TAC_ADD; break;
    case AST_SUB: type = TAC_SUB; break;
    case AST_MUL: type = TAC_MUL; break;
    case AST_DIV: type = TAC_DIV; 
    case AST_LT: type = TAC_LT; break;
    case AST_GT: type = TAC_GT; break; 
    case AST_NOT: type = TAC_NOT; break;
    case AST_LE: type = TAC_LE; break;
    case AST_GE: type = TAC_GE; break;
    case AST_EQ: type = TAC_EQ; break;
    case AST_NE: type = TAC_NE; break;
    case AST_AND: type = TAC_AND; break;
    case AST_OR: type = TAC_OR; break;
    default:
        fprintf(stderr, "ERRO: operador binário não reconhecido\n");
        printNode(node);
        exit(1);
    }
    HashNode *temp_result = makeTemp(); // Para ser o resultado da operação

    TAC *tac = TAC_create(type,
                          temp_result,
                          op1 == NULL ? NULL : op1->res,
                          op2 == NULL ? NULL : op2->res);

    return TAC_join(TAC_join(op1, op2), tac);
}

// Cria um TAC para instrução "print"
TAC *TAC_make_print(AST *node, TAC *tac) {
    if (node->type != AST_PRINT) {
        fprintf(stderr, "ERRO, o nodo não é do tipo AST_PRINT\n");
        printNode(node);
        exit(1);
    }

    return TAC_create(TAC_PRINT, node->symbol, NULL, NULL);
}

// Cria um TAC para instrução "read"
TAC *TAC_make_read(AST *node, TAC *tac) {
    if (node->type != AST_READ) {
        fprintf(stderr, "ERRO, o nodo não é do tipo AST_READ\n");
        printNode(node);
        exit(1);
    }

    return TAC_create(TAC_READ, node->symbol, NULL, NULL);
}

// Cria o conjunto de TACs que representam um "while"
TAC *TAC_make_while(AST *node, TAC *condition, TAC *body) {
    if (node->type != AST_WHILE) {
        fprintf(stderr, "Nodo não é do tipo AST_WHILE\n");
        printNode(node);
        exit(1);
    }

    HashNode *begin = makeLabel();
    HashNode *end = makeLabel();

    TAC *begin_label = TAC_create(TAC_LABEL, begin, NULL, NULL);
    TAC *end_label = TAC_create(TAC_LABEL, end, NULL, NULL);

    TAC *goto_end_if_zero = TAC_create(TAC_JZ,
                                       end,
                                       condition == NULL ? NULL : condition->res,
                                       NULL);

    TAC *goto_begin = TAC_create(TAC_JMP,
                                begin,
                                NULL,
                                NULL);

    return
        TAC_join(begin_label,
            TAC_join(condition,
                TAC_join(goto_end_if_zero,
                    TAC_join(body,
                        TAC_join(goto_begin,
                            end_label
                            )))));
}

/*
TAC *TAC_make_arg(AST *node, TAC *tac) {
}
*/

// TODO: Temos que terminar isto...
TAC *TAC_generate_code(AST *node) {
    if (node == NULL) {
        return NULL;
    }

    //fprintf(stdout, "Generating code for: ");
    //printNode(node);

    TAC *codes[MAX_SONS];
    TAC *res = NULL;

    // Chama recursivamente em cada um dos filhos do nodo.
    int i;
    for (i = 0; i < MAX_SONS; ++i) {
        codes[i] = TAC_generate_code(node->son[i]);
    }

    switch (node->type) {
    case AST_SYMBOL:
        res = TAC_create(TAC_SYMBOL, node->symbol, NULL, NULL);
        break;

    case AST_ADD:
    case AST_SUB:
    case AST_MUL:
    case AST_DIV:
    case AST_LT:
    case AST_GT:
    case AST_LE:
    case AST_GE:
    case AST_EQ:
    case AST_NE:
    case AST_AND:
    case AST_OR:
        res = TAC_make_binary_operator(node, codes[0], codes[1]);
        break;

    case AST_TYPE_BYTE:
    case AST_TYPE_SHORT:
    case AST_TYPE_LONG:
    case AST_TYPE_FLOAT:
    case AST_TYPE_DOUBLE:
        res = TAC_create(TAC_TYPE, node->symbol, NULL, NULL);
        break;

    case AST_DECL_LIST: 
        // res = TAC_join(codes[0], codes[1]); Não sei se é assim mesmo...
        break;

    case AST_PRINT_ARGS:
        ;
        break;

    case AST_VAR_DECL:
        // Temos que implementar isto aqui.
        break;

    case AST_FUNC_DECL:
        // Temos que implementar isto aqui também.
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
        res = TAC_make_while(node, codes[0], codes[1]);
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

    default:
        res = TAC_join(TAC_join(TAC_join(codes[0], codes[1]), codes[2]), codes[3]);
    }

    return res;
}
