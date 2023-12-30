#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pentaroll.h"

const int NN1 = N - NEED_TO_WIN + 1;
bool didInitTot = false;


typedef struct ScoreList {
    long white;
    long black;
    float score;
    struct ScoreList* next;
} ScoreList;
void freeNode(ScoreList* current);

ScoreList* memo[0x10000] ={NULL};

int hashBan(Ban* ban) {
  return ((ban->white) | 
    (ban->white >> 16) |
    (ban->white >> 32) |
    (ban->black) | 
    (ban->black >> 16) |
    (ban->black >> 32)) & 0xffff;
}

float flatScore(Ban* ban, bool forWhite) {
  int checkVal = checkWin(ban);
  if(checkVal == 3) return 0;
  if(checkVal == 2) return forWhite ? -1. : 1.;
  if(checkVal == 1) return forWhite ? 1. : -1.;

  int hash = hashBan(ban);
  ScoreList* current = memo[hash];
  while(current != NULL) {
    if(current->black == ban->black && current->white == ban->white) {
      return forWhite ? current->score : -current->score;
    }
    current = current->next;
  }

  int whiteCount = 0;
  int blackCount = 0;

  for(int i = 0; i < N; i++) {
    int w = __builtin_popcountl(ban->white & (rowFull << N * i));
    int b = __builtin_popcountl(ban->black & (rowFull << N * i));
    whiteCount += w * w;
    blackCount += b * b;
    w = __builtin_popcountl(ban->white & (colFull << i));
    b = __builtin_popcountl(ban->black & (colFull << i));
    whiteCount += w * w;
    blackCount += b * b;
  }
  for(int i = 0; i < NN1; i++) {
    for(int j = 0; j < NN1; j++) {
      int w = __builtin_popcountl(ban->white & (rightDigMask << (i*N + j)));
      int b = __builtin_popcountl(ban->black & (rightDigMask << (i*N + j)));
      whiteCount += w * w;
      blackCount += b * b;
      w = __builtin_popcountl(ban->white & (leftDigMask << (i*N + j)));
      b = __builtin_popcountl(ban->black & (leftDigMask << (i*N + j)));
      whiteCount += w * w;
      blackCount += b * b;
    }
  }
  float wScore = (float)whiteCount/(float)((2*N + NN1*NN1)*36) - (float)blackCount/(float)((2*N + NN1*NN1)*36);
  ScoreList* new = malloc(sizeof(ScoreList));
  new->black = ban->black;
  new->white = ban->white;
  new->score = wScore;
  new->next = memo[hash];
  memo[hash] = new;
  return forWhite ? wScore : -wScore;
}

bool scoreAIInsert(Ban *ban, bool isWhiteTurn, float (*func)(Ban *, bool)) {
  if(!didInitTot) {
    didInitTot = true;
    int seed = 1145141919;
    printf("Seed: %d\n", seed);
    srand(seed);
  }

  float maxScore = -2;
  int maxScoreVal = 0;
  int sameCount = 0;
  for(int i = 1; i < 24; i++) {
    Ban* kari = copyBan(ban);
    if(!checkInsert(kari, i)) {
      free(kari);
      continue;
    }
    insert(kari, i, isWhiteTurn);
    float s = func(kari, isWhiteTurn);
    if(maxScore < s) {
      maxScore = s;
      maxScoreVal = i;
      sameCount = 1;
    } else if(maxScore - s < 0.00001) {
      sameCount ++;
      if(rand() % sameCount == 0) {
        maxScoreVal = i;
      }
    }
    free(kari);
  }
  insert(ban, maxScoreVal, isWhiteTurn);
  return (isWhiteTurn ? false : true);

}


void freeMemo() {
  for(int i = 0; i < 0x10000; i++) {
    freeNode(memo[i]);
    memo[i] = NULL;
  }
}
void freeNode(ScoreList* current) {
  if(current == NULL) return;
  freeNode(current->next);
  fflush(stdout);
  free(current);
}

float alphaBeta(Ban *ban, int depth, float alpha, float beta, bool forWhite) {
  if(depth == 0) {
    float a = flatScore(ban, forWhite);
    printf("    %f\n", a);
    return a;
  }
  for(int j = 0; j < 2-depth; j++) printf("  ");
  printf("Begin:\n");
  for(int i = 1; i < 24; i++) {
    Ban* kari = copyBan(ban);
    if(!checkInsert(kari, i)) {
      free(kari);
      continue;
    }
    insert(kari, i, !forWhite);
    float current = -alphaBeta(kari, depth - 1, -beta, -alpha, !forWhite); 
    free(kari);
    if(alpha > current) alpha = current;
    if(alpha <= beta) {
      for(int j = 0; j < 2-depth; j++) printf("  ");
      printf("%f(枝刈り%d)\n", alpha, i);
      return alpha;
    }
  }
  for(int j = 0; j < 2-depth; j++) printf("  ");
  printf("%f\n", alpha);
  return alpha;
}

float alphaBetaScore(Ban* ban, bool forWhite) {
  return alphaBeta(ban, 2, 2, -2, forWhite);
}


bool shallowAIInsert(Ban *ban, bool isWhiteTurn) {
  return scoreAIInsert(ban, isWhiteTurn,  (float (*)(Ban *, bool))flatScore);
}

bool abAIInsert(Ban *ban, bool isWhiteTurn) {
  return scoreAIInsert(ban, isWhiteTurn,  (float (*)(Ban *, bool))alphaBetaScore);
}