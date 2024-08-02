OBJS = board.o main.o

all : $(OBJS)
	$(CC) $(OBJS) -o main

board.o : board.h board.c
main.o : main.c

clean: 
	rm -fr main ${OBJS}