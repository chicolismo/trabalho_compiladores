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

#define TAC_BEGINFUN 21
#define TAC_ENDFUN 22

#define TAC_JZ 23 // jump if zero
//#define TAC_JN 24 // jump if negative
#define TAC_JMP 25

#define TAC_CALL 26 // op1 = fn, res = res

#define TAC_ARG 27

//#define TAC_TYPE 29 // Talvez desse para tratar tipos como símbolos...
#define TAC_PARAM 30
#define TAC_LITERAL 31
#define TAC_VAR_DECL 32
#define TAC_ARY_DECL 33
#define TAC_ASSIGN 34
#define TAC_EMPTY_LIST 35


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

TAC *TAC_make_binary_operator(AST *node, TAC *tac1, TAC *tac2);

TAC *TAC_make_read(AST *node, TAC *tac);
TAC *TAC_make_print(AST *node, TAC *args);

TAC *TAC_make_while(AST *node, TAC *cond, TAC *body);

TAC *TAC_make_arg(AST *node, TAC *tac);

TAC *TAC_generate_code(AST *node);
#endif // __TAC_H__
