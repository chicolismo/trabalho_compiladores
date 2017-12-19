#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "tac.h"

FILE *output_file;
static int label_index = 0;

void generate_scalar_var(HashNode *identifier) {
    
}

void generate_vector_var(HashNode *identifier) {
    
}

void generate_label(TAC *tac) {
    fprintf(output_file, "%s:\n", tac->res->string);
}

void generate_temp(TAC *tac) {
    int end_label = label_index++;
    
    fprintf(output_file, "\tjmp\tL_%d\n", end_label);
    fprintf(output_file, "%s:\n", tac->res->string);
    
    generate_scalar_var(tac->res);
    
    fprintf(output_file, "L_%d:\n", end_label);
}

void generate_math_or_logic_operation(TAC *tac) {
    char operation[6] = "\0";
    switch (tac->type) {
        case TAC_ADD: strcpy(operation, "addl"); break;
        case TAC_SUB: strcpy(operation, "subl"); break;
        case TAC_MUL: strcpy(operation, "imull"); break;
        case TAC_DIV: strcpy(operation, "idivl"); break;
        case TAC_AND: strcpy(operation, "andl"); break;
        case TAC_OR: strcpy(operation, "orl"); break;
        default: return;
    }
    
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->string);
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->string);
    fprintf(output_file, "\t%s\t%%ebx, %%eax\n", operation);
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->string);
}

void generate_compare_operation(TAC *tac) {
    char operation[6] = "\0";
    switch (tac->type) {
        case TAC_LT: strcpy(operation, "setl"); break;
        case TAC_GT: strcpy(operation, "setg"); break;
        case TAC_LE: strcpy(operation, "setle"); break;
        case TAC_GE: strcpy(operation, "setge"); break;
        case TAC_EQ: strcpy(operation, "sete"); break;
        case TAC_NE: strcpy(operation, "setne"); break;
        default: return;
    }
    
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ecx\n", tac->op1->string);
    fprintf(output_file, "\tcmpl\t%s(%%rip), %%ecx\n", tac->op2->string);
    fprintf(output_file, "\t%s\t%%dl\n", operation);
    fprintf(output_file, "\tandb\t$1, %%dl\n");
    fprintf(output_file, "\tmovzbl\t%%dl, %%ecx\n");
    fprintf(output_file, "\tmovl\t%%ecx, %s(%%rip)\n", tac->res->string);
}

void generate_not(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ecx\n", tac->op1->string);
    fprintf(output_file, "\tcmpl\t$0, %%ecx\n");
    fprintf(output_file, "\tsetne\t%%dl\n");
    fprintf(output_file, "\txorb\t$-1, %%dl\n");
    fprintf(output_file, "\tandb\t$1, %%dl\n");
    fprintf(output_file, "\tmovzbl\t%%dl, %%edx\n");
    fprintf(output_file, "\tmovl\t%%edx, %s(%%rip)\n", tac->res->string);
}

void generate_read(TAC *tac) {
    int format_label = label_index++;
    int end_label = label_index++;
    
    fprintf(output_file, "\tleaq\tL_%d(%%rip), %%rdi\n", format_label);
    fprintf(output_file, "\tleaq\t%s(%%rip), %%rsi\n", tac->res->string);
    fprintf(output_file, "\tmovb\t$0, %%al\n");
    fprintf(output_file, "\tcallq\t_scanf\n");
    fprintf(output_file, "\tjmp\tL_%d\n", end_label);
    
    fprintf(output_file, "L_%d:\n", format_label);
    fprintf(output_file, "\t.asciz\t\"%%ld\"\n");
    
    fprintf(output_file, "L_%d:\n", end_label);
}

void generate_print(TAC *tac) {
    int format_label = label_index++;
    int end_label = label_index++;
    
    fprintf(output_file, "\tleaq\tL_%d(%%rip), %%rdi\n", format_label);
    fprintf(output_file, "\tmovq\t%s(%%rip), %%rsi\n", tac->res->string);
    fprintf(output_file, "\tmovb\t$0, %%al\n");
    fprintf(output_file, "\tcallq\t_printf\n");
    fprintf(output_file, "\tjmp\tL_%d\n", end_label);
    
    fprintf(output_file, "L_%d:\n", format_label);
    
    if (tac->res->type == SYMBOL_STRING) {
        fprintf(output_file, "\t.asciz\t\"%s\"\n", tac->res->string);
    } else {
        fprintf(output_file, "\t.asciz\t\"%%ld\"\n");
    }
    
    fprintf(output_file, "L_%d:\n", end_label);
}

void generate_return(TAC *tac) {
    if(tac->res->type == SYMBOL_LIT_INTEGER ||
       tac->res->type == SYMBOL_LIT_REAL ||
       tac->res->type == SYMBOL_LIT_CHAR) {
        fprintf(output_file, "\tmovl\t$%s, %%eax\n", tac->res->string);
    } else {
        fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", tac->res->string);
    }
    
    fprintf(output_file, "\tpopq\t%%rbp\n");
    fprintf(output_file, "\tretq\n");
}

void generate_jz(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->string);
    fprintf(output_file, "\tcmpl\t$0, %%eax\n");
    fprintf(output_file, "\tje\t%s\n", tac->res->string);
}

void generate_jump(TAC *tac) {
    fprintf(output_file, "\tjmp\t%s\n", tac->res->string);
}

void generate_assign(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->string);
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->string);
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
            case TAC_AND:
            case TAC_OR:
                generate_math_or_logic_operation(tac); break;

            case TAC_LT:
            case TAC_GT:
            case TAC_LE:
            case TAC_GE:
            case TAC_EQ:
            case TAC_NE:
                generate_compare_operation(tac); break;

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
        
        tac = tac->next;
    }
    
    fclose(output_file);
}
