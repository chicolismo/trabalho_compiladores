%{
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int yyerror(char *text);

extern int yylex();
extern int getLineNumber();

%}


%token KW_INT
%token KW_REAL
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

%start program

%%

program: decl
       | expr;


type: KW_INT
    | KW_BYTE
    | KW_SHORT
    | KW_LONG
    | KW_FLOAT
    | KW_DOUBLE
    ;


decl: TK_IDENTIFIER ':' type '=' expr
    | TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' ';'
    | TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' '=' list
    ;


literal: LIT_INTEGER
       | LIT_REAL
       | LIT_CHAR
       | LIT_STRING
       ;

list:
    ;

params:
      ;

expr: TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' params ')'
    | '(' expr ')'
    | literal
    ;

%%

int yyerror(char *text) {
    printf("Erro de sintaxe na linha %d\n", getLineNumber());
    exit(3);
    return 3;
}
