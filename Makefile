CC = gcc
CFLAGS = -g -Wall -Wextra -Wno-unused -Werror -std=c99

default: 
    
addtest: addtest.c
	$(CC) $(CFLAGS) $^ -o addtest -lrt -pthread
    
sltest: sltest.c
	$(CC) $(CFLAGS) $^ -o sltest -lrt -pthread

dist: check
	mkdir lab1-laurenyeung
	cp *.sh *.c *.pdf *Makefile README* lab1-laurenyeung
	tar -cvf lab1-laurenyeung.tar.gz lab1-laurenyeung


	
