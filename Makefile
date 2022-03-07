CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o 
		$(CC) -o main main.cpp
 
# The main.o target can be written more simply

main.o: main.cpp
		$(CC) -c main.cpp


run:
		./main

clear:
		rm main