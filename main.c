#include "pentaroll.h"

Ban *ban;
int count;
bool isWhiteTurn;



int main(void) {
  initBan();
  // initTest();

  while (!finished) {
    isWhiteTurn = isWhiteTurn ? weakAIInsert(ban, isWhiteTurn) : usrInsert(ban, isWhiteTurn);
    drawBan(ban);
    finished = checkWin(ban);
  }
}
