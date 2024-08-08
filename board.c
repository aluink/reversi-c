#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "board.h"

#define BOARD_COLOR "\033[0;97m"
#define BLACK_COLOR "\033[0;32m"
#define RED_COLOR "\033[0;31m"
#define YELLOW_COLOR "\033[0;34m"
#define NORMAL_COLOR "\033[0m"


bitboard ADJACENCY_MASKS[64] = {
  0x302,
  0x705,
  0xE0A,
  0x1C14,
  0x3828,
  0x7050,
  0xE0A0,
  0xC040,
  0x30203,
  0x70507,
  0xE0A0E,
  0x1C141C,
  0x382838,
  0x705070,
  0xE0A0E0,
  0xC040C0,
  0x3020300,
  0x7050700,
  0xE0A0E00,
  0x1C141C00,
  0x38283800,
  0x70507000,
  0xE0A0E000,
  0xC040C000,
  0x302030000,
  0x705070000,
  0xE0A0E0000,
  0x1C141C0000,
  0x3828380000,
  0x7050700000,
  0xE0A0E00000,
  0xC040C00000,
  0x30203000000,
  0x70507000000,
  0xE0A0E000000,
  0x1C141C000000,
  0x382838000000,
  0x705070000000,
  0xE0A0E0000000,
  0xC040C0000000,
  0x3020300000000,
  0x7050700000000,
  0xE0A0E00000000,
  0x1C141C00000000,
  0x38283800000000,
  0x70507000000000,
  0xE0A0E000000000,
  0xC040C000000000,
  0x302030000000000,
  0x705070000000000,
  0xE0A0E0000000000,
  0x1C141C0000000000,
  0x3828380000000000,
  0x7050700000000000,
  0xE0A0E00000000000,
  0xC040C00000000000,
  0x203000000000000,
  0x507000000000000,
  0xA0E000000000000,
  0x141C000000000000,
  0x2838000000000000,
  0x5070000000000000,
  0xA0E0000000000000,
  0x40C0000000000000,
};

// #define UP (8)
// #define DOWN (-8)
// #define LEFT (-1)
// #define RIGHT (1)
// #define UP_LEFT (UP + LEFT)
// #define UP_RIGHT (UP + RIGHT)
// #define DOWN_RIGHT (DOWN + RIGHT)
// #define DOWN_LEFT (DOWN + LEFT)

/**
 * Converts a board position index to a string
 * coordinate. The returned string memory must be freed
 */
char* posToCoords(int pos) {
  char col = pos % 8 + 'A';
  int row = pos / 8 + 1;
  // return (char)(1 + 'A');
  char *str = malloc(3);
  sprintf(str, "%c%d", col, row);
  return str;
}

void printBitboard(bitboard board) {
  for (int row = 7;row >= 0;row--) {
    for (int col = 0;col < 8;col++) {
      printf("%d", (int)(board >> (row*8+col) & 1));
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
      mask |= 1UL << (pos - 8);

      // DOWN-LEFT
      if (LEFT) mask |= 1UL << (pos - 9);

      // DOWN-RIGHT
      if (RIGHT) mask |= 1UL << (pos - 7);
    }

    if (UP) { // UP
      mask |= 1UL << (pos + 8);

      // UP-LEFT
      if (LEFT) mask |= 1UL << (pos + 7);

      // UP-RIGHT
      if (RIGHT) mask |= 1UL << (pos + 9);
    }

    // LEFT
    if (LEFT) mask |= 1UL << (pos - 1);

    // RIGHT
    if (RIGHT) mask |= 1UL << (pos + 1);

    printf("0x%llX,\n", mask);
  }
}

Board* newGame() {
  Board * b = malloc(sizeof(Board));
  b->turn = 0;
  b->bitboards[0] = 0x0000001008000000UL;
  b->bitboards[1] = 0x0000000810000000UL;
  
  return b;
}

Board* newGameSet(short turn, bitboard yellow, bitboard red) {
  Board * b = malloc(sizeof(Board));
  b->turn = turn;
  b->bitboards[0] = yellow;
  b->bitboards[1] = red;

  printBitboard(b->bitboards[0]);
  printBitboard(b->bitboards[1]);
  
  return b;
}


