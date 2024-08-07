#include "ai.h"
#include "board.h"

#define INF (300000)

int absearch(Board *b, int depth, int alpha, int beta) {
  
}

void makeAiMove(Board *b) {
  Moveset *moves = getLegalMoves(b);
  int depth = 3;
  int bestScore = -INF;
  int bestMove;
  int score;
  Mademove mm = { moves, -1 };

  for (int i = 0;i < moves->count;i++) {
    mm.pos = moves->moves[i];
    makemove(b, mm);

    score = -absearch(b, depth, -INF, INF);

    if (score > bestScore) {
      bestScore = score;
      bestMove = mm.pos;
    }

    unmakemove(b, mm);
  }

  mm.pos = bestMove;
  makemove(b, mm);
}

