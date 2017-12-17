#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "tac.h"

FILE *output_file;

void generate_scalar_var(HashNode *identifier) {
}

void generate_vector_var(HashNode *identifier) {
}

void generate_asm(TAC *tac_list) {
    // Open output file
    char *filename;
    filename = calloc(sizeof(char), strlen(output_filename)+3);
    sprintf(filename,"%s.s", output_filename);
    output_file = fopen(filename,"w");

    // Create var for all hash nodes
    HashNode *scan;
    int i;
    for (i=0; i<HASH_SIZE; i++) {
        scan = hashTable[i];

        while(scan != NULL) {
            switch(scan->type) {

            case SYMBOL_LIT_INTEGER:
            case SYMBOL_LIT_REAL:
            case SYMBOL_LIT_CHAR:
            case SYMBOL_STRING:
            case SYMBOL_IDENTIFIER_SCALAR:
                generate_scalar_var(scan); break;

            case SYMBOL_IDENTIFIER_VECTOR:
                generate_vector_var(scan); break;
            }

            scan = scan->next;
        }
    }
}
