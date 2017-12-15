%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "semantic.h"
#include "tac.h"

int yylex();
int yyerror(char *text);
extern int getLineNumber();

FILE *output_file = NULL;

%}

%union {
	AST *ast;
	HashNode *symbol;
}

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%type<ast> program

%type<ast> identifier
%type<ast> literal_integer
%type<ast> literal_real
%type<ast> literal_char
%type<ast> literal_string

%type<ast> declarations
%type<ast> dec
%type<ast> var_dec
%type<ast> fun_dec
%type<ast> literals_list
%type<ast> params
%type<ast> params_list
%type<ast> param
%type<ast> args
%type<ast> args_list
%type<ast> block
%type<ast> cmd
%type<ast> cmds
%type<ast> print_args
%type<ast> type
%type<ast> literal
%type<ast> expression
%type<ast> any_expression

%type<symbol> TK_IDENTIFIER
%type<symbol> LIT_INTEGER
%type<symbol> LIT_REAL
%type<symbol> LIT_CHAR
%type<symbol> LIT_STRING


%left '+'
%left '-'
%left '*'
%left '/'

%start program

%%

program: declarations {
    $$ = $1;
    fprintf(stdout, "Imprimindo a árvore\n");
    printAST($$, 0);

    TAC *tac = TAC_reverse_list(TAC_generate_code($1));
    TAC_print_forward(tac);

    generateCode(output_file, $$);
    semanticVerification($$);
};

declarations: dec declarations { $$ = createAST(AST_DECL_LIST, 0, $1, $2, 0, 0); }
            |                  { $$ = 0; }
            ;

dec: var_dec { $$ = $1; }
   | fun_dec { $$ = $1; }
   ;


var_dec: identifier ':' type '=' literal ';'                           { $$ = createAST(AST_VAR_DECL, 0, $1, $3, $5, 0); }
       | identifier ':' type '[' literal_integer ']' literals_list ';' { $$ = createAST(AST_ARY_DECL, 0, $1, $3, $5, $7); }
       ;

identifier: TK_IDENTIFIER { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }

literal_integer: LIT_INTEGER { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }

literal_real: LIT_REAL { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }

literal_char: LIT_CHAR { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }

literals_list: literal literals_list { $$ = createAST(AST_LIT_LIST, 0, $1, $2, 0, 0); }
             |                       { $$ = createAST(AST_EMPTY_LIT_LIST, 0, 0, 0, 0, 0); }
             ;

fun_dec: '(' type ')' identifier '(' params ')' block { $$ = createAST(AST_FUNC_DECL, 0, $2, $4, $6, $8); }
       ;

params: params_list { $$ = $1; }
      |             { $$ = NULL; }
      ;

params_list: param ',' params_list { $$ = createAST(AST_PARAM_LIST, 0, $1, $3, 0, 0); }
           | param                 { $$ = $1; }
           ;

param: identifier ':' type { $$ = createAST(AST_PARAM, 0, $1, $3, 0, 0); }
     ;

args: args_list { $$ = $1; }
    |           { $$ = NULL; }
    ;

args_list: expression ',' args_list { $$ = createAST(AST_ARG_LIST, 0, $1, $3, 0, 0); }
         | expression               { $$ = $1; }
         ;

block: '{' cmds '}' { $$ = createAST(AST_BLOCK, 0, $2, 0, 0, 0); }
     ;

cmds: cmd ';' cmds { $$ = createAST(AST_CMD_LIST, 0, $1, $3, 0, 0);}
    | cmd { $$ = $1; }
    ;


