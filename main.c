#include <stdio.h>

#include "board.h"

int main() {
   Board *b = newGame();
   
   printBoard(b);

   return 0;
}
