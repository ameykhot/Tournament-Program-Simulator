CC=gcc

all : run checkmem clean
compile:
	$(CC) -c tournament.c -o tournament.o
	$(CC) -c program4.c -o program4.o
	$(CC) program4.o tournament.o -o program4
run:compile
	./program4
clean:clean
	rm *.o program4	

