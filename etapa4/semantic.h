
#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include "astree.h"

void semanticVerification(AST *node);
void setTypes(AST *node);
void setTypesOfNode(AST *node, int type, int identifierIndex, int dataTypeIndex);
void checkUndeclaredIdentifiers(AST *node);
void checkIdentifiersUsage(AST *node);
int checkFunctionReturnType(AST *node, int dataType);
void checkFunctionCall(AST *functionCall, AST *node);
void compareArgsAndParams(AST *functionCall, AST *args, AST *params);
int getExpressionDataType(AST *node);
int convertDataTypes(int type1, int type2);

#endif // __SEMANTIC_H__
