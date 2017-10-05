etapa2: y.tab.o lex.yy.o hash.o main.o
	gcc y.tab.o lex.yy.o hash.o main.o -o etapa2

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

hash.o: hash.c
	gcc -c hash.c

main.o: main.c
	gcc -c main.c

clean:
	rm etapa2 lex.yy.c lex.yy.h y.tab.c y.tab.h *.o
