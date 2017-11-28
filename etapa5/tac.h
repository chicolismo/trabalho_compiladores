#ifndef __TAC_H__
#define __TAC_H__

#define LABEL_SIZE 15

#include "hash.h"
#include "astree.h"

// TODO: Temos que descobrir quais símbolos são necessários

#define TAC_SYMBOL 1
#define TAC_LABEL 2
#define TAC_MOVE 3

#define TAC_ADD 4
#define TAC_SUB 5
#define TAC_MUL 6
#define TAC_DIV 7

#define TAC_LT 8
#define TAC_GT 9
#define TAC_LE 10
#define TAC_GE 11

#define TAC_EQ 12
#define TAC_NE 13

#define TAC_AND 14
#define TAC_OR 15
#define TAC_NOT 16

#define TAC_READ 17
#define TAC_RET 18
#define TAC_INC 19 // ?
#define TAC_PRINT 20

#define TAC_BEGINFUN 21
#define TAC_ENDFUN 22
#define TAC_IFZ 23 // jump if zero
#define TAC_IFN 24 // jump if negative
#define TAC_JUMP 25
#define TAC_CALL 26
#define TAC_ARG 27

#define TAC_PARAM_PUSH 28
#define TAC_PARAM_POP 29

typedef struct TAC {
    int type;

    HashNode *res;
    HashNode *op1;
    HashNode *op2;

    struct TAC *prev;
    struct TAC *next;
} TAC;

// Criar
TAC *TAC_create(int type, HashNode *res, HashNode *op1, HashNode *op2);

// Imprimir
void TAC_print(TAC *tac);

// Unir
TAC *TAC_join(TAC *tac1, TAC *tac2);


// Funções auxiliares
TAC *TAC_get_first(TAC *tac);
TAC *TAC_get_last(TAC *tac);
TAC *TAC_reverse_list(TAC *tac);

void TAC_print_forward(TAC *tac);

void TAC_print_backward(TAC *tac);

HashNode *makeLabel();
HashNode *makeTemp();

TAC *generate_code(AST *node);
TAC *make_while(TAC *code1, TAC *code2);
TAC *make_if_then(TAC *code1, TAC *code2);
TAC *make_if_then_else(TAC *code1, TAC *code2, TAC *code3);
TAC *make_binary_operator(int type, TAC *code1, TAC *code2);
#endif // __TAC_H__
