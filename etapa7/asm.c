#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"
#include "tac.h"

FILE *output_file;
static int has_data_section_init = 0;
static int lcfi_counter = 0;

char *get_string(HashNode *node) {
    switch (node->type) {
        case SYMBOL_LIT_INTEGER:
        case SYMBOL_LIT_REAL:
        case SYMBOL_LIT_CHAR:
        case SYMBOL_STRING:
            return node->asm_string;
            
        default:
            return node->string;
    }
}

AST *get_declaration(char *identifier, int type, int id_index, int data_index, AST *ast) {
    if (!ast) {
        return NULL;
    }
    
    if (ast->type == type &&
        strcmp(identifier, ast->son[id_index]->symbol->string) == 0) {
        return ast->son[data_index];
    }
    
    AST *aux;
    int i;
    for (i=0; i<MAX_SONS; i++) {
        aux = get_declaration(identifier, type, id_index, data_index, ast->son[i]);
        if (aux) {
            return aux;
        }
    }
    
    return NULL;
}

void init_main_section() {
    fprintf(output_file, "\t.section\t__TEXT,__text,regular,pure_instructions\n");
    fprintf(output_file, "\t.macosx_version_min\t10, 13\n");
    fprintf(output_file, "\t.globl\t_main\n");
    fprintf(output_file, "\t.p2align\t4, 0x90\n");
}

void init_data_section() {
    if (!has_data_section_init) {
        fprintf(output_file, "\n\t.section\t__DATA,__data\n");
        has_data_section_init = 1;
    }
}

void init_text_section() {
    fprintf(output_file, "\n\t.section\t__TEXT,__cstring,cstring_literals\n");
    fprintf(output_file, "L_.str:\n");
    fprintf(output_file, "\t.asciz\t\"%%d\"\n");
}

void generate_string_const(HashNode *identifier) {
    fprintf(output_file, "%s:\n", identifier->asm_string);
    fprintf(output_file, "\t.asciz\t%s\n", identifier->string);
}

void generate_not_initialized_scalar_var(HashNode *identifier) {
    fprintf(output_file, "\t.comm\t%s,2,2\n", get_string(identifier));
}

void generate_not_initialized_vector_var(HashNode *identifier) {
    int length = 4 * identifier->length;
    fprintf(output_file, "\t.comm\t%s,%d,4\n", get_string(identifier), length);
}

void generate_initialized_scalar_var(HashNode *identifier, AST *value) {
    init_data_section();
    
    fprintf(output_file, "\t.globl\t%s\n", identifier->asm_string);
    fprintf(output_file, "\t.p2align\t2\n");
    fprintf(output_file, "%s:\n", identifier->asm_string);
    
    if (identifier->type == SYMBOL_IDENTIFIER_SCALAR) {
        fprintf(output_file, "\t.long\t%s\n", value->symbol->string);
    } else {
        fprintf(output_file, "\t.long\t%s\n", identifier->string);
    }
}

void generate_initialized_vector_var(HashNode *identifier, AST *values) {
    init_data_section();
    
    fprintf(output_file, "\t.globl\t%s\n", identifier->asm_string);
    fprintf(output_file, "\t.p2align\t4\n");
    fprintf(output_file, "%s:\n", identifier->asm_string);
    
    AST *aux = values;
    do {
        fprintf(output_file, "\t.long\t%s\n", aux->son[0]->symbol->string);
        aux = aux->son[1];
    } while(aux->type == AST_LIT_LIST);
}

void generate_label(TAC *tac) {
    fprintf(output_file, "%s:\n", tac->res->string);
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
    
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->op1));
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ebx\n", get_string(tac->op2));
    fprintf(output_file, "\t%s\t%%ebx, %%eax\n", operation);
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", get_string(tac->res));
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
    
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ecx\n", get_string(tac->op1));
    fprintf(output_file, "\tcmpl\t%s(%%rip), %%ecx\n", get_string(tac->op2));
    fprintf(output_file, "\t%s\t%%dl\n", operation);
    fprintf(output_file, "\tandb\t$1, %%dl\n");
    fprintf(output_file, "\tmovzbl\t%%dl, %%ecx\n");
    fprintf(output_file, "\tmovl\t%%ecx, %s(%%rip)\n", get_string(tac->res));
}

