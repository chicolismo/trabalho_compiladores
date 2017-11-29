#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "semantic.h"

AST *program;

void semanticVerification(AST *node) {
    program = node;
    setTypes(node);
    checkUndeclaredIdentifiers(node);
    checkIdentifiersUsage(node);
}

void setTypes(AST *node) {
    if (!node) {
        return;
    }

    else if (node->type == AST_VAR_DECL) {
        setTypesOfNode(node, SYMBOL_IDENTIFIER_SCALAR, 0, 1);
    }

    else if (node->type == AST_ARY_DECL) {
        setTypesOfNode(node, SYMBOL_IDENTIFIER_VECTOR, 0, 1);
    }

    else if (node->type == AST_FUNC_DECL) {
        setTypesOfNode(node, SYMBOL_IDENTIFIER_FUNCTION, 1, 0);
        setTypes(node->son[2]); // Define tipos para os parametros da funcao
    }

    else if (node->type == AST_PARAM) {
        setTypesOfNode(node, SYMBOL_IDENTIFIER_SCALAR, 0, 1);
    }

    int i;
    // Aplica recursao apenas para declaracoes
    if (node->type == AST_DECL_LIST || node->type == AST_PARAM_LIST) {
        for (i = 0; i < MAX_SONS; i++) {
            setTypes(node->son[i]);
        }
    }
}

void setTypesOfNode(AST *node, int type, int identifierIndex, int dataTypeIndex) {
    // Nodo ja teve seu tipo redefinido antes, entao ja foi declarado anteriormente
    if (node->son[identifierIndex]->symbol->type != SYMBOL_IDENTIFIER) {
        fprintf(stderr, "ERRO SEMANTICO: Redeclaracao de \"%s\" na linha %d, previamente declarado na linha %d.\n",
                node->son[identifierIndex]->symbol->string, node->lineNumber,
                node->son[identifierIndex]->symbol->lineNumber);
        exit(4);
    } else {
        node->son[identifierIndex]->symbol->type = type;
        node->son[identifierIndex]->symbol->lineNumber = node->lineNumber;

        if (node->son[dataTypeIndex]->type == AST_TYPE_BYTE) {
            node->son[identifierIndex]->symbol->dataType = DATATYPE_BYTE;
        }

        else if (node->son[dataTypeIndex]->type == AST_TYPE_SHORT) {
            node->son[identifierIndex]->symbol->dataType = DATATYPE_SHORT;
        }

        else if (node->son[dataTypeIndex]->type == AST_TYPE_LONG) {
            node->son[identifierIndex]->symbol->dataType = DATATYPE_LONG;
        }

        else if (node->son[dataTypeIndex]->type == AST_TYPE_FLOAT) {
            node->son[identifierIndex]->symbol->dataType = DATATYPE_FLOAT;
        }

        else if (node->son[dataTypeIndex]->type == AST_TYPE_DOUBLE) {
            node->son[identifierIndex]->symbol->dataType = DATATYPE_DOUBLE;
        }
    }
}

void checkUndeclaredIdentifiers(AST *node) {
    if (!node) {
        return;
    }

    // Se tipo do identificador nao foi redefinido ainda, ele nao foi declarado
    if (node->symbol && node->symbol->type == SYMBOL_IDENTIFIER) {
        fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d nao declarado.\n",
                node->symbol->string, node->lineNumber);
        exit(4);
    }

    int i;
    for (i = 0; i < MAX_SONS; i++) {
        checkUndeclaredIdentifiers(node->son[i]);
    }
}

