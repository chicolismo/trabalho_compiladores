#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

extern int isRunning();
extern void initMe();
extern int getLineNumber();

extern void printHashTable();
extern char *yytext;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

void infoSymbol() {
    if (yytext[0] == '\0') {
        return;
    }
    printf("%d: >>%c<<\n", getLineNumber(), yytext[0]);
}

void info(const char *type) {
    printf("%d: %s >>%s<<\n", getLineNumber(), type, yytext);
}

int main(int argc, char **argv) {
    initMe();
    
    if (argc < 1) {
    	fprintf(stderr, "É preciso fornecer um arquivo de teste\n");
	}

    FILE *testFile = fopen(argv[1], "r");
    if (testFile == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de teste\n");
        exit(1);
    }
    yyin = testFile;
    yyparse();
    printHashTable();

    return 0;
}
