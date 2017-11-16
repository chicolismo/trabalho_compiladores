
#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "astree.h"

void semanticVerification(AST *node);
void semanticSetTypes(AST *node);
void setTypesOfNode(AST *node, int type, int identifierIndex, int datatypeIndex);
void semanticCheckUndeclared(AST *node);
void semanticCheckUsage(AST *node);
void checkFunctionCall(AST *functionCall, AST *node);
void compareArgsAndParams(AST *functionCall, AST *args, AST *params);
int getExpressionDataType(AST *node);
int convertDataTypes(int type1, int type2);

#endif // __SEMANTIC_H__
