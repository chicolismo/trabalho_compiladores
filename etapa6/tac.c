#include "tac.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    char tac_string[TAC_STRING_SIZE] = "\0";

    switch (tac->type) {
    case TAC_SYMBOL:       return;
    case TAC_LABEL:        strcpy(tac_string, "TAC_LABEL"); break;
    case TAC_ADD:          strcpy(tac_string, "TAC_ADD"); break;
    case TAC_SUB:          strcpy(tac_string, "TAC_SUB"); break;
    case TAC_MUL:          strcpy(tac_string, "TAC_MUL"); break;
    case TAC_DIV:          strcpy(tac_string, "TAC_DIV"); break;
    case TAC_LT:           strcpy(tac_string, "TAC_LT"); break;
    case TAC_GT:           strcpy(tac_string, "TAC_GT"); break;
    case TAC_LE:           strcpy(tac_string, "TAC_LE"); break;
    case TAC_GE:           strcpy(tac_string, "TAC_GE"); break;
    case TAC_EQ:           strcpy(tac_string, "TAC_EQ"); break;
    case TAC_NE:           strcpy(tac_string, "TAC_NE"); break;
    case TAC_AND:          strcpy(tac_string, "TAC_AND"); break;
    case TAC_OR:           strcpy(tac_string, "TAC_OR"); break;
    case TAC_NOT:          strcpy(tac_string, "TAC_NOT"); break;
    case TAC_READ:         strcpy(tac_string, "TAC_READ"); break;
    case TAC_PRINT:        strcpy(tac_string, "TAC_PRINT"); break;
    case TAC_RET:          strcpy(tac_string, "TAC_RET"); break;
    case TAC_JZ:           strcpy(tac_string, "TAC_IFZ"); break;
    case TAC_JMP:          strcpy(tac_string, "TAC_JUMP"); break;
    case TAC_ASSIGN:       strcpy(tac_string, "TAC_ASSIGN"); break;
    case TAC_ARRAY_ASSIGN: strcpy(tac_string, "TAC_ARRAY_ASSIGN"); break;
    case TAC_ARRAY_INDEX:  strcpy(tac_string, "TAC_ARRAY_INDEX"); break;
    case TAC_BEGIN_FUNC:   strcpy(tac_string, "TAC_BEGIN_FUNC"); break;
    case TAC_END_FUNC:     strcpy(tac_string, "TAC_END_FUNC"); break;
    case TAC_CALL:         strcpy(tac_string, "TAC_CALL"); break;
    case TAC_PUSH_ARG:     strcpy(tac_string, "TAC_PUSH_ARG"); break;
    case TAC_POP_ARG:      strcpy(tac_string, "TAC_POP_ARG"); break;
    default:               return;
    }

    fprintf(stdout, "TAC(%s, %s, %s, %s)\n",
            tac_string,
            tac->res? tac->res->string : "NULL",
            tac->op1? tac->op1->string : "NULL",
            tac->op2? tac->op2->string : "NULL");
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
    case AST_DIV: type = TAC_DIV; break;
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
    
    TAC *temp_tac = TAC_create(TAC_TEMP, makeTemp(), NULL, NULL);
    TAC *tac = TAC_create(type, temp_tac->res,
                          op1? op1->res : NULL,
                          op2? op2->res : NULL);

    return TAC_join(TAC_join(TAC_join(temp_tac, op1), op2), tac);
}

// Cria um TAC para instrução "read"
TAC *TAC_make_read(TAC *expression) {
    TAC *read_tac = TAC_create(TAC_READ, expression->res, NULL, NULL);
    return TAC_join(expression, read_tac);
}

// Cria um TAC para instrução "print"
TAC *TAC_make_print(TAC *expression) {
    TAC *print_tac = TAC_create(TAC_PRINT, expression->res, NULL, NULL);
    return TAC_join(expression, print_tac);
}

// Cria um TAC para instrução "return"
TAC *TAC_make_return(TAC *expression) {
    TAC *return_tac = TAC_create(TAC_RET, expression->res, NULL, NULL);
    return TAC_join(expression, return_tac);
}

// if (condition) then (if_true);
TAC *TAC_make_if(TAC *condition, TAC *if_true) {
    HashNode *label = makeLabel();
    TAC *jump = TAC_create(TAC_JZ, label, condition == NULL ? NULL : condition->res, NULL);
    TAC *label_tac = TAC_create(TAC_LABEL, label, NULL, NULL);
    return TAC_join(TAC_join(TAC_join(condition, jump), if_true), label_tac);
}

// if (condition) then (if_true) else (if_false);
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

TAC *TAC_make_assign(TAC *identifier, TAC *expression) {
    TAC *assign_tac = TAC_create(TAC_ASSIGN, identifier->res, expression->res, NULL);
    return TAC_join(TAC_join(identifier, expression), assign_tac);
}

TAC *TAC_make_ary_assign(TAC *identifier, TAC *index, TAC *expression) {
    TAC *ary_assign_tac = TAC_create(TAC_ARRAY_ASSIGN, identifier->res,
                                     index->res, expression->res);
    return TAC_join(TAC_join(TAC_join(identifier, index), expression), ary_assign_tac);
}

