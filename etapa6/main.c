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
    
    if (argc < 2) {
        fprintf(stderr, "ERRO: Arquivo não informado.\n");
        return 1;
	}

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        fprintf(stderr, "ERRO: Arquivo de entrada inexistente.\n");
        return 2;
    }
    yyin = input_file;

//    FILE *output_file = fopen(argv[2], "w");
//    if (output_file == NULL) {
//        fprintf(stderr, "ERRO: Arquivo de saída inexistente.\n");
//        fclose(input_file);
//        return 2;
//    }
//    set_output_file(output_file);

    initMe();
    yyparse();

    fprintf(stderr, "Compilação realizada com sucesso.\n\n");
    fclose(input_file);
//    fclose(output_file);

    return EXIT_SUCCESS; // 0
}
