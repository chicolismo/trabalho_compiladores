#include "tac.h"
#include <stdlib.h>
#include <stdio.h>

TAC *TAC_create(int type, HashNode *res, HashNode *op1, HashNode *op2) {
    TAC *tac = malloc(sizeof(TAC));
    tac->type = type;
    tac->res = res;
    tac->op1 = op1;
    tac->op2 = op2;
    return tac;
}

// TAC_join {{{
//
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
// }}}


// TAC_print {{{

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
    case TAC_INC:
        fprintf(stdout, "TAC_INC");
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
    case TAC_IFZ:
        fprintf(stdout, "TAC_IFZ");
        break;
    case TAC_JUMP:
        fprintf(stdout, "TAC_JUMP");
        break;
    case TAC_CALL:
        fprintf(stdout, "TAC_CALL");
        break;
    case TAC_ARG:
        fprintf(stdout, "TAC_ARG");
        break;
    case TAC_PARAM_PUSH:
        fprintf(stdout, "TAC_PARAM_PUSH");
        break;
    case TAC_PARAM_POP:
        fprintf(stdout, "TAC_PARAM_POP");
        break;
    default:
        fprintf(stderr, "!!TAC NÃO RECONHECIDO!!");
        break;
    }

    //
    // Imprime os membros do TAC, se houver
    //
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
// }}}
