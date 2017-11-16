#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "semantic.h"

AST* program;

void semanticVerification(AST *node) {
    program = node;
    semanticSetTypes(node);
    semanticCheckUndeclared(node);
    semanticCheckUsage(node);
    semanticCheckOperands(node);
}

void semanticSetTypes(AST *node) {
    if(!node)
        return;
    
    else if(node->type == AST_VAR_DECL) {
        // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
            exit(4);
        } else {
            node->son[0]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;
            node->son[0]->symbol->lineNumber = node->lineNumber;
            
            if(node->son[1]->type == AST_TYPE_BYTE)
                node->son[0]->symbol->datatype = DATATYPE_BYTE;
            
            else if(node->son[1]->type == AST_TYPE_SHORT)
                node->son[0]->symbol->datatype = DATATYPE_SHORT;
            
            else if(node->son[1]->type == AST_TYPE_LONG)
                node->son[0]->symbol->datatype = DATATYPE_LONG;
            
            else if(node->son[1]->type == AST_TYPE_FLOAT)
                node->son[0]->symbol->datatype = DATATYPE_FLOAT;
            
            else if(node->son[1]->type == AST_TYPE_DOUBLE)
                node->son[0]->symbol->datatype = DATATYPE_DOUBLE;
        }
    }
    
    else if(node->type == AST_ARY_DECL) {
        // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
            exit(4);
        } else {
            node->son[0]->symbol->type = SYMBOL_IDENTIFIER_VECTOR;
            node->son[0]->symbol->lineNumber = node->lineNumber;
            
            if(node->son[1]->type == AST_TYPE_BYTE)
                node->son[0]->symbol->datatype = DATATYPE_BYTE;
            
            else if(node->son[1]->type == AST_TYPE_SHORT)
                node->son[0]->symbol->datatype = DATATYPE_SHORT;
            
            else if(node->son[1]->type == AST_TYPE_LONG)
                node->son[0]->symbol->datatype = DATATYPE_LONG;
            
            else if(node->son[1]->type == AST_TYPE_FLOAT)
                node->son[0]->symbol->datatype = DATATYPE_FLOAT;
            
            else if(node->son[1]->type == AST_TYPE_DOUBLE)
                node->son[0]->symbol->datatype = DATATYPE_DOUBLE;
        }
    }
    
    else if(node->type == AST_FUNC_HEADER) {
        // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
        if(node->son[1]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n", node->son[1]->symbol->string, node->lineNumber, node->son[1]->symbol->lineNumber);
            exit(4);
        } else {
            node->son[1]->symbol->type = SYMBOL_IDENTIFIER_FUNCTION;
            node->son[1]->symbol->lineNumber = node->lineNumber;
            
            if(node->son[0]->type == AST_TYPE_BYTE)
                node->son[1]->symbol->datatype = DATATYPE_BYTE;
            
            else if(node->son[0]->type == AST_TYPE_SHORT)
                node->son[1]->symbol->datatype = DATATYPE_SHORT;
            
            else if(node->son[0]->type == AST_TYPE_LONG)
                node->son[1]->symbol->datatype = DATATYPE_LONG;
            
            else if(node->son[0]->type == AST_TYPE_FLOAT)
                node->son[1]->symbol->datatype = DATATYPE_FLOAT;
            
            else if(node->son[0]->type == AST_TYPE_DOUBLE)
                node->son[1]->symbol->datatype = DATATYPE_DOUBLE;
        }
    }
    
    else if(node->type == AST_PARAM) {
        // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER) {
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
            exit(4);
        } else {
            node->son[0]->symbol->type = SYMBOL_IDENTIFIER_SCALAR;
            node->son[0]->symbol->lineNumber = node->lineNumber;
            
            if(node->son[1]->type == AST_TYPE_BYTE)
                node->son[0]->symbol->datatype = DATATYPE_BYTE;
            
            else if(node->son[1]->type == AST_TYPE_SHORT)
                node->son[0]->symbol->datatype = DATATYPE_SHORT;
            
            else if(node->son[1]->type == AST_TYPE_LONG)
                node->son[0]->symbol->datatype = DATATYPE_LONG;
            
            else if(node->son[1]->type == AST_TYPE_FLOAT)
                node->son[0]->symbol->datatype = DATATYPE_FLOAT;
            
            else if(node->son[1]->type == AST_TYPE_DOUBLE)
                node->son[0]->symbol->datatype = DATATYPE_DOUBLE;
        }
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticSetTypes(node->son[i]);
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
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um escalar.\n", node->symbol->text, node->lineNumber);
            exit(4);
        }
    }

    else if(node->type == AST_ARY_ASSIGN) {
        if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um vetor.\n", node->symbol->text, node->lineNumber);
            exit(4);
        }
    }

    else if(node->type == AST_FUNC_CALL) {
        if(node->symbol->type != SYMBOL_IDENTIFIER_FUNCTION) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser uma chamada de funcao.\n", node->symbol->text, node->lineNumber);
            exit(4);
        }
        
        checkFunctionCall(node, program));
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticCheckUsage(node->son[i]);
}

void semanticCheckOperands(AST *node) {
//    int i;
//
//    if(!node)
//        return;
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
    
    compareArgsAndParams(functionCall, args->son[1], params->son[1]);
}

int convertDataTypes(int type1, int type2) {
    // Se os tipos forem equivalentes
    if type1 == type2
        return 0;
    
    // Se os tipos forem compativeis, retorna o maior deles
    if(type1 >= DATATYPE_BYTE && type1 <= DATATYPE_DOUBLE && type2 >= DATATYPE_BYTE && type2 <= DATATYPE_DOUBLE) {
        if type1 > type2
            return type1;
        else
            return type2;
    }
    
    // Tipos nao compativeis
    return -1;
}
