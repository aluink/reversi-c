OBJS = ai.o board.o main.o

all : $(OBJS)
	$(CC) $(OBJS) -o main

ai.o : ai.c ai.h
board.o : board.h board.c
main.o : main.c

clean: 
	rm -fr main ${OBJS}