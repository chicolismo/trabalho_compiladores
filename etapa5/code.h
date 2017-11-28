#ifndef __CODE_H__
#define __CODE_H__

#include "tac.h"
#include "astree.h"

TAC *generate_code(AST *node);
TAC *make_while(TAC *code1, TAC *code2);
TAC *make_if_then(TAC *code1, TAC *code2);
TAC *make_if_then_else(TAC *code1, TAC *code2, TAC *code3);
TAC *make_binary_operator(int type, TAC *code1, TAC *code2);

#endif // __CODE_H__