void checkIdentifiersUsage(AST *node) {
    if (!node) {
        return;
    }

    // Verifica se indices de vetores sao de tipos inteiros
    if (node->type == AST_ARY_INDEX || node->type == AST_ARY_ASSIGN) {
        int dataType = getExpressionDataType(node->son[1]);
        if (dataType != DATATYPE_BYTE && dataType != DATATYPE_SHORT && dataType != DATATYPE_LONG) {
            fprintf(stderr, "ERRO SEMANTICO: Indice do vetor \"%s\" na linha %d deveria ser um inteiro.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    // Verifica tipo de retorno da funcao
    if (node->type == AST_FUNC_DECL) {
        int returnCheck = checkFunctionReturnType(node->son[3], node->son[1]->symbol->dataType);
        if (returnCheck == 0) {
            fprintf(stderr, "ERRO SEMANTICO: Funcao \"%s\" declarada na linha %d nao possui retorno.\n",
                    node->son[1]->symbol->string, node->lineNumber);
            exit(4);
        }
        else if (returnCheck < 0) {
            fprintf(stderr, "ERRO SEMANTICO: Funcao \"%s\" declarada na linha %d possui retorno com tipo incompativel.\n",
                    node->son[1]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    // Verifica atribuicao a escalares
    else if (node->type == AST_VAR_ASSIGN) {
        if (node->son[0]->symbol->type != SYMBOL_IDENTIFIER_SCALAR) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um escalar.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }

        if (convertDataTypesByClasses(node->son[0]->symbol->dataType,
                                      getExpressionDataType(node->son[1])) == DATATYPE_ERROR) {
            fprintf(stderr, "ERRO SEMANTICO: Incompatibilidade de tipos na atribuicao ao escalar \"%s\" na linha %d.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    // Verifica atribuicao a vetores
    else if (node->type == AST_ARY_ASSIGN) {
        if (node->son[0]->symbol->type != SYMBOL_IDENTIFIER_VECTOR) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser um vetor.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }

        if (convertDataTypesByClasses(node->son[0]->symbol->dataType,
                                      getExpressionDataType(node->son[2])) == DATATYPE_ERROR) {
            fprintf(stderr, "ERRO SEMANTICO: Incompatibilidade de tipos na atribuicao ao indice do vetor \"%s\" na linha %d.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }
    }

    // Verifica chamada de funcao
    else if (node->type == AST_FUNC_CALL) {
        if (node->son[0]->symbol->type != SYMBOL_IDENTIFIER_FUNCTION) {
            fprintf(stderr, "ERRO SEMANTICO: Identificador \"%s\" na linha %d deveria ser uma chamada de funcao.\n",
                    node->son[0]->symbol->string, node->lineNumber);
            exit(4);
        }

        checkFunctionCall(node, program);
    }

    // Verifica testes do if e while
    else if (node->type == AST_IF || node->type == AST_IF_ELSE || node->type == AST_WHILE) {
        if (getExpressionDataType(node->son[0]) != DATATYPE_BOOL) {
            fprintf(stderr, "ERRO SEMANTICO: Teste condicional na linha %d nao retorna uma expressao booleana.\n",
                    node->son[0]->lineNumber);
            exit(4);
        }
    }

    int i;
    for (i = 0; i < MAX_SONS; i++) {
        checkIdentifiersUsage(node->son[i]);
    }
}

// Retorna um valor positivo se encontrar apenas retornos com tipo compativel
// Retorna 0 se nao houver nenhum retorno na funcao
// Retorna um valor negativo se encontrar retornos com tipo incompativel
int checkFunctionReturnType(AST *node, int dataType) {
    if (!node) {
        return 0;
    }

    if (node->type == AST_RETURN) {
        if (convertDataTypesByClasses(dataType, getExpressionDataType(node->son[0])) != DATATYPE_ERROR) {
            return 1;
        } else {
            return -1000;
        }
    }

    int i, returnsSum = 0;
    for (i = 0; i < MAX_SONS; i++) {
        returnsSum += checkFunctionReturnType(node->son[i], dataType);
    }
    return returnsSum;
}

void checkFunctionCall(AST *functionCall, AST *node) {
    if (!node) {
        return;
    }

    else if (node->type == AST_FUNC_DECL &&
             strcmp(functionCall->son[0]->symbol->string, node->son[1]->symbol->string) == 0) {
        compareArgsAndParams(functionCall, functionCall->son[1], node->son[2]);
        return;
    }

    int i;
    for (i = 0; i < MAX_SONS; i++) {
        checkFunctionCall(functionCall, node->son[i]);
    }
}

void compareArgsAndParams(AST *functionCall, AST *args, AST *params) {
    if (!args && !params) {
        return;
    }

    if (!args || !params) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d com um numero incompativel de argumentos.\n",
                functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }

    if (args->type != AST_ARG_LIST && params->type != AST_PARAM_LIST) {
        // Compara ultimos elementos das listas
        compareArgAndParam(functionCall, args, params);
        return;
    }

    if (args->type != AST_ARG_LIST || params->type != AST_PARAM_LIST) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d com um numero incompativel de argumentos.\n",
                functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }

    // Compara argumento com parametro atuais
    compareArgAndParam(functionCall, args->son[0], params->son[0]);

    // Aplica recursao para demais argumentos e parametros
    compareArgsAndParams(functionCall, args->son[1], params->son[1]);
}

void compareArgAndParam(AST *functionCall, AST *arg, AST *param) {
    int argDataType = getExpressionDataType(arg);
    int paramDataType = getExpressionDataType(param->son[0]);
    int dataType = convertDataTypesByClasses(argDataType, paramDataType);

    if (dataType == DATATYPE_ERROR) {
        fprintf(stderr, "ERRO SEMANTICO: Chamada da funcao \"%s\" na linha %d possui argumentos com tipos incompativeis com a sua declaracao.\n",
                functionCall->son[0]->symbol->string, functionCall->lineNumber);
        exit(4);
    }
}

int getExpressionDataType(AST *node) {
    int dataType;

    if (!node) {
        return DATATYPE_ERROR;
    }

    switch (node->type) {
    case AST_SYMBOL:
    case AST_LIT_INTEGER:
    case AST_LIT_REAL:
    case AST_LIT_CHAR:
        if (node->symbol->type == SYMBOL_LIT_INTEGER) {
            return DATATYPE_LONG;
        } else if (node->symbol->type == SYMBOL_LIT_REAL) {
            return DATATYPE_DOUBLE;
        } else if (node->symbol->type == SYMBOL_LIT_CHAR) {
            return DATATYPE_BYTE;
        } else {
            return node->symbol->dataType;
        }

    case AST_ARY_INDEX:
    case AST_FUNC_CALL:
        return node->son[0]->symbol->dataType;

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
        if (dataType != DATATYPE_ERROR && dataType != DATATYPE_BOOL) {
            return DATATYPE_BOOL;
        } else {
            return DATATYPE_ERROR;
        }

    case AST_NOT:
        if (getExpressionDataType(node->son[0]) == DATATYPE_BOOL) {
            return DATATYPE_BOOL;
        } else {
            return DATATYPE_ERROR;
        }

    case AST_AND:
    case AST_OR:
        if (getExpressionDataType(node->son[0]) == DATATYPE_BOOL &&
                getExpressionDataType(node->son[1]) == DATATYPE_BOOL) {
            return DATATYPE_BOOL;
        } else {
            return DATATYPE_ERROR;
        }

    default:
        return DATATYPE_ERROR;
    }
}

int convertDataTypes(int type1, int type2) {
    // Se os tipos forem equivalentes
    if (type1 == type2) {
        return type1;
    }

    // Se os tipos forem compativeis, retorna o maior deles
    if (type1 >= DATATYPE_BYTE && type1 <= DATATYPE_DOUBLE &&
            type2 >= DATATYPE_BYTE && type2 <= DATATYPE_DOUBLE) {
        if (type1 > type2) {
            return type1;
        } else {
            return type2;
        }
    }

    // Se os dois tipos forem booleanos
    if (type1 == DATATYPE_BOOL && type2 == DATATYPE_BOOL) {
        return DATATYPE_BOOL;
    }

    // Tipos nao compativeis
    return DATATYPE_ERROR;
}

int convertDataTypesByClasses(int type1, int type2) {
    // Se os tipos forem equivalentes
    if (type1 == type2) {
        return type1;
    }
    
    // Se os tipos forem inteiros, retorna o maior deles
    if (type1 >= DATATYPE_BYTE && type1 <= DATATYPE_LONG &&
        type2 >= DATATYPE_BYTE && type2 <= DATATYPE_LONG) {
        if (type1 > type2) {
            return type1;
        } else {
            return type2;
        }
    }
    
    // Se os tipos forem reais, retorna o maior deles
    if (type1 >= DATATYPE_FLOAT && type1 <= DATATYPE_DOUBLE &&
        type2 >= DATATYPE_FLOAT && type2 <= DATATYPE_DOUBLE) {
        if (type1 > type2) {
            return type1;
        } else {
            return type2;
        }
    }
    
    // Se os dois tipos forem booleanos
    if (type1 == DATATYPE_BOOL && type2 == DATATYPE_BOOL) {
        return DATATYPE_BOOL;
    }
    
    // Tipos nao compativeis
    return DATATYPE_ERROR;
}
