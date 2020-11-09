.PHONY: all generate meta1 printmeta1 lex lexerrors sint sinterrors tree treeprint clean

all:generate

meta1: generate printmeta1

lex:generate lexerrors

sint: generate sinterrors

tree: generate treeprint

generate:
	lex uccompiler.l
	yacc -d --verbose uccompiler.y
	cc -o uccompiler y.tab.c lex.yy.c


printmeta1:
	./uccompiler -1 <test.txt 

lexerrors:
	./uccompiler -e1 <test.txt

sinterrors:
	./uccompiler -e2 <test.txt
 
treeprint:
	./uccompiler -t <test.txt

clean:
	@echo "Cleaning up..."
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm uccompiler


