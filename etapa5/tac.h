#ifndef __TAC_H__
#define __TAC_H__

#include "hash.h"
#include "astree.h"

#define TAC_STRING_SIZE 20

#define TAC_SYMBOL       1
#define TAC_LABEL        2
#define TAC_TEMP         3

#define TAC_ADD          4
#define TAC_SUB          5
#define TAC_MUL          6
#define TAC_DIV          7

#define TAC_LT           8
#define TAC_GT           9
#define TAC_LE           10
#define TAC_GE           11
#define TAC_EQ           12
#define TAC_NE           13

#define TAC_AND          14
#define TAC_OR           15
#define TAC_NOT          16

#define TAC_READ         17
#define TAC_PRINT        18
#define TAC_RET          19

#define TAC_JZ           20
#define TAC_JMP          21

#define TAC_ASSIGN       22
#define TAC_ARRAY_ASSIGN 23
#define TAC_ARRAY_INDEX  24

#define TAC_BEGINFUN     25
#define TAC_ENDFUN       26
#define TAC_EMPTY_LIST   27

#define TAC_CALL         28
#define TAC_PUSH_ARG     29
#define TAC_POP_ARG      30


// Define um Nodo TAC (Three address code)
typedef struct TAC {
    int type;

    HashNode *res; // Resultado
    HashNode *op1; // Operando 1
    HashNode *op2; // Operando 2

    struct TAC *prev; // Nodo TAC anterior
    struct TAC *next; // Nodo TAC seguinte
} TAC;


// Criar um TAC
TAC *TAC_create(int type, HashNode *res, HashNode *op1, HashNode *op2);

// Imprimir um TAC
void TAC_print(TAC *tac);

// Unir dois TACs
TAC *TAC_join(TAC *tac1, TAC *tac2);

// Funções auxiliares
TAC *TAC_get_first(TAC *tac);
TAC *TAC_get_last(TAC *tac);
TAC *TAC_reverse_list(TAC *tac);

void TAC_print_forward(TAC *tac);
void TAC_print_backward(TAC *tac);

TAC *TAC_make_binary_operator(AST *node, TAC *op1, TAC *op2);
TAC *TAC_make_read(TAC *expression);
TAC *TAC_make_print(TAC *expression);
TAC *TAC_make_return(TAC *expression);
TAC *TAC_make_if(TAC *condition, TAC *if_true);
TAC *TAC_make_if_else(TAC *condition, TAC *if_true, TAC *if_false);
TAC *TAC_make_while(TAC *condition, TAC *body);
TAC *TAC_make_assign(TAC *identifier, TAC *expression);
TAC *TAC_make_ary_assign(TAC *identifier, TAC *index, TAC *expression);
TAC *TAC_make_ary_index(TAC *identifier, TAC *index);
TAC *TAC_make_fun_declaration(AST *node, TAC *fn_name, TAC *fn_params, TAC *fn_body);
TAC *TAC_make_func_call(TAC *func_name, TAC *args);
TAC *TAC_make_push_arg(TAC *arg);
TAC *TAC_make_pop_args(TAC *args);
TAC *TAC_generate_code(AST *node);

#endif // __TAC_H__