void generate_not(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%ecx\n", get_string(tac->op1));
    fprintf(output_file, "\tcmpl\t$0, %%ecx\n");
    fprintf(output_file, "\tsetne\t%%dl\n");
    fprintf(output_file, "\txorb\t$-1, %%dl\n");
    fprintf(output_file, "\tandb\t$1, %%dl\n");
    fprintf(output_file, "\tmovzbl\t%%dl, %%edx\n");
    fprintf(output_file, "\tmovl\t%%edx, %s(%%rip)\n", get_string(tac->res));
}

void generate_read(TAC *tac) {
    fprintf(output_file, "\tleaq\tL_.str(%%rip), %%rdi\n");
    fprintf(output_file, "\tleaq\t%s(%%rip), %%rsi\n", tac->res->asm_string);
    fprintf(output_file, "\tmovb\t$0, %%al\n");
    fprintf(output_file, "\tcallq\t_scanf\n");
}

void generate_print(TAC *tac) {
    if (tac->res->type == SYMBOL_STRING) {
        fprintf(output_file, "\tleaq\t%s(%%rip), %%rdi\n", tac->res->asm_string);
    } else {
        fprintf(output_file, "\tleaq\tL_.str(%%rip), %%rdi\n");
    }
    
    fprintf(output_file, "\tmovl\t%s(%%rip), %%esi\n", get_string(tac->res));
    fprintf(output_file, "\tmovb\t$0, %%al\n");
    fprintf(output_file, "\tcallq\t_printf\n");
}

void generate_return(TAC *tac) {
    if(tac->res->type == SYMBOL_LIT_INTEGER ||
       tac->res->type == SYMBOL_LIT_REAL ||
       tac->res->type == SYMBOL_LIT_CHAR) {
        fprintf(output_file, "\tmovl\t$%s, %%eax\n", tac->res->string);
    } else {
        fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->res));
    }
    
    fprintf(output_file, "\tpopq\t%%rbp\n");
    fprintf(output_file, "\tretq\n");
}

void generate_jz(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->op1));
    fprintf(output_file, "\tcmpl\t$0, %%eax\n");
    fprintf(output_file, "\tje\t%s\n", get_string(tac->res));
}

void generate_jump(TAC *tac) {
    fprintf(output_file, "\tjmp\t%s\n", get_string(tac->res));
}

void generate_assign(TAC *tac) {
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->op1));
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", get_string(tac->res));
}

void generate_array_assign(TAC *tac) {
    fprintf(output_file, "\tmovq\t%s@GOTPCREL(%%rip), %%rcx\n", get_string(tac->res));
    fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->op2));
    fprintf(output_file, "\tmovslq\t%s(%%rip), %%rdx\n", get_string(tac->op1));
    fprintf(output_file, "\tmovl\t%%eax, (%%rcx,%%rdx,4)\n");
}

void generate_array_index(TAC *tac) {
    fprintf(output_file, "\tmovq\t%s@GOTPCREL(%%rip), %%rcx\n", get_string(tac->op1));
    fprintf(output_file, "\tmovslq\t%s(%%rip), %%rdx\n", get_string(tac->op2));
    fprintf(output_file, "\tmovl\t(%%rcx,%%rdx,4), %%eax\n");
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", get_string(tac->res));
}

void generate_begin_func(TAC *tac) {
    fprintf(output_file, "_%s:\n", get_string(tac->res));
    fprintf(output_file, "\t.cfi_startproc\n");
    fprintf(output_file, "\tpushq\t%%rbp\n");
    fprintf(output_file, "Lcfi%d:\n", lcfi_counter++);
    fprintf(output_file, "\t.cfi_def_cfa_offset\t16\n");
    fprintf(output_file, "Lcfi%d:\n", lcfi_counter++);
    fprintf(output_file, "\t.cfi_offset %%rbp,\t-16\n");
    fprintf(output_file, "\tmovq\t%%rsp, %%rbp\n");
    fprintf(output_file, "Lcfi%d:\n", lcfi_counter++);
    fprintf(output_file, "\t.cfi_def_cfa_register\t%%rbp\n");
}

void generate_end_func(TAC *tac) {
    fprintf(output_file, "\t.cfi_endproc\n\n");
}

void generate_call(TAC *tac) {
    fprintf(output_file, "\tcallq\t_%s\n", get_string(tac->op1));
    fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n", get_string(tac->res));
}