cmd: identifier '=' expression                        { $$ = createAST(AST_VAR_ASSIGN, 0, $1, $3, 0, 0); }
   | identifier '[' expression ']' '=' expression     { $$ = createAST(AST_ARY_ASSIGN, 0, $1, $3, $6, 0); }
   | KW_READ '>' identifier                           { $$ = createAST(AST_READ, 0, $3, 0, 0, 0); }
   | KW_PRINT print_args                              { $$ = createAST(AST_PRINT, 0, $2, 0, 0, 0); }
   | KW_RETURN expression                             { $$ = createAST(AST_RETURN, 0, $2, 0, 0, 0); }
   | KW_IF '(' expression ')' KW_THEN cmd             { $$ = createAST(AST_IF, 0, $3, $6, 0, 0); }
   | KW_IF '(' expression ')' KW_THEN cmd KW_ELSE cmd { $$ = createAST(AST_IF_ELSE, 0, $3, $6, $8, 0); }
   | KW_WHILE '(' expression ')' cmd                  { $$ = createAST(AST_WHILE, 0, $3, $5, 0, 0); }
   | block                                            { $$ = $1; }
   |                                                  { $$ = NULL; }
   ;


type: KW_BYTE   { $$ = createAST(AST_TYPE_BYTE, 0, 0, 0, 0, 0); }
    | KW_SHORT  { $$ = createAST(AST_TYPE_SHORT, 0, 0, 0, 0, 0); }
    | KW_LONG   { $$ = createAST(AST_TYPE_LONG, 0, 0, 0, 0, 0); }
    | KW_FLOAT  { $$ = createAST(AST_TYPE_FLOAT, 0, 0, 0, 0, 0); }
    | KW_DOUBLE { $$ = createAST(AST_TYPE_DOUBLE, 0, 0, 0, 0, 0); }
    ;


literal_string: LIT_STRING { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }


literal: literal_integer { $$ = $1; }
       | literal_real    { $$ = $1; }
       | literal_char    { $$ = $1; }
       ;


print_args: any_expression ',' print_args { $$ = createAST(AST_PRINT_ARGS, 0, $1, $3, 0, 0); }
          | any_expression                { $$ = $1; }
          ;

any_expression: literal_string { $$ = $1; }
              | expression { $$ = $1; }
              ;

expression: literal                            { $$ = $1; }
          | identifier                         { $$ = $1; }
          | identifier '[' expression ']'      { $$ = createAST(AST_ARY_INDEX, 0, $1, $3, 0, 0); }
          | identifier '(' args ')'            { $$ = createAST(AST_FUNC_CALL, 0, $1, $3, 0, 0); }
          | '(' expression ')'                 { $$ = createAST(AST_PARENS_EXPR, 0, $2, 0, 0, 0); }
          | expression '+' expression          { $$ = createAST(AST_ADD, 0, $1, $3, 0, 0); }
          | expression '-' expression          { $$ = createAST(AST_SUB, 0, $1, $3, 0, 0); }
          | expression '*' expression          { $$ = createAST(AST_MUL, 0, $1, $3, 0, 0); }
          | expression '/' expression          { $$ = createAST(AST_DIV, 0, $1, $3, 0, 0); }
          | expression '<' expression          { $$ = createAST(AST_LT, 0, $1, $3, 0, 0); }
          | expression '>' expression          { $$ = createAST(AST_GT, 0, $1, $3, 0, 0); }
          | '!' expression                     { $$ = createAST(AST_NOT, 0, $2, 0, 0, 0); }
          | expression OPERATOR_LE expression  { $$ = createAST(AST_LE, 0, $1, $3, 0, 0); }
          | expression OPERATOR_GE expression  { $$ = createAST(AST_GE, 0, $1, $3, 0, 0); }	
          | expression OPERATOR_EQ expression  { $$ = createAST(AST_EQ, 0, $1, $3, 0, 0); }
          | expression OPERATOR_NE expression  { $$ = createAST(AST_NE, 0, $1, $3, 0, 0); }
          | expression OPERATOR_AND expression { $$ = createAST(AST_AND, 0, $1, $3, 0, 0); }
          | expression OPERATOR_OR expression  { $$ = createAST(AST_OR, 0, $1, $3, 0, 0); }
          ;


%%

void set_output_file(FILE *fh) {
    output_file = fh;
}

int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
}
