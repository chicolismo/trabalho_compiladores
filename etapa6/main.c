#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

extern void initMe();
extern FILE *yyin;
extern int yyparse();
extern void set_output_file(FILE *fh);

int main(int argc, char **argv) {
    
    if (argc < 3) {
        fprintf(stderr, "ERRO: Arquivo não informado. É preciso fornecer um arquivo de entrada e um arquivo de saída.\n");
        return 1;
	}

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "ERRO: Arquivo de entrada inexistente.\n");
        return 2;
    }
    yyin = input_file;

    strcpy(output_filename, argv[2]);

    initMe();
    yyparse();

    fprintf(stderr, "Compilação realizada com sucesso.\n\n");
    fclose(input_file);

    return EXIT_SUCCESS;
}
