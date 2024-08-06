#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "strings.h"

int main() {
  Board *b = newGame();
  char buffer[64];
  int col, row, i;
  Mademove history[64];
  int movecount = 0;

  int ENABLE_GHOST_MOVES = 1;

  for (i = 0; i < 64; i++) {
    history[i].moves = NULL;
  }

  while (1) {
    if (!history[movecount].moves) {
      history[movecount].moves = getLegalMoves(b);
    }
    printBoard(b, ENABLE_GHOST_MOVES ? history[movecount].moves : NULL);
    printMoves(history[movecount].moves);

   printf("mc: %d\n", movecount);
    printf("Enter a command or move: ");
    fgets(buffer, 64, stdin);

    if (!strncmp("quit", buffer, 4)) {
      while (movecount >= 0) {
        free(history[movecount--].moves);
      }
      break;
    }
    else if (!strncmp("ghost", buffer, 2)) {
      ENABLE_GHOST_MOVES ^= 1;
    }
    else if (!strncmp("undo", buffer, 2)) {
      free(history[movecount].moves);
      history[movecount--].moves = NULL;
      unmakemove(b, history[movecount]);
    }
    else {
      col = buffer[0] - (buffer[0] > 'Z' ? 'a' : 'A');
      row = buffer[1] - '1';
      if (history[movecount].moves->movemasks[row * 8 + col]) {
        history[movecount].col = col;
        history[movecount].row = row;
        makemove(b, history[movecount]);
        movecount++;
      }
      else {
        printf("ILLEGAL MOVE!\n");
      }
    }
  }

  printf("Exiting\n");

  return 0;
}
