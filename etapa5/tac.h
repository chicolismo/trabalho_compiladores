#ifndef __TAC_H__
#define __TAC_H__

#include "hash.h"

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
#define TAC_IFZ 23
#define TAC_JUMP 24
#define TAC_CALL 25
#define TAC_ARG 26

#define TAC_PARAM_PUSH 27
#define TAC_PARAM_POP 28

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

#endif // __TAC_H__
