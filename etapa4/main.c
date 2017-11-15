#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

extern void initMe();
extern FILE *yyin;
extern int yyparse();
extern void set_output_file(FILE *fh);

int main(int argc, char **argv) {
    
    if (argc < 3) {
        fprintf(stderr, "ERRO: Arquivo nao informado. Eh preciso fornecer um arquivo de entrada e um arquivo de saida.\n");
        exit(1);
	}

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "ERRO: Arquivo de entrada inexistente.\n");
        exit(2);
    }
    yyin = input_file;

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        fprintf(stderr, "ERRO: Arquivo de saida inexistente.\n");
        fclose(input_file);
        exit(2);
    }
    set_output_file(output_file);

    initMe();
    yyparse();

    fprintf(stderr, "Compilacao realizada com sucesso.\n\n");
    fclose(input_file);
    fclose(output_file);
    exit(0);
}
