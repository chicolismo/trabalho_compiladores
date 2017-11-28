etapa4: y.tab.o lex.yy.o semantic.o hash.o astree.o main.o
	gcc y.tab.o lex.yy.o semantic.o hash.o astree.o main.o -o etapa4

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

semantic.o: semantic.c
	gcc -c semantic.c

hash.o: hash.c
	gcc -c hash.c

astree.o: astree.c
	gcc -c astree.c

main.o: main.c
	gcc -c main.c

clean:
	#rm etapa4 lex.yy.c lex.yy.h y.tab.c y.tab.h *.o *~
	rm etapa4 lex.yy.c lex.yy.h y.tab.c y.tab.h *.o
