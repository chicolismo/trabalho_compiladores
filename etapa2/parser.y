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
%left '*'

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

block: '{' cmds '}'
    ;

cmds: cmd ';' cmds
    | cmd
    ;

cmd: TK_IDENTIFIER '=' expression
    | TK_IDENTIFIER '[' LIT_INTEGER ']' '=' expression
    | KW_READ '>' TK_IDENTIFIER
    | KW_PRINT exp_list
    | KW_RETURN expression
    | KW_IF exp KW_THEN cmd
    | KW_IF exp KW_THEN cmd KW_ELSE cmd
    | KW_WHILE '(' exp ')' cmd
    | block
    |
    ;

exp_list: expression ',' exp_list
    | expression
    ;

expression: LIT_STRING
    | exp
    ;

exp: LIT_INTEGER
    | LIT_REAL
    | LIT_CHAR
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' LIT_INTEGER ']'
    | '('exp ')'
    | exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | exp '<' exp
    | exp '>' exp
    | '!' exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_GE exp
    | exp OPERATOR_EQ exp
    | exp OPERATOR_NE exp
    | exp OPERATOR_AND exp
    | exp OPERATOR_OR exp
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
| LIT_STRING
;



%%



int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
}

