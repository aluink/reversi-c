
#ifndef __BOARD_H_
#define __BOARD_H_
#endif

typedef unsigned long long bitboard;

typedef enum {
  EMPTY = -1,
  YELLOW = 0,
  RED = 1
} Piece;

typedef struct {
  bitboard bitboards[2];
  short turn;
} Board;

typedef struct {
  char count;
  int moves[64];
  bitboard movemasks[64];
} Moveset;

typedef struct {
  Moveset* moves;
  int col;
  int row;
} Mademove;

// void generateNeighborMasks();
Board* newGame();
void printBoard(Board * b, Moveset* ghostMoves);
Moveset* getLegalMoves(Board* b);
void printMoves(Moveset* moves);
void unmakemove(Board *b, Mademove mm);
void makemove(Board * b, Mademove mm);