void generate_push_arg(TAC *tac) {
    TAC *next_tac = tac->next;
    int param_index = 0;
    
    // Find function call and param index
    while (next_tac) {
        if (next_tac->type == TAC_CALL &&
            !strcmp(tac->op1->string, next_tac->op1->string) &&
            tac->callId == next_tac->callId) {
            break;
        } else if (next_tac->type == TAC_PUSH_ARG &&
                   !strcmp(tac->op1->string, next_tac->op1->string) &&
                   tac->callId == next_tac->callId) {
            param_index++;
        }
        next_tac = next_tac->next;
    }
    
    // Find params list for function name
    AST *params = get_declaration(next_tac->op1->string, AST_FUNC_DECL, 1, 2, ast_root);
    
    // Find param for arg
    while (params && param_index) {
        param_index--;
        params = params->son[1];
    }
    
    if (params) {
        if (params->type == AST_PARAM_LIST) {
            params = params->son[0];
        }
        
        fprintf(output_file, "\tmovl\t%s(%%rip), %%eax\n", get_string(tac->res));
        fprintf(output_file, "\tmovl\t%%eax, %s(%%rip)\n",
                get_string(params->son[0]->symbol));
    }
}

void generate_asm(TAC *tac_list) {
    // Open output file
    char *filename;
    filename = calloc(sizeof(char), strlen(output_filename)+3);
    sprintf(filename,"%s.s", output_filename);
    output_file = fopen(filename,"w");

    init_main_section();
    
    // Read TAC and generate asm
    int tac_index = 0;
    TAC *tac = tac_list;
    
    while (tac) {
        switch (tac->type) {
            case TAC_SYMBOL:
                break;

            case TAC_LABEL:
                generate_label(tac); break;

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

            default:
                break;
        }
        
        tac = tac->next;
    }
    
    // Create not initialized variables
    HashNode *scan;
    AST *value;
    int i;
    
    for (i=0; i<HASH_SIZE; i++) {
        scan = hashTable[i];
        
        while(scan != NULL) {
            switch(scan->type) {
                case SYMBOL_IDENTIFIER_SCALAR:
                    value = get_declaration(scan->string, AST_PARAM, 0, 0, ast_root);
                    if (value && value->type == AST_SYMBOL) {
                        generate_not_initialized_scalar_var(scan);
                    }
                    break;
                    
                case SYMBOL_IDENTIFIER_VECTOR:
                    value = get_declaration(scan->string, AST_ARY_DECL, 0, 3, ast_root);
                    if (value && value->type == AST_EMPTY_LIT_LIST) {
                        generate_not_initialized_vector_var(scan);
                    }
                    break;
                    
                case SYMBOL_TEMP:
                    generate_not_initialized_scalar_var(scan);
                    break;
            }
            scan = scan->next;
        }
    }
    
    // Create section for constants and initilized variables
    init_data_section();
    
    for (i=0; i<HASH_SIZE; i++) {
        scan = hashTable[i];
        while(scan != NULL) {
            switch(scan->type) {
                case SYMBOL_LIT_INTEGER:
                case SYMBOL_LIT_REAL:
                case SYMBOL_LIT_CHAR:
                    generate_initialized_scalar_var(scan, NULL);
                    break;
                    
                case SYMBOL_IDENTIFIER_SCALAR:
                    value = get_declaration(scan->string, AST_VAR_DECL, 0, 2, ast_root);
                    if (value && value->type == AST_SYMBOL) {
                        generate_initialized_scalar_var(scan, value);
                    }
                    break;
                    
                case SYMBOL_IDENTIFIER_VECTOR:
                    value = get_declaration(scan->string, AST_ARY_DECL, 0, 3, ast_root);
                    if (value && value->type == AST_LIT_LIST) {
                        generate_initialized_vector_var(scan, value);
                    }
                    break;
            }
            scan = scan->next;
        }
    }
    
    // Create section for strings
    init_text_section();
    
    for (i=0; i<HASH_SIZE; i++) {
        scan = hashTable[i];
        while(scan != NULL) {
            if (scan->type == SYMBOL_STRING) {
                generate_string_const(scan);
            }
            scan = scan->next;
        }
    }
    
    fclose(output_file);
}
