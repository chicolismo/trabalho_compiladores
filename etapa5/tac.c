#include "tac.h"
#include <stdlib.h>
#include <stdio.h>

// Cria um TAC (obviamente)
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

    TAC *temp2 = tac2;
    while (temp2->prev != NULL) {
        temp2 = temp2->prev;
    }

    TAC *temp1 = tac1;
    while (temp1->next != NULL) {
        temp1 = temp1->next;
    }
    temp2->prev = temp1;
    temp1->next = temp2;

    while (temp1->prev != NULL) {
        temp1 = temp1->prev;
    }

    return temp1;
}

// Imprime um TAC
void TAC_print(TAC *tac) {
    if (tac == NULL) {
        return;
    }

    fprintf(stdout, "TAC(");

    switch (tac->type) {

    case TAC_SYMBOL:       return;
    case TAC_LABEL:        fprintf(stdout, "TAC_LABEL"); break;
    case TAC_MOVE:         fprintf(stdout, "TAC_MOVE"); break;
    case TAC_ADD:          fprintf(stdout, "TAC_ADD"); break;
    case TAC_SUB:          fprintf(stdout, "TAC_SUB"); break;
    case TAC_MUL:          fprintf(stdout, "TAC_MUL"); break;
    case TAC_DIV:          fprintf(stdout, "TAC_DIV"); break;
    case TAC_LT:           fprintf(stdout, "TAC_LT"); break;
    case TAC_GT:           fprintf(stdout, "TAC_GT"); break;
    case TAC_LE:           fprintf(stdout, "TAC_LE"); break;
    case TAC_GE:           fprintf(stdout, "TAC_GE"); break;
    case TAC_EQ:           fprintf(stdout, "TAC_EQ"); break;
    case TAC_NE:           fprintf(stdout, "TAC_NE"); break;
    case TAC_AND:          fprintf(stdout, "TAC_AND"); break;
    case TAC_OR:           fprintf(stdout, "TAC_OR"); break;
    case TAC_NOT:          fprintf(stdout, "TAC_NOT"); break;
    case TAC_READ:         fprintf(stdout, "TAC_READ"); break;
    case TAC_RET:          fprintf(stdout, "TAC_RET"); break;
    case TAC_PRINT:        fprintf(stdout, "TAC_PRINT"); break;
    case TAC_BEGINFUN:     fprintf(stdout, "TAC_BEGINFUN"); break;
    case TAC_ENDFUN:       fprintf(stdout, "TAC_ENDFUN"); break;
    case TAC_JZ:           fprintf(stdout, "TAC_IFZ"); break;
    case TAC_JMP:          fprintf(stdout, "TAC_JUMP"); break;
    case TAC_CALL:         fprintf(stdout, "TAC_CALL"); break;
    case TAC_VAR_DECL:     fprintf(stdout, "TAC_VAR_DECL"); break;
    case TAC_ARY_DECL:     fprintf(stdout, "TAC_ARY_DECL"); break;
    case TAC_ASSIGN:       fprintf(stdout, "TAC_ASSIGN"); break;
    case TAC_ARRAY_ASSIGN: fprintf(stdout, "TAC_ARRAY_ASSIGN"); break;
//    case TAC_ARRAY_INDEX:  fprintf(stdout, "TAC_ARRAY_INDEX"); break;
//    case TAC_EMPTY_LIST:   fprintf(stdout, "TAC_EMPTY_LIST"); break;
    default:               fprintf(stderr, "!!TAC NÃO RECONHECIDO!!\n"); break;
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
    TAC *prev = last->prev;
    last->prev = NULL;

    if (prev == NULL) {
        return last;
    }
    else {
        return TAC_join(last, TAC_reverse_list(prev));
    }
}

void TAC_print_forward(TAC *tac) {
    while (tac != NULL) {
        TAC_print(tac);
        tac = tac->next;
    }
}

void TAC_print_backward(TAC *tac) {
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
    case AST_LE: type = TAC_LE; break;
    case AST_GE: type = TAC_GE; break;
    case AST_EQ: type = TAC_EQ; break;
    case AST_NE: type = TAC_NE; break;
    case AST_AND: type = TAC_AND; break;
    case AST_OR: type = TAC_OR; break;
    case AST_NOT: type = TAC_NOT; break;
    default:
        fprintf(stderr, "ERRO: operador binário não reconhecido\n");
        printNode(node);
        exit(1);
    }
    
    TAC *tac = TAC_create(type, makeTemp(),
                          op1? op1->res : NULL,
                          op2? op2->res : NULL);

    return TAC_join(TAC_join(op1, op2), tac);
}

