.PHONY: all generate print errors run clean

all:generate print

errors:generate run

generate:
	lex uccompiler.l
	clang -o uccompiler lex.yy.c

print:
	./uccompiler -1 <test.txt 

run:
	./uccompiler <test.txt

clean:
	@echo "Cleaning up..."
	rm uccompiler
	rm lex.yy.c

