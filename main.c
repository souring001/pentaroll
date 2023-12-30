#include <stdio.h>
#include <stdlib.h>
#include "pentaroll.h"
#define GAME_COUNT 100

int count;
bool isWhiteTurn;
int finished;
int whiteWin = 0;
int blackWin = 0;


int main(void) {
  initMasks();
  for(int i = 0; i < GAME_COUNT; i++) {
    Ban *ban = initBan();
    isWhiteTurn = 1;
    while (!finished) {
      isWhiteTurn = isWhiteTurn ? shallowAIInsert(ban, isWhiteTurn) : abAIInsert(ban, isWhiteTurn);
      // drawBan(ban);
      finished = checkWin(ban);
      if(finished == 1) whiteWin ++;
      if(finished == 2) blackWin ++;
    }
    free(ban);
    freeMemo();
  }
  printf("結果(白先攻): 白の勝利%d回 黒の勝利%d回 引き分け%d回\n", whiteWin, blackWin, GAME_COUNT-whiteWin-blackWin);
  whiteWin = 0;
  blackWin = 0;
  for(int i = 0; i < GAME_COUNT; i++) {
    Ban *ban = initBan();
    isWhiteTurn = 0;
    while (!finished) {
      isWhiteTurn = isWhiteTurn ? shallowAIInsert(ban, isWhiteTurn) : abAIInsert(ban, isWhiteTurn);
      // drawBan(ban);
      finished = checkWin(ban);
      if(finished == 1) whiteWin ++;
      if(finished == 2) blackWin ++;
    }
    free(ban);
    freeMemo();
  }
  printf("結果(黒先攻): 白の勝利%d回 黒の勝利%d回 引き分け%d回\n", whiteWin, blackWin, GAME_COUNT-whiteWin-blackWin);
}