// Cria um TAC para instrução "print"
TAC *TAC_make_print(TAC *arg) {
    return TAC_create(TAC_PRINT, arg->res, NULL, NULL);
}

// Cria um TAC para instrução "read"
TAC *TAC_make_read(TAC *expression) {
    return TAC_create(TAC_READ, expression->res, NULL, NULL);
}

// Cria o conjunto de TACs que representam um "while"
TAC *TAC_make_while(TAC *condition, TAC *body) {
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
                        TAC_join(goto_begin, end_label)))));
}

// if (cond) then (if_true);
TAC *TAC_make_if(TAC *condition, TAC *if_true) {
    HashNode *label = makeLabel();
    TAC *jump = TAC_create(TAC_JZ, label, condition == NULL ? NULL : condition->res, NULL);
    TAC *label_tac = TAC_create(TAC_LABEL, label, NULL, NULL);
    return TAC_join(TAC_join(TAC_join(condition, jump), if_true), label_tac);
}

// if (cond) then (if_true) else (if_false);
TAC *TAC_make_if_else(TAC *condition, TAC *if_true, TAC *if_false) {
    HashNode *else_label = makeLabel();
    HashNode *end_label = makeLabel();
    TAC *jz_tac = TAC_create(TAC_JZ, else_label, condition == NULL ? NULL : condition->res, NULL);
    TAC *else_tac = TAC_create(TAC_LABEL, else_label, NULL, NULL);
    TAC *jmp_tac = TAC_create(TAC_JMP, end_label, NULL, NULL);
    TAC *end_tac = TAC_create(TAC_LABEL, end_label, NULL, NULL);

    return
        TAC_join(condition,
            TAC_join(jz_tac,
                TAC_join(if_true,
                    TAC_join(jmp_tac,
                        TAC_join(else_tac,
                            TAC_join(if_false, end_tac))))));
}

// return (expr)
TAC *TAC_make_return(TAC *expression) {
    TAC *return_tac = TAC_create(TAC_RET, expression->res, NULL, NULL);
    return TAC_join(expression, return_tac);
}

TAC *TAC_make_fun_declaration(AST *node, TAC *fn_name, TAC *fn_params, TAC *fn_body) {
    TAC *begin_fun_tac = TAC_create(TAC_BEGINFUN, node->symbol, NULL, NULL);
    TAC *end_fun_tac = TAC_create(TAC_ENDFUN, node->symbol, NULL, NULL);

    // begin name params body end
    return
        TAC_join(begin_fun_tac,
             TAC_join(fn_name,
                TAC_join(fn_params,
                    TAC_join(fn_body, end_fun_tac))));
}

TAC *TAC_make_param(AST *node) {
    return TAC_create(TAC_PARAM, node->son[0]->symbol, NULL, NULL);
}

TAC *TAC_make_fun_call(AST *node, TAC *fn_name, TAC *args) {
    HashNode *temp = makeTemp();
    TAC *func_call = TAC_create(TAC_CALL, temp, fn_name->res, NULL);
    return TAC_join(args, func_call);
}

TAC *TAC_make_assign(AST *node, TAC *symbol, TAC *expr) {
    TAC *assign_tac = TAC_create(TAC_ASSIGN, node->symbol, NULL, NULL);
    return TAC_join(symbol, TAC_join(expr, assign_tac));
}

