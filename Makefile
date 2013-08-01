CC=gcc
CFLAGS=-Wall -g
all: ex1 ex3 ex4 ex5 ex6

ex1:
	$(CC) $(CFLAGS) ex1.c
ex3:
	$(CC) $(CFLAGS) ex3.c
ex4:
	$(CC) $(CFLAGS) ex4.c
ex5:
	$(CC) $(CFLAGS) ex5.c
ex6:
	$(CC) $(CFLAGS) ex6.c -o ex6

clean:
	rm -f ex1 ex3 a.out ex4 ex6
