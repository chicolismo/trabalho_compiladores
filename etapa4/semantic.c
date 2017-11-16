#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "semantic.h"

AST* program;

void semanticVerification(AST *node) {
    program = node;
    semanticSetTypes(node);
    semanticCheckUndeclared(node);
    semanticCheckUsage(node);
}

void semanticSetTypes(AST *node) {
    if(!node)
        return;
    
    else if(node->type == AST_VAR_DECL)
        setTypesOfNode(node, SYMBOL_IDENTIFIER_SCALAR, 0, 1);
        
    else if(node->type == AST_ARY_DECL)
        setTypesOfNode(node, SYMBOL_IDENTIFIER_VECTOR, 0, 1);
        
    else if(node->type == AST_FUNC_HEADER)
        setTypesOfNode(node, SYMBOL_IDENTIFIER_FUNCTION, 1, 0);
        
    else if(node->type == AST_PARAM)
        setTypesOfNode(node, SYMBOL_IDENTIFIER_SCALAR, 0, 1);
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticSetTypes(node->son[i]);
}

void setTypesOfNode(AST *node, int type, int identifierIndex, int datatypeIndex) {
    // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
    if(node->son[identifierIndex]->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n", node->son[identifierIndex]->symbol->string, node->lineNumber, node->son[identifierIndex]->symbol->lineNumber);
        exit(4);
    } else {
        node->son[identifierIndex]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;
        node->son[identifierIndex]->symbol->lineNumber = node->lineNumber;
        
        if(node->son[datatypeIndex]->type == AST_TYPE_BYTE)
            node->son[identifierIndex]->symbol->datatype = DATATYPE_BYTE;
        
        else if(node->son[datatypeIndex]->type == AST_TYPE_SHORT)
            node->son[identifierIndex]->symbol->datatype = DATATYPE_SHORT;
        
        else if(node->son[datatypeIndex]->type == AST_TYPE_LONG)
            node->son[identifierIndex]->symbol->datatype = DATATYPE_LONG;
        
        else if(node->son[datatypeIndex]->type == AST_TYPE_FLOAT)
            node->son[identifierIndex]->symbol->datatype = DATATYPE_FLOAT;
        
        else if(node->son[datatypeIndex]->type == AST_TYPE_DOUBLE)
            node->son[identifierIndex]->symbol->datatype = DATATYPE_DOUBLE;
    }
}

void semanticCheckUndeclared(AST *node) {
    if(!node)
        return;
    
    // Se tipo do identificador nao foi redefinido ainda, ele nao foi declarado
    if(node->symbol && node->symbol->type == SYMBOL_IDENTIFIER) {
        fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d nao declarado.\n", node->symbol->string, node->lineNumber);
        exit(4);
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticCheckUndeclared(node->son[i]);
}

void semanticCheckUsage(AST *node) {
    if(!node)
        return;
    
    else if(node->type == AST_VAR_ASSIGN) {
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER_SCALAR) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um escalar.\n", node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    else if(node->type == AST_ARY_ASSIGN) {
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um vetor.\n", node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    else if(node->type == AST_FUNC_CALL) {
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER_FUNCTION) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser uma chamada de funcao.\n", node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
        
        checkFunctionCall(node, program);
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticCheckUsage(node->son[i]);
}

void checkFunctionCall(AST *functionCall, AST *node) {
    if(!node)
        return;
    
    else if(node->type == AST_FUNC_HEADER &&
            strcmp(functionCall->son[0]->symbol->string, node->son[1]->symbol->string) == 0) {
        compareArgsAndParams(functionCall, functionCall->son[1], node->son[2]);
        return;
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        checkFunctionCall(functionCall, node->son[i]);
}

void compareArgsAndParams(AST *functionCall, AST *args, AST *params) {
    if(!args && !params)
        return;
    
    if(!args || !params) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d com um numero incompativel de argumentos.\n", functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }
    
    if(args->type != AST_LIST && params->type != AST_PARAM_LIST)
        return;
    
    if(args->type != AST_LIST || params->type != AST_PARAM_LIST) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d com um numero incompativel de argumentos.\n", functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }
    
    int argDataType = getExpressionDataType(args->son[0]);
    int paramDataType = getExpressionDataType(params->son[0]->son[0]);
    int dataType = convertDataTypes(argDataType, paramDataType);

    if(dataType == DATATYPE_ERROR) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d possui argumentos com tipos incompativeis com a sua declaracao.\n", functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }
    
    compareArgsAndParams(functionCall, args->son[1], params->son[1]);
}

int getExpressionDataType(AST *node) {
    int dataType;
    
    if(!node)
        return DATATYPE_ERROR;
    
    switch(node->type) {
        case AST_SYMBOL:
            return node->symbol->datatype;
            
        case AST_ARY_INDEX:
        case AST_FUNC_CALL:
            return node->son[0]->symbol->datatype;
            
        case AST_PARENS_EXPR:
            return getExpressionDataType(node->son[0]);
            
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
            return convertDataTypes(getExpressionDataType(node->son[0]),
                                    getExpressionDataType(node->son[1]));
            
        case AST_LT:
        case AST_GT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_NE:
            dataType = convertDataTypes(getExpressionDataType(node->son[0]),
                                        getExpressionDataType(node->son[1]));
            if(dataType != DATATYPE_ERROR && dataType != DATATYPE_BOOL)
                return DATATYPE_BOOL;
            else
                return DATATYPE_ERROR;
            
        case AST_NOT:
            if(getExpressionDataType(node->son[0]) == DATATYPE_BOOL)
                return DATATYPE_BOOL;
            else
                return DATATYPE_ERROR;
            
        case AST_AND:
        case AST_OR:
            if(getExpressionDataType(node->son[0]) == DATATYPE_BOOL &&
               getExpressionDataType(node->son[1]) == DATATYPE_BOOL)
                return DATATYPE_BOOL;
            else
                return DATATYPE_ERROR;
            
        default:
            return DATATYPE_ERROR;
    }
}

int convertDataTypes(int type1, int type2) {
    // Se os tipos forem equivalentes
    if(type1 == type2)
        return type1;
    
    // Se os tipos forem compativeis, retorna o maior deles
    if(type1 >= DATATYPE_BYTE && type1 <= DATATYPE_DOUBLE && type2 >= DATATYPE_BYTE && type2 <= DATATYPE_DOUBLE) {
        if(type1 > type2)
            return type1;
        else
            return type2;
    }
    
    // Se os dois tipos forem booleanos
    if(type1 == DATATYPE_BOOL && type2 == DATATYPE_BOOL)
        return DATATYPE_BOOL;
    
    // Tipos nao compativeis
    return DATATYPE_ERROR;
}