bitboard can_move_direction(Board *b, int col, int row, int cdir, int rdir) {
  int other_count = 0;
  bitboard mask = 0;
  for (
    col += cdir, row += rdir;
    row >= 0 && row < 8 && col >= 0 && col < 8;
    col += cdir, row += rdir) {
    if (b->bitboards[b->turn ^ 1] >> (row*8+col) & 1) {
      mask |= 1ULL << (row*8+col);
      continue;
    } if (b->bitboards[b->turn] >> (row*8+col) & 1) {
      return mask;
    } else {
      return 0;
    }
  }

  return 0;
}


Moveset* getLegalMoves(Board* b) {
  int movecount = 0;
  bitboard currentPlayerBoard = b->bitboards[b->turn];
  bitboard otherPlayerBoard = b->bitboards[b->turn ^ 1];
  bitboard allBoard = currentPlayerBoard | otherPlayerBoard;

  bitboard tmp = otherPlayerBoard;
  int k[3] = { -1, -1, -1 };
  int moveCheck[64] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1
  };
  bitboard posMask;
  Moveset* moveset = malloc(sizeof(Moveset));
  moveset->count = 0;
  while (tmp > 0) {
    int idx = ffsll(tmp) - 1;
    int col = idx % 8;
    int row = idx / 8;
    bitboard move_options = ADJACENCY_MASKS[idx] & ~allBoard;
    while (move_options > 0) {
      int move_option_idx = ffsll(move_options) - 1;
      int mo_col = move_option_idx % 8;
      int mo_row = move_option_idx / 8;

      if ((posMask = can_move_direction(b, mo_col, mo_row, col - mo_col, row - mo_row))) {
        if (moveCheck[move_option_idx] > -1) {
          moveset->movemasks[moveCheck[move_option_idx]] |= posMask;
        } else {
          moveCheck[move_option_idx] = move_option_idx;
          moveset->moves[moveset->count] = move_option_idx;
          moveset->movemasks[move_option_idx] = posMask | (1ULL << move_option_idx);
          moveset->count++;
        }
        
      }

      move_options &= move_options - 1;
    }

    tmp &= tmp - 1;
  }

  return moveset;
}

void printMoves(Moveset* moveset) {
  for (int i = 0;i < moveset->count;i++) {
    printf("%c%d\n", moveset->moves[i] % 8 + 'A', moveset->moves[i] / 8 + 1);
    // printBitboard(moveset->movemasks[moveset->moves[i]]);
    // printf("\n");
  }
}

Piece getPos(Board * b, int col, int row) {
  int pos = row*8+col;
  if ((b->bitboards[0] >> pos & 1UL) > 0) return YELLOW;
  if ((b->bitboards[1] >> pos & 1UL) > 0) return RED;
  return EMPTY;
}



void printBoard(Board * b, Moveset* ghostMoves) {
  printf("%s", BOARD_COLOR);
  printf("   +---+---+---+---+---+---+---+---+\n");
  for (int row = 7;row >= 0;row--) {
    printf(" %d ", row+1);
    for (int col = 0;col < 8;col++) {
      Piece piece = getPos(b, col, row);
      char c = piece == EMPTY ? ' ' : 'O';
      const char* color = piece == RED
        ? RED_COLOR
        : piece == YELLOW
          ? YELLOW_COLOR
          : BLACK_COLOR;
        
      if (ghostMoves && ghostMoves->movemasks[row*8+col]) {
        c = 'X';
      }
      printf("+ %s%c%s ", color, c, BOARD_COLOR);
    }
    printf("+\n");
    printf("   +---+---+---+---+---+---+---+---+\n");
  }
  printf("     A   B   C   D   E   F   G   H\n");
  printf("%s%s%s to move.\n",
    b->turn == 0 ? YELLOW_COLOR : RED_COLOR,
    b->turn == 0 ? "Yellow" : "Red",
    NORMAL_COLOR
  );
}

void change_turn(Board *b) {
  b->turn ^= 1;
}

void makemove(Board * b, Mademove mm) {
  b->bitboards[b->turn] |= mm.moves->movemasks[mm.pos];
  change_turn(b);
  b->bitboards[b->turn] &= ~mm.moves->movemasks[mm.pos];
}

void unmakemove(Board *b, Mademove mm) {
  b->bitboards[b->turn] |= mm.moves->movemasks[mm.pos] & ~(1ULL << mm.pos);
  change_turn(b);
  b->bitboards[b->turn] &= ~mm.moves->movemasks[mm.pos];
}
