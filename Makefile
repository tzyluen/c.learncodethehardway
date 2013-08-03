CC=gcc
CFLAGS=-Wall -g
all: ex1 ex3 ex4 ex5 ex6 ex7 ex8 ex16

ex1:
	$(CC) $(CFLAGS) ex1.c -o ex1
ex3:
	$(CC) $(CFLAGS) ex3.c -o ex3
ex4:
	$(CC) $(CFLAGS) ex4.c -o ex4
ex5:
	$(CC) $(CFLAGS) ex5.c -o ex5
ex6:
	$(CC) $(CFLAGS) ex6.c -o ex6
ex7:
	$(CC) $(CFLAGS) ex7.c -o ex7
ex8:
	$(CC) $(CFLAGS) ex8.c -o ex8
ex16:
	$(CC) $(CFLAGS) ex16.c -o ex16
clean:
	rm -f ex1 ex3 ex4 ex5 ex6 ex7 ex8 ex16
