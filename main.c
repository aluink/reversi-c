#include <stdio.h>

#include "board.h"

int main() {
   Board *b = newGame();
   printf("Hello World!\n");

   printBoard(b);

   return 0;
}
