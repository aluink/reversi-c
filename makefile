OBJS = board.o

board.o : board.h board.c

main : board.o
	$(CC) $(OBJS) main.c -o main

all : main
