%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"

int yylex();
int yyerror(char *text);
extern int getLineNumber();

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

%type<ast> args
%type<ast> args_list
%type<ast> expression
%type<ast> any_expression

%left '+'
%left '-'
%left '*'
%left '/'

%start program

%%

program: declarations
    ;

declarations: dec declarations
    |
    ;

dec: var_dec
    | fun_dec
    ;

var_dec: TK_IDENTIFIER ':' type '=' literal ';'
    | TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' literals_list ';'
    ;

literals_list: literal literals_list
    |
    ;

fun_dec: fun_header block
    ;

fun_header: '(' type ')' TK_IDENTIFIER '(' params ')'
    ;

params: params_list
    |
    ;

params_list: param ',' params_list
    | param
    ;

param: TK_IDENTIFIER ':' type
    ;

args: args_list                           { $$ = $1; }
    |                                     { $$ = NULL; }
    ;

args_list: expression ',' args_list       { $$ = createAST(AST_LIST,0,$1,$3,0,0); }
    | expression                          { $$ = $1; }
    ;

block: '{' cmds '}'
    ;

cmds: cmd ';' cmds
    | cmd
    ;

cmd: TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' expression ']' '=' expression
    | KW_READ '>' TK_IDENTIFIER
    | KW_PRINT expressions_list
    | KW_RETURN expression
    | KW_IF '(' expression ')' KW_THEN cmd
    | KW_IF '(' expression ')' KW_THEN cmd KW_ELSE cmd
    | KW_WHILE '(' expression ')' cmd
    | block
    |
    ;

expressions_list: any_expression ',' expressions_list
    | any_expression
    ;

type: KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;

literal: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    ;

expression: LIT_INTEGER                   { $$ = createAST(AST_SYMBOL,$1,0,0,0,0); }
    | LIT_REAL                            { $$ = createAST(AST_SYMBOL,$1,0,0,0,0); }
    | LIT_CHAR                            { $$ = createAST(AST_SYMBOL,$1,0,0,0,0); }
    | TK_IDENTIFIER                       { $$ = createAST(AST_SYMBOL,$1,0,0,0,0); }
    | TK_IDENTIFIER '[' expression ']'    { $$ = createAST(AST_SYMBOL,$1,$3,0,0,0); }
    | TK_IDENTIFIER '(' args ')'          { $$ = createAST(AST_SYMBOL,$1,$3,0,0,0); }
    | '(' expression ')'                  { $$ = $2; }
    | expression '+' expression           { $$ = createAST(AST_ADD,0,$1,$3,0,0); }
    | expression '-' expression           { $$ = createAST(AST_SUB,0,$1,$3,0,0); }
    | expression '*' expression           { $$ = createAST(AST_MUL,0,$1,$3,0,0); }
    | expression '/' expression           { $$ = createAST(AST_DIV,0,$1,$3,0,0); }
    | expression '<' expression           { $$ = createAST(AST_LESS,0,$1,$3,0,0); }
    | expression '>' expression           { $$ = createAST(AST_GREATER,0,$1,$3,0,0); }
    | '!' expression                      { $$ = createAST(AST_NOT,0,$2,0,0,0); }
    | expression OPERATOR_LE expression   { $$ = createAST(AST_LE,0,$1,$3,0,0); }
    | expression OPERATOR_GE expression   { $$ = createAST(AST_GE,0,$1,$3,0,0); }	
    | expression OPERATOR_EQ expression   { $$ = createAST(AST_EQ,0,$1,$3,0,0); }
    | expression OPERATOR_NE expression   { $$ = createAST(AST_NE,0,$1,$3,0,0); }
    | expression OPERATOR_AND expression  { $$ = createAST(AST_AND,0,$1,$3,0,0); }
    | expression OPERATOR_OR expression   { $$ = createAST(AST_OR,0,$1,$3,0,0); }
    ;

any_expression: LIT_STRING                { $$ = createAST(AST_SYMBOL,$1,0,0,0,0); }
    | expression                          { $$ = $1; }
    ;

%%

int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
}
