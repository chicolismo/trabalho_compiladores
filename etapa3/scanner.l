%{
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

int currentLine = 1;
int running = 1;

int yywrap();
int isRunning();
int getLineNumber();
void initMe();
%}

%x MULTILINE_COMMENT

%%

[0-9]+          { yylval.symbol = setHashNode(yytext, LIT_INTEGER); return LIT_INTEGER; }
[0-9]+"."[0-9]+ { yylval.symbol = setHashNode(yytext, LIT_REAL);    return LIT_REAL; }
'([^\\]|\\.)'   { yylval.symbol = setHashNode(yytext, LIT_CHAR);    return LIT_CHAR; }
\"(\\.|[^"])*\" { yylval.symbol = setHashNode(yytext, LIT_STRING);  return LIT_STRING; }

[\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=\!\&\$\#]  return yytext[0];

"<="   return OPERATOR_LE;
">="   return OPERATOR_GE;
"=="   return OPERATOR_EQ;
"!="   return OPERATOR_NE;
"&&"   return OPERATOR_AND;
"||"   return OPERATOR_OR;

byte   return KW_BYTE;
short  return KW_SHORT;
long   return KW_LONG;
float  return KW_FLOAT;
double return KW_DOUBLE;
if     return KW_IF;
then   return KW_THEN;
else   return KW_ELSE;
while  return KW_WHILE;
for    return KW_FOR;
read   return KW_READ;
return return KW_RETURN;
print  return KW_PRINT;

[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])* { yylval.symbol = setHashNode(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }

[ \t]+ ;
"//".* ;
"\n" ++currentLine;

<INITIAL>"/*" BEGIN(MULTILINE_COMMENT);

<MULTILINE_COMMENT>"*/" BEGIN(INITIAL);
<MULTILINE_COMMENT>. ;

. return TOKEN_ERROR;

%%

int yywrap() {
    running = 0;
    return 1;
}

int isRunning() {
    return running;
}

int getLineNumber() {
    return currentLine;
}

void initMe() {
    initializeHashTable();
}