TAC *TAC_make_ary_index(TAC *identifier, TAC *index) {
    TAC *temp_tac = TAC_create(TAC_TEMP, makeTemp(), NULL, NULL);
    TAC *ary_index_tac = TAC_create(TAC_ARRAY_INDEX, temp_tac->res,
                                    identifier->res, index->res);
    return TAC_join(TAC_join(TAC_join(temp_tac, identifier), index), ary_index_tac);
}

TAC *TAC_make_ary_decl_assign(TAC *identifier, TAC *index, TAC *expression) {
    int i, n = atoi(index->res->string);
    TAC *ary_decl_tac = NULL;
    TAC *ary_assign_tac = NULL;
    TAC *aux_expression = expression;

    for (i=0; i<n; i++) {
        if (!aux_expression) {
            fprintf(stderr, "ERRO SEMANTICO: Vetor %s na linha %d inicializado com número incompatível de índices.\n",
                    identifier->res->string, identifier->res->lineNumber);
            exit(4);
        }

        char index_string[10];
        sprintf(index_string, "%d", i);
        
        ary_assign_tac = TAC_create(TAC_ARRAY_ASSIGN, identifier->res,
                                    setHashNode(index_string, SYMBOL_LIT_INTEGER),
                                    aux_expression->res);
        
        ary_decl_tac = TAC_join(ary_decl_tac, ary_assign_tac);
        
        aux_expression = aux_expression->next;
    }
    
    return ary_decl_tac;
}

TAC *TAC_make_func_declaration(TAC *func_name, TAC *func_params, TAC *func_body) {
    TAC *begin_func_tac = TAC_create(TAC_BEGIN_FUNC, func_name->res, NULL, NULL);
    TAC *end_func_tac = TAC_create(TAC_END_FUNC, func_name->res, NULL, NULL);

    return TAC_join(TAC_join(TAC_join(begin_func_tac, func_params), func_body), end_func_tac);
}

TAC *TAC_make_func_call(TAC *func_name, TAC *args) {
    HashNode *label_node = makeLabel();
    
    TAC *temp_tac = TAC_create(TAC_TEMP, makeTemp(), NULL, NULL);
    TAC *func_call = TAC_create(TAC_CALL, temp_tac->res, func_name->res, label_node);
    TAC *label = TAC_create(TAC_LABEL, label_node, NULL, NULL);
    TAC *pop_args = TAC_make_pop_args(args);
    
    TAC *func_call_join = TAC_join(TAC_join(TAC_join(args, func_call), label), pop_args);
    return TAC_join(temp_tac, func_call_join);
}

TAC *TAC_make_push_arg(TAC *arg) {
    return TAC_create(TAC_PUSH_ARG, arg->res, NULL, NULL);
}

TAC *TAC_make_pop_args(TAC *args) {
    TAC *aux = args;
    TAC *pop_args = NULL;
    
    while (aux && aux->type == TAC_PUSH_ARG) {
        pop_args = TAC_join(pop_args, TAC_create(TAC_POP_ARG, NULL, NULL, NULL));
        aux = aux->next;
    }
    
    return pop_args;
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

    case AST_READ:
        return TAC_make_read(codes[0]);

    case AST_PRINT:
        return codes[0];

    case AST_PRINT_ARGS:
        if (codes[1] == NULL)
            return TAC_make_print(codes[0]);
//        else if (codes[1]->type == TAC_SYMBOL)
//            return TAC_join(TAC_make_print(codes[0]),
//                            TAC_make_print(codes[1]));
        else
            return TAC_join(TAC_make_print(codes[0]), codes[1]);

    case AST_RETURN:
        return TAC_make_return(codes[0]);

    case AST_IF:
        return TAC_make_if(codes[0], codes[1]);

    case AST_IF_ELSE:
        return TAC_make_if_else(codes[0], codes[1], codes[2]);

    case AST_WHILE:
        return TAC_make_while(codes[0], codes[1]);

    case AST_VAR_ASSIGN:
        return TAC_make_assign(codes[0], codes[1]);

    case AST_ARY_ASSIGN:
        return TAC_make_ary_assign(codes[0], codes[1], codes[2]);

    case AST_ARY_INDEX:
        return TAC_make_ary_index(codes[0], codes[1]);

    case AST_VAR_DECL:
        return TAC_make_assign(codes[0], codes[2]);

    case AST_ARY_DECL:
        return TAC_make_ary_decl_assign(codes[0], codes[2], codes[3]);

    case AST_LIT_LIST:
        return TAC_join(codes[0], codes[1]);

    case AST_EMPTY_LIT_LIST:
        return NULL;

    case AST_FUNC_DECL:
        return TAC_make_func_declaration(codes[1], codes[2], codes[3]);

    case AST_PARAM_LIST:
        return TAC_join(codes[0], codes[1]);

    case AST_PARAM:
        return codes[0];

    case AST_FUNC_CALL:
        return TAC_make_func_call(codes[0], codes[1]);

    case AST_ARG_LIST:
        if (codes[1]->type == TAC_SYMBOL)
            return TAC_join(TAC_make_push_arg(codes[0]),
                            TAC_make_push_arg(codes[1]));
        else
            return TAC_join(TAC_make_push_arg(codes[0]), codes[1]);

    default:
        return TAC_join(TAC_join(TAC_join(codes[0], codes[1]), codes[2]), codes[3]);
    }
}
