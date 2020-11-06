.PHONY: all generate print errors run clean

all:generate print

errors:generate run

generate:
	lex uccompiler.l
	yacc -d uccompiler.y
	cc -o uccompiler y.tab.c lex.yy.c


print:
	./uccompiler -1 <test.txt 

run:
	./uccompiler <test.txt

clean:
	@echo "Cleaning up..."
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm uccompiler


