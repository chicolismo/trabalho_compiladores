#ifndef __TAC_H__
#define __TAC_H__

#include "hash.h"
#include "astree.h"

// TODO: Temos que descobrir quais símbolos são necessários

#define TAC_SYMBOL 1
#define TAC_LABEL 2

#define TAC_MOVE 3 // res = op1

#define TAC_ADD 4 // res = op1 + op2
#define TAC_SUB 5 // res = op1 - op2
#define TAC_MUL 6 // res = op1 * op2
#define TAC_DIV 7 // res = op1 / op2

#define TAC_LT 8 // res = op1 < op2
#define TAC_GT 9 // res = op1 > op2
#define TAC_LE 10 // res = op1 <= op2
#define TAC_GE 11 // res = op1 >= op2

#define TAC_EQ 12 // res = op1 == op2
#define TAC_NE 13 // res = op1 != op2

#define TAC_AND 14 // res = op1 && op2
#define TAC_OR 15 // res = op1 || op2

#define TAC_NOT 16 // res = !op1

#define TAC_READ 17
#define TAC_PRINT 18

#define TAC_RET 19 // op1 é o valor a ser retornado

#define TAC_BEGINFUN 20
#define TAC_ENDFUN 21

#define TAC_JZ 22 // jump if zero
#define TAC_JMP 23

#define TAC_CALL 24 // op1 = fn, res = res

#define TAC_PARAM 25
#define TAC_VAR_DECL 26
#define TAC_ARY_DECL 27
#define TAC_ASSIGN 28
#define TAC_EMPTY_LIST 29
#define TAC_ARRAY_ASSIGN 30
#define TAC_ARRAY_INDEX 31


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
TAC *TAC_make_print(TAC *arg);
TAC *TAC_make_read(TAC *expression);
TAC *TAC_make_while(TAC *condition, TAC *body);
TAC *TAC_make_if(TAC *condition, TAC *if_true);
TAC *TAC_make_if_else(TAC *condition, TAC *if_true, TAC *if_false);
TAC *TAC_make_return(TAC *expression);
TAC *TAC_make_fun_declaration(AST *node, TAC *fn_name, TAC *fn_params, TAC *fn_body);
TAC *TAC_make_fun_call(AST *node, TAC *fn_name, TAC *fn_args);
TAC *TAC_make_param(AST *node);
TAC *TAC_make_var_declaration(AST *node, TAC *symbol, TAC *literal);
TAC *TAC_make_ary_declaration(AST *node, TAC *symbol, TAC *size, TAC *literals);
TAC *TAC_make_assign(AST *node, TAC *symbol, TAC *expr);
TAC *TAC_make_ary_assign(AST *node, TAC *symbol, TAC *index_expr, TAC *val_expr);
TAC *TAC_make_ary_index(AST *node, TAC *symbol, TAC *index_expr);
TAC *TAC_generate_code(AST *node);

#endif // __TAC_H__
