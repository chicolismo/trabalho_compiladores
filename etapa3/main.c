#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
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
extern void set_output_file(FILE *fh);

int main(int argc, char **argv) {
    
    if (argc < 3) {
    	fprintf(stderr, "É preciso fornecer um arquivo de entrada e um arquivo de saída.\n");
        exit(1);
	}

    FILE *input_file = fopen(argv[1], "r");

    if (input_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de teste\n");
        exit(1);
    }

    yyin = input_file;
    initMe();
    yyparse();

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de saída\n");
        exit(1);
    }
    set_output_file(output_file);

    fprintf(stdout, "Operação realizada com sucesso!\nImprimindo a tabela hash.\n");
    printHashTable();
    fprintf(stdout, "Terminado.\n\n");
    return 0;
}
