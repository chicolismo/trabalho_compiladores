%{

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int yylex();
int yyerror(char *text);
extern int getLineNumber();

%}

%union { HashNode *symbol; }

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

args: args_list
    |
    ;

args_list: expression ',' args_list
    | expression
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

expression: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expression ']'
    | TK_IDENTIFIER '(' args ')'
    | '(' expression ')'
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '<' expression
    | expression '>' expression
    | '!' expression
    | expression OPERATOR_LE expression
    | expression OPERATOR_GE expression
    | expression OPERATOR_EQ expression
    | expression OPERATOR_NE expression
    | expression OPERATOR_AND expression
    | expression OPERATOR_OR expression
    ;

any_expression: LIT_STRING
    | expression
    ;



%%



int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
}

