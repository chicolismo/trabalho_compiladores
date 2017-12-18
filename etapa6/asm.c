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

void generate_label(TAC *tac) {
    
}

void generate_temp(TAC *tac) {
    
}

void generate_math_operation(TAC *tac) {
    
}

void generate_compare_operation(TAC *tac) {
    
}

void generate_logic_operation(TAC *tac) {
    
}

void generate_not(TAC *tac) {
    
}

void generate_read(TAC *tac) {
    
}

void generate_print(TAC *tac) {
    
}

void generate_return(TAC *tac) {
    
}

void generate_jz(TAC *tac) {
    
}

void generate_jump(TAC *tac) {
    
}

void generate_assign(TAC *tac) {
    
}

void generate_array_assign(TAC *tac) {
    
}

void generate_array_index(TAC *tac) {
    
}

void generate_begin_func(TAC *tac) {
    
}

void generate_end_func(TAC *tac) {
    
}

void generate_call(TAC *tac) {
    
}

void generate_push_arg(TAC *tac) {
    
}

void generate_pop_arg(TAC *tac) {
    
}

void generate_asm(TAC *tac_list) {
    // Open output file
    char *filename;
    filename = calloc(sizeof(char), strlen(output_filename)+3);
    sprintf(filename,"%s.s", output_filename);
    output_file = fopen(filename,"w");

    // Define asm version for macOS
    fprintf(output_file, "\t.section\t__TEXT,__text,regular,pure_instructions\n");
    fprintf(output_file, "\t.macosx_version_min\t10, 13\n");
    
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
    
    // Read TAC and generate asm
    int tac_index = 0;
    TAC *tac = tac_list;
    
    while (tac) {
        switch (tac->type) {

        case TAC_SYMBOL:
            break;

        case TAC_LABEL:
            generate_label(tac); break;

        case TAC_TEMP:
            generate_temp(tac); break;

        case TAC_ADD:
        case TAC_SUB:
        case TAC_MUL:
        case TAC_DIV:
            generate_math_operation(tac); break;

        case TAC_LT:
        case TAC_GT:
        case TAC_LE:
        case TAC_GE:
        case TAC_EQ:
        case TAC_NE:
            generate_compare_operation(tac); break;

        case TAC_AND:
        case TAC_OR:
            generate_logic_operation(tac); break;

        case TAC_NOT:
            generate_not(tac); break;

        case TAC_READ:
            generate_read(tac); break;

        case TAC_PRINT:
            generate_print(tac); break;

        case TAC_RET:
            generate_return(tac); break;

        case TAC_JZ:
            generate_jz(tac); break;

        case TAC_JMP:
            generate_jump(tac); break;

        case TAC_ASSIGN:
            generate_assign(tac); break;

        case TAC_ARRAY_ASSIGN:
            generate_array_assign(tac); break;

        case TAC_ARRAY_INDEX:
            generate_array_index(tac); break;

        case TAC_BEGIN_FUNC:
            generate_begin_func(tac); break;

        case TAC_END_FUNC:
            generate_end_func(tac); break;

        case TAC_CALL:
            generate_call(tac); break;

        case TAC_PUSH_ARG:
            generate_push_arg(tac); break;

        case TAC_POP_ARG:
            generate_pop_arg(tac); break;

        default:
            break;
        }
    }
}
