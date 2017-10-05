%{
#include "tokens.h"
#include "hash.h"
#include <string.h>
#include <stdbool.h>

void removeExtraSpaces(char *inputString);

/*char buffer[256];*/
/*int idx = 0;*/
/*char *str;*/
int currentLine = 1;
int running = 1;
%}

%x MULTILINE_COMMENT
%x IDENTIFIER

KEYWORD byte|short|long|float|double|if|then|else|while|for|read|return|print

%%

<INITIAL>{
    [0-9]+ {
        setHashNode(yytext, LIT_INTEGER);
        return LIT_INTEGER;
    }

    [0-9]+"."[0-9]+ {
        setHashNode(yytext, LIT_REAL);
        return LIT_REAL;
    }

    /*[0-9]+"."[0-9]+(f|F) {*/
        /*setHashNode(yytext, LIT_REAL);*/
        /*return LIT_REAL;*/
    /*}*/

    '([^\\]|\\.)' {
        setHashNode(yytext, LIT_CHAR);
        return LIT_CHAR;
    }

    \"(\\.|[^"])*\" {
        setHashNode(yytext, LIT_STRING);
        return LIT_STRING;
    }

    [\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=\!\&\$\#] {
        return yytext[0];
    }

    "<=" { return OPERATOR_LE; }
    ">=" { return OPERATOR_GE; }
    "==" { return OPERATOR_EQ; }
    "!=" { return OPERATOR_NE; }
    "&&" { return OPERATOR_AND; }
    "||" { return OPERATOR_OR; }

    byte { return KW_BYTE; }
    short { return KW_SHORT; }
    long { return KW_LONG; }
    float { return KW_FLOAT; }
    double { return KW_DOUBLE; }
    if { return KW_IF; }
    then { return KW_THEN; }
    else { return KW_ELSE; }
    while { return KW_WHILE; }
    for { return KW_FOR; }
    read { return KW_READ; }
    return { return KW_RETURN; }
    print { return KW_PRINT; }

    [a-zA-Z_]([a-zA-Z_0-9 \t]*[a-zA-Z0-9])? {
        removeExtraSpaces(yytext);
        setHashNode(yytext, TK_IDENTIFIER);
        return TK_IDENTIFIER;
    }

    /*
       Originalmente estávamos usando o código que identificava a primeira
       letra do nome do identificador e mudava o estado para poder ler diversas
       palavras separadas com espaços.

       Isso era necessário para poder escrever coisas como:

               long var 1;

       Onde o começo da linha seria identificado como palavra-chave, e o resto
       como identificador.

       Devido ao email enviado esclarecendo que a linha acima deveria ser
       entendida como um identificador, resolvemos atualizar o código e não
       usar outro estado para os identificadores.

       As linhas comentadas abaixo eram as responsáveis pelo comportamento
       original.
     */

    /*[a-zA-Z_]+ {*/
        /*// Coloca a palavra de volta e muda de estado.*/
        /*yyless(0);*/
        /*BEGIN(IDENTIFIER);*/
    /*}*/
}

    /*<IDENTIFIER>{*/
        /*[a-zA-Z_]+([a-zA-Z_0-9 \t]*[a-zA-Z0-9])? {*/
            /*setHashNode(yytext, TK_IDENTIFIER);*/
            /*return TK_IDENTIFIER;*/
        /*}*/
        /*. {*/
            /*yyless(0);*/
            /*BEGIN(INITIAL);*/
        /*}*/
    /*}*/

[ \t]+ {}
"//".* {}
"\n" { ++currentLine; }

<INITIAL>"/*" { BEGIN(MULTILINE_COMMENT); }

<MULTILINE_COMMENT>"*/" { BEGIN(INITIAL); }
<MULTILINE_COMMENT>. ;

<INITIAL>. {
    // Se chegar aqui, é um caractere não reconhecido.
    return TOKEN_ERROR;
}
%%

int yywrap();
int isRunning();
int getLineNumber();
void initMe();

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

void removeExtraSpaces(char *inputString) {
    size_t len = strlen(inputString);
    char *string = malloc(sizeof(char) * len);

    int i = 0;
    bool insertSpace = true;
    char *c = inputString;
    while (i < len && *c != '\0') {
        if (*c == ' ' || *c == '\t') {
            if (insertSpace) {
                string[i] = ' ';
                insertSpace = false;
            }
            else {
                --i;
            }
        }
        else {
            insertSpace = true;
            string[i] = *c;
        }
        ++c;
        ++i;
    }
    string[i] = '\0';
    strcpy(inputString, string);
    free(string);
}
