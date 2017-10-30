%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER
%token<symbol> LIT_REAL
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> program
%type<ast> declarations
%type<ast> dec
%type<ast> var_dec
%type<ast> fun_dec
%type<ast> literals_list
%type<ast> fun_header
%type<ast> params
%type<ast> params_list
%type<ast> param
%type<ast> args
%type<ast> args_list
%type<ast> block
%type<ast> cmd
%type<ast> cmds
%type<ast> expressions_list
%type<ast> type
%type<ast> literal
%type<ast> expression
%type<ast> any_expression

%type<ast> KW_BYTE
%type<ast> KW_SHORT
%type<ast> KW_LONG
%type<ast> KW_FLOAT
%type<ast> KW_DOUBLE


%left '+'
%left '-'
%left '*'
%left '/'

%start program

%%

program: declarations {
                          $$ = $1;
                          printAST($$, 0);
                          //generateCode(output_file, $$);
                      }
       ;

declarations: dec declarations { $$ = createAST(AST_DECL_LIST, 0, $1, $2, 0, 0); }
            |                  { $$ = 0; }
            ;

dec: var_dec { $$ = $1; }
   | fun_dec { $$ = $1; }
   ;

var_dec: TK_IDENTIFIER ':' type '=' literal ';'                       { $$ = createAST(AST_VAR_DECL, 0, $1, $3, $5, 0); }
       | TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' literals_list ';' { $$ = createAST(AST_ARY_DECL, 0, $1, $3, $5, $7); }
       ;

literals_list: literal literals_list
             |                       { $$ = NULL; }
             ;

fun_dec: fun_header block { $$ = createAST(AST_FUNC_DECL, 0, $1, $2, 0, 0); }
       ;

fun_header: '(' type ')' TK_IDENTIFIER '(' params ')' { $$ = createAST(AST_FUNC_HEADER, 0, $2, $4, $6, 0); }
          ;

params: params_list { $$ = $1; }
      |             { $$ = NULL; }
      ;

params_list: param ',' params_list { $$ = createAST(AST_PARAM_LIST, 0, $1, $3, 0, 0); }
           | param                 { $$ = $1; }
           ;

param: TK_IDENTIFIER ':' type { $$ = createAST(AST_PARAM, 0, $1, $3, 0, 0); }
     ;

args: args_list { $$ = $1; }
    |           { $$ = NULL; }
    ;

args_list: expression ',' args_list { $$ = createAST(AST_LIST, 0, $1, $3, 0, 0); }
         | expression               { $$ = $1; }
         ;

block: '{' cmds '}' { $$ = createAST(AST_BLOCK, 0, $2, 0, 0, 0); }
     ;

cmds: cmd ';' cmds { $$ = createAST(AST_CMD_LIST, 0, $1, $3, 0, 0);}
    | cmd { $$ = $1; }
    ;

cmd: TK_IDENTIFIER '=' expression                     { $$ = createAST(AST_VAR_ASSIGN, 0, $1, $3, 0, 0); printAST($$, 0); }
   | TK_IDENTIFIER '[' expression ']' '=' expression  { $$ = createAST(AST_ARY_ASSIGN, 0, $1, $3, $6, 0); printAST($$, 0); }
   | KW_READ '>' TK_IDENTIFIER                        { $$ = createAST(AST_READ, 0, $3, 0, 0, 0); }
   | KW_PRINT expressions_list                        { $$ = createAST(AST_PRINT, 0, $2, 0, 0, 0); }
   | KW_RETURN expression                             { $$ = createAST(AST_RETURN, 0, $2, 0, 0, 0); }
   | KW_IF '(' expression ')' KW_THEN cmd             { $$ = createAST(AST_IF, 0, $3, $6, 0, 0); }
   | KW_IF '(' expression ')' KW_THEN cmd KW_ELSE cmd { $$ = createAST(AST_IF_ELSE, 0, $3, $6, $8, 0); }
   | KW_WHILE '(' expression ')' cmd                  { $$ = createAST(AST_WHILE, 0, $3, $5, 0, 0); }
   | block                                            { $$ = $1; }
   |                                                  { $$ = NULL; }
   ;

expressions_list: any_expression ',' expressions_list { $$ = createAST(AST_EXPR_LIST, 0, $1, $3, 0, 0); }
                | any_expression                      { $$ = $1; }
                ;

type: KW_BYTE   { $$ = createAST(AST_TYPE_BYTE, 0, 0, 0, 0, 0); }
    | KW_SHORT  { $$ = createAST(AST_TYPE_SHORT, 0, 0, 0, 0, 0); }
    | KW_LONG   { $$ = createAST(AST_TYPE_LONG, 0, 0, 0, 0, 0); }
    | KW_FLOAT  { $$ = createAST(AST_TYPE_FLOAT, 0, 0, 0, 0, 0); }
    | KW_DOUBLE { $$ = createAST(AST_TYPE_DOUBLE, 0, 0, 0, 0, 0); }
    ;


literal: LIT_INTEGER { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
       | LIT_REAL    { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
       | LIT_CHAR    { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
       ;

expression: LIT_INTEGER                        { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
          | LIT_REAL                           { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
          | LIT_CHAR                           { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
          | TK_IDENTIFIER                      { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
          | TK_IDENTIFIER '[' expression ']'   { $$ = createAST(AST_SYMBOL, $1, $3, 0, 0, 0); printAST($$, 0); }
          | TK_IDENTIFIER '(' args ')'         { $$ = createAST(AST_SYMBOL, $1, $3, 0, 0, 0); printAST($$, 0); }
          | '(' expression ')'                 { $$ = $2; }
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

any_expression: LIT_STRING { $$ = createAST(AST_SYMBOL, $1, 0, 0, 0, 0); }
              | expression { $$ = $1; }
              ;

%%

void set_output_file(FILE *fh) {
    output_file = fh;
}

int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
}
