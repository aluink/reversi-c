#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "strings.h"

int main() {
   Board *b = newGame();
   char buffer[64];
   int col, row;

   int ENABLE_GHOST_MOVES = 1;

   while(1) {
      Moveset* moves = getLegalMoves(b);
      printBoard(b, ENABLE_GHOST_MOVES ? moves : NULL);
      printMoves(moves);

      printf("Enter a command or move: ");
      fgets(buffer, 64, stdin);

      if (!strncmp("quit", buffer, 4)) {
         free(moves);
         break;
      } else if (!strncmp("ghost", buffer, 2)) {
         ENABLE_GHOST_MOVES ^= 1;
      } else {
         col = buffer[0] - (buffer[0] > 'Z' ? 'a' : 'A');
         row = buffer[1] - '1';
         if (moves->movemasks[row*8+col]) {
            makemove(b, moves, col, row);
         } else {
            printf("ILLEGAL MOVE!\n");
         }
      }

      free(moves);
   }

   printf("Exiting\n");


   return 0;
}
