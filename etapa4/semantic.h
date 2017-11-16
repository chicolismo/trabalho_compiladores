
#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "astree.h"

void semanticVerification(AST *node);
void semanticSetTypes(AST *node);
void semanticCheckUndeclared(AST *node);
void semanticCheckUsage(AST *node);
void semanticCheckOperands(AST *node);

#endif // __SEMANTIC_H__
