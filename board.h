
typedef unsigned long long bitboard;

typedef enum {
  BLACK = -1,
  EMPTY = 0,
  WHITE = 1
} Piece;

typedef struct {
  bitboard bitboards[2];
  short turn;
} Board;

void generateNeighborMasks();
Board* newGame();
void printBoard(Board * b);