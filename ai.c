#include "ai.h"
#include "board.h"

#include <stdlib.h>

#define INF (300000)

int count_pieces(bitboard b) {
  int i = 0;
  while (b &= b - 1) i++;
  return i;
}

int piece_count_score(Board *b) {
  return
    count_pieces(b->bitboards[b->turn]) -
    count_pieces(b->bitboards[b->turn ^ 1]);
}

/**
 * Score the board from the current player's perspective
 */
int eval(Board *b, Moveset *ms) {
  return piece_count_score(b) + (ms ? ms->count : 0);
}

int absearch(Board *b, int depth, int alpha, int beta, Moveset *ms) {
  int score;
  int i;
  ms = ms ? ms : getLegalMoves(b);

  if (ms->count == 0) {
      change_turn(b);
      ms = getLegalMoves(b);

      if(ms->count == 0) {
        // Game over
        score = piece_count_score(b);
        score = score > 0
          ? INF
          : score < 0
            ? -INF
            : 0;
      } else {
        score = -absearch(b, depth-1, alpha, beta, ms);
      }
      free(ms);
      return score;
  }

  for (i = 0;i < ms->count;i++) {
    if(beta < alpha) {
      // cutoffs++;
      // if(entry != null && entry.bestmove.equals(m)){
      //   hashBMCuts++;
      // }
      // if(isKiller(m, depth)){
      //   killerCuts++;
      // }
      return alpha;
    }
  }
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

    score = -absearch(b, depth, -INF, INF, NULL);

    if (score > bestScore) {
      bestScore = score;
      bestMove = mm.pos;
    }

    unmakemove(b, mm);
  }

  mm.pos = bestMove;
  makemove(b, mm);
}