TAC *TAC_make_ary_assign(AST *node, TAC *symbol, TAC *index_expr, TAC *val_expr) {
    TAC *ary_assign_tac = TAC_create(TAC_ARRAY_ASSIGN, node->symbol, NULL, NULL);
    return TAC_join(symbol, TAC_join(index_expr, TAC_join(val_expr, ary_assign_tac)));
}

TAC *TAC_make_ary_index(AST *node, TAC *symbol, TAC *index_expr) {
    TAC *ary_index_tac = TAC_create(TAC_ARRAY_INDEX, node->symbol, NULL, NULL);
    return TAC_join(symbol, TAC_join(index_expr, ary_index_tac));
}

TAC *TAC_generate_code(AST *node) {
    if (node == NULL) {
        return NULL;
    }

    TAC *codes[MAX_SONS];

    // Chama recursivamente em cada um dos filhos do nodo.
    int i;
    for (i = 0; i < MAX_SONS; ++i) {
        codes[i] = TAC_generate_code(node->son[i]);
    }

    switch (node->type) {

    case AST_SYMBOL:
        return TAC_create(TAC_SYMBOL, node->symbol, NULL, NULL);

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
    case AST_NOT:
        return TAC_make_binary_operator(node, codes[0], codes[1]);

    case AST_FUNC_DECL:
        return TAC_make_fun_declaration(node, codes[1], codes[2], codes[3]);

    case AST_LIT_LIST:
        // Temos que fazer invertido, para a lista vazia ficar no fim da pilha
        return TAC_join(codes[1], codes[0]);

    case AST_EMPTY_LIT_LIST:
        return TAC_create(TAC_EMPTY_LIST, node->symbol, NULL, NULL);

    // Atribuições
    case AST_VAR_ASSIGN:
        // codes[0] -> symbol (a variável)
        // codes[1] -> expr (o valor sendo atribuido)
        // printf("var assign\n");
        // return TAC_join(codes[1], TAC_create(TAC_ASSIGN, node->symbol, codes[0] ? codes[0]->res : NULL, NULL));
        return TAC_make_assign(node, codes[0], codes[1]);

    case AST_ARY_ASSIGN:
        // codes[0] -> symbol (o vetor)
        // codes[1] -> expr (vai ser o indice)
        // codes[2] -> expr (o valor a ser salvo no indice)
        return TAC_make_ary_assign(node, codes[0], codes[1], codes[2]);

    case AST_ARY_INDEX:
        // codes[0] -> symbol (o vetor)
        // codes[1] -> expr (expressao do indice)
        return TAC_make_ary_index(node, codes[0], codes[1]);

    case AST_WHILE:
        return TAC_make_while(codes[0], codes[1]);

    case AST_IF_ELSE:
        return TAC_make_if_else(codes[0], codes[1], codes[2]);

    case AST_IF:
        return TAC_make_if(codes[0], codes[1]);

    case AST_RETURN:
        return TAC_make_return(codes[0]);

    case AST_PRINT:
        // codes[0] -> print_args
        return codes[0];

    case AST_PRINT_ARGS:
        if (codes[1]->type == TAC_SYMBOL)
            return TAC_join(TAC_make_print(codes[0]),
                            TAC_make_print(codes[1]));
        else
            return TAC_join(TAC_make_print(codes[0]), codes[1]);

    case AST_READ:
        return TAC_make_read(codes[0]);

    case AST_PARAM:
        //res = codes[0];
        //TAC_make_param(node, codes[0]);
        return TAC_make_param(node);

    case AST_FUNC_CALL:
        // codes[0] -> symbol
        // codes[1] -> args
        return TAC_make_fun_call(node, codes[0], codes[1]);

    case AST_ARG_LIST:
        return TAC_join(codes[1], codes[0]);

    default:
        return TAC_join(TAC_join(TAC_join(codes[0], codes[1]), codes[2]), codes[3]);
    }
}
