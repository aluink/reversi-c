#include "ai.h"
#include "board.h"

#include <stdlib.h>
#include <sys/time.h>

#define INF (300000)
#define SEARCH_TIME (5000)

typedef unsigned long long millis;

millis start_time;
int timeup() {
  millis cur_time;
  struct timeval tv;

  gettimeofday(&tv, NULL);

  cur_time =
    (unsigned long long)(tv.tv_sec) * 1000 +
    (unsigned long long)(tv.tv_usec) / 1000;

  return (cur_time - start_time) > SEARCH_TIME;
}

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
  int best = -INF;
  int bestmove;
  int i;
  Mademove mm;
  Moveset *to_clear = NULL;

  ms = ms ? ms : (to_clear = getLegalMoves(b));

  if (ms->count == 0) {
      change_turn(b);
      ms = getLegalMoves(b);

      if(ms->count == 0) {
        // Game over
        best = eval(b, NULL);
        best = best > 0
          ? INF
          : best < 0
            ? -INF
            : 0;
      } else {
        best = absearch(b, depth-1, alpha, beta, ms);
      }
      free(ms);
  } if (!depth) {
    best = eval(b, ms);
  } else {
    mm.moves = ms;
    for (i = 0;i < ms->count;i++) {
      mm.pos = ms->moves[i];
      makemove(b, mm);
      score = -absearch(b, depth-1, -beta, -alpha, NULL);
      unmakemove(b, mm);

      if(timeup()) {
        best = -INF;
        break;
      }

      if(score > best){
        bestmove = i;
        alpha = best = score;
      }
      if(beta < alpha) {
        // cutoffs++;
        // if(entry != null && entry.bestmove.equals(m)){
        //   hashBMCuts++;
        // }
        // if(isKiller(m, depth)){
        //   killerCuts++;
        // }
        best = alpha;
        break;
      }
    }
  }

  if (to_clear) free(to_clear);

  return best;
}

void getBestMove(Board *b, Mademove *mm) {
  int depth = 3;
  int bestScore = -INF;
  int bestMove;
  int score;

  for (int i = 0;i < mm->moves->count;i++) {
    mm->pos = mm->moves->moves[i];
    makemove(b, *mm);
    score = -absearch(b, depth, -INF, INF, NULL);
    unmakemove(b, *mm);

    if (score > bestScore) {
      bestScore = score;
      bestMove = mm->pos;
    }

  }

  mm->pos = bestMove;
}

