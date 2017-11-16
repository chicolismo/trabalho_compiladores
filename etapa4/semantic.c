#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "semantic.h"

void semanticVerification(AST *node) {
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
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarada na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
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
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarada na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
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
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarada na linha %d.\n", node->son[1]->symbol->string, node->lineNumber, node->son[1]->symbol->lineNumber);
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
            fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarada na linha %d.\n", node->son[0]->symbol->string, node->lineNumber, node->son[0]->symbol->lineNumber);
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
        fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d nao declarado.\n", node->symbol->string, node->symbol->lineNumber);
        exit(4);
    }
    
    int i;
    for(i=0; i<MAX_SONS; i++)
        semanticCheckUndeclared(node->son[i]);
}

void semanticCheckUsage(AST *node) {
    if(!node)
        return;
    
//    else if(node->type == AST_VAR_ASSIGN) {
//        if(node->symbol->type != SYMBOL_VAR) {
//            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um escalar.\n", node->symbol->text, node->symbol->lineNumber);
//            exit(4);
//        }
//    }
//
//    else if(node->type == AST_ARY_ASSIGN) {
//        if(node->symbol->type != SYMBOL_VAR) {
//            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um vetor.\n", node->symbol->text, node->symbol->lineNumber);
//            exit(4);
//        }
//    }
//
//    else if(node->type == AST_ARY_INDEX) {
//        if(node->symbol->type != SYMBOL_VAR) {
//            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser uma chamada de funcao.\n", node->symbol->text, node->symbol->lineNumber);
//            exit(4);
//        }
//    }
//
//    else if(node->type == AST_FUNC_CALL) {
//        if(node->symbol->type != SYMBOL_VAR) {
//            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser uma chamada de funcao.\n", node->symbol->text, node->symbol->lineNumber);
//            exit(4);
//        }
//    }
    
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
