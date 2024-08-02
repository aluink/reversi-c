#include <stdio.h>
#include <stdlib.h>

#include "board.h"

char* posToCoords(int pos) {
  char col = pos % 8 + 'A';
  int row = pos / 8 + 1;
  // return (char)(1 + 'A');
  sprintf(malloc(3), "%c%d");
}

void printBitboard(bitboard board) {
  for (int row = 7;row >= 0;row--) {
    for (int col = 0;col < 8;col++) {
      printf("%d", (board >> (row*8+col) & 1));
    }
    printf("\n");
  }
  printf("\n");
}

void generateNeighborMasks() {
  for (int pos = 0;pos < 64;pos++) {
    bitboard mask = 0;
    int LEFT = pos % 8 > 0;
    int RIGHT = pos % 8 < 7;
    int UP = pos < 56;
    int DOWN = pos > 7;

    if (DOWN) { // DOWN
      mask |= 1UL << pos - 8;

      // DOWN-LEFT
      if (LEFT) mask |= 1UL << pos - 9;

      // DOWN-RIGHT
      if (RIGHT) mask |= 1UL << pos - 7;
    }

    if (UP) { // UP
      mask |= 1UL << pos + 8;

      // UP-LEFT
      if (LEFT) mask |= 1UL << pos + 7;

      // UP-RIGHT
      if (RIGHT) mask |= 1UL << pos + 9;
    }

    // LEFT
    if (LEFT) mask |= 1UL << pos - 1;

    // RIGHT
    if (RIGHT) mask |= 1UL << pos + 1;
    char * coords = posToCoords(pos);
    printf("%s\n", coords);
    free(coords);
    printBitboard(mask);
  }
}

// 


Board* newGame() {
  Board * b = malloc(sizeof(Board));
  b->turn = 0;
  b->bitboards[0] = 0x0000001008000000UL;
  b->bitboards[1] = 0x0000000810000000UL;
  
  return b;
}




void getLegalMoves(Board* b) {
  bitboard currentPlayerBoard = b->bitboards[b->turn];
  bitboard otherPlayerBoard = b->bitboards[b->turn ^ 1];

  bitboard tmp = currentPlayerBoard;
  while (tmp > 0) {
    
  }
}

// Piece getPos(Board * b, int pos) {
//   if ((b->bitboards[0] >> pos & 1UL) > 0) return BLACK;
//   if ((b->bitboards[1] >> pos & 1UL) > 0) return WHITE;
//   return EMPTY;
// }

Piece getPos(Board * b, int col, int row) {
  int pos = row*8+col;
  if ((b->bitboards[0] >> pos & 1UL) > 0) return BLACK;
  if ((b->bitboards[1] >> pos & 1UL) > 0) return WHITE;
  return EMPTY;
}


void printBoard(Board * b) {
  printf("   +---+---+---+---+---+---+---+---+\n");
  for (int row = 7;row >= 0;row--) {
    printf(" %d ", row);
    for (int col = 0;col < 8;col++) {
      Piece piece = getPos(b, col, row);
      char c = piece == WHITE
        ? 'X'
        : piece == BLACK
          ? 'O'
          : ' ';
      printf("+ %c ", c);
    }
    printf("+\n");
    printf("   +---+---+---+---+---+---+---+---+\n", row+1);
  }
  printf("     A   B   C   D   E   F   G   H\n");
}

// void makemove(Board * b, int pos) {
//   b->bitboards[b->turn] |= 1UL << pos;
//   b->turn ^= 1;
// }

void makemove(Board * b, int col, int row) {
  int pos = row*8+col;
  b->bitboards[b->turn] |= 1UL << pos;
  b->turn ^= 1;
}
