#include <stdio.h>

#include "board.h"
#include "strings.h"

int main() {
   Board *b = newGame();
   int moves[60];

   int count = getLegalMoves(b, moves);

   printBoard(b);

   printMoves(count, moves);

   return 0;
}
