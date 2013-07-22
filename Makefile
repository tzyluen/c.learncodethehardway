CFLAGS=-Wall -g
all: ex1 ex3

ex1:
	gcc ex1.c
ex3:
	gcc ex3.c
clean:
	rm -f ex1 ex3 a.out
