CC=gcc
CFLAGS=-Wall -g
all: ex1 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex14 ex14_e ex15 ex16 ex16_e ex17

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
ex9:
	$(CC) $(CFLAGS) ex9.c -o ex9
ex10:
	$(CC) $(CFLAGS) ex10.c -o ex10
ex11:
	$(CC) $(CFLAGS) ex11.c -o ex11
ex14:
	$(CC) $(CFLAGS) ex14.c -o ex14 
ex14_e:
	$(CC) $(CFLAGS) ex14_extended.c -o ex14_extended
ex16:
	$(CC) $(CFLAGS) ex16.c -o ex16
ex16_e:
	$(CC) $(CFLAGS) ex16_extended.c -o ex16_extended
ex17:
	$(CC) $(CFLAGS) ex17.c -o ex17
clean:
	rm -f ex1 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 ex11 ex14 ex14_extended ex15 ex16
	rm -f ex16_extended ex17
	rm -fr *.dSYM
	rm -fr *.out
	rm -f vgcore*
	rm -f core*
	rm -f my.db
