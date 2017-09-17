#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "tokens.h"
#include "hash.h"

extern int isRunning();
extern void initMe();
extern int getLineNumber();

void infoSymbol() {
    if (yytext[0] == '\0') {
        return;
    }
    printf("%d: >>%c<<\n", getLineNumber(), yytext[0]);
}

void info(const char *type) {
    printf("%d: %s >>%s<<\n", getLineNumber(), type, yytext);
}

int main() {
    initMe();

    FILE *testFile = fopen("./test.txt", "r");
    if (testFile == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de teste\n");
        exit(1);
    }

    yyin = testFile;

    while (isRunning()) {
        switch (yylex()) {
            case KW_BYTE:
                info("keyword byte"); break;
            case KW_SHORT:
                info("keyword short"); break;
            case KW_LONG:
                info("keyword long"); break;
            case KW_FLOAT:
                info("keyword float"); break;
            case KW_DOUBLE:
                info("keyword double"); break;
            case KW_IF:
                info("keyword if"); break;
            case KW_THEN:
                info("keyword then"); break;
            case KW_ELSE:
                info("keyword else"); break;
            case KW_WHILE:
                info("keyword while"); break;
            case KW_FOR:
                info("keyword for"); break;
            case KW_READ:
                info("keyword read"); break;
            case KW_RETURN:
                info("keyword return"); break;
            case KW_PRINT:
                info("keyword print"); break;
            case OPERATOR_LE:
                info("operator le"); break;
            case OPERATOR_GE:
                info("operator ge"); break;
            case OPERATOR_EQ:
                info("operator eq"); break;
            case OPERATOR_NE:
                info("operator ne"); break;
            case OPERATOR_AND:
                info("operator and"); break;
            case OPERATOR_OR:
                info("operator or"); break;
            case TK_IDENTIFIER:
                info("identifier"); break;
            case LIT_INTEGER:
                info("int literal"); break;
            case LIT_REAL:
                info("real literal"); break;
            case LIT_CHAR:
                info("char literal"); break;
            case LIT_STRING:
                info("string literal"); break;
            case TOKEN_ERROR:
                info("token error"); break;
            default:
                infoSymbol(); break;
        }
    }

    printHashTable();

    return 0;
}
