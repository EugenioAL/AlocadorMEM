CC = g++
CFLAGS = -Wall -g
 
all: main
 
main: main.o aloca.o
	$(CC) -o main main.o aloca.o
 
main.o: main.cpp aloca.h
	$(CC) -o main.o main.cpp -c -W -Wall -ansi -pedantic
 
aloca.o: aloca.cpp aloca.h
	$(CC) -o aloca.o aloca.cpp -c -W -Wall -ansi -pedantic

run:
	./main
 
clean:
	rm -rf *.o *~ main