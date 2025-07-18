# Authors: Jose Urrea, Abdihakim Ahmed
# Class Account Username: cssc1465, cssc1402
# Class Informartion: CS 480, Summer 2025
# Assignment Information : Programming Assignment #1
# File : MAKEFILE

all: bots

bots: main.o bots.o
	gcc -Wall -pthread -o bots main.o bots.o

main.o: main.c bots.h
	gcc -Wall -pthread -c main.c

bots.o: bots.c bots.h
	gcc -Wall -pthread -c bots.c

clean:
	rm -f main.o bots.o bots QUOTE.txt
