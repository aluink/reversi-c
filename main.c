#include <stdio.h>

#include "board.h"
#include "strings.h"

int main() {
   Board *b = newGame();
   int moves[60];

   int count = getLegalMoves(b, moves);

   printf("%d\n", count);

   return 0;
}
