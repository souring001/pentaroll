#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pentaroll.h"

bool didInit = false;

// 完全ランダム
bool veryweakAIInsert(Ban *ban, bool isWhiteTurn) {
  if(!didInit) {
    didInit = true;
    srand((unsigned int)time(NULL));
  }
  int num = rand() % 24;
  bool allowInsert = checkInsert(ban, num+1);
  while(!allowInsert) {
    int num = (num + 1) % 24;
    allowInsert = checkInsert(ban, num+1);
  }
  insert(ban, num, isWhiteTurn);
  return (isWhiteTurn ? false : true);
}


// 勝ち確定の場面だけ判定。それ以外はランダム
bool weakAIInsert(Ban *ban, bool isWhiteTurn) {
  if(!didInit) {
    didInit = true;
    srand((unsigned int)time(NULL));
  }

  for(int i = 1; i < 24; i++) {
    Ban* kari = copyBan(ban);
    if(!checkInsert(kari, i)) {
      free(kari);
      continue;
    }

    insert(kari, i, isWhiteTurn);
    int checkVal = checkWin(kari);
    if(isWhiteTurn && checkVal == 1) {
      insert(ban, i, isWhiteTurn);
      free(kari);
      return !isWhiteTurn;
    } else if(!isWhiteTurn && checkVal == 2) {
      insert(ban, i, isWhiteTurn);
      free(kari);
      return !isWhiteTurn;
    }
    free(kari);
  }

  int num = rand() % 24;
  bool allowInsert = checkInsert(ban, num+1);
  while(!allowInsert) {
    int num = (num + 1) % 24;
    allowInsert = checkInsert(ban, num+1);
  }
  insert(ban, num+1, isWhiteTurn);
  return (isWhiteTurn ? false : true);
}

