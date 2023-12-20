#include "pentaroll.h"

Ban *ban;
int count;
bool isWhiteTurn;



int main(void) {
  initBan();
  initTest();

  while (!finished) {
    drawBan(ban);
    isWhiteTurn = usrInsert(ban, isWhiteTurn);
    // isWhiteTurn = aiInsert(isWhiteTurn);
    // finished = true;
  }
}

// int judge(char board[N][N]) {
//   //横
//   for(int i = 0; i < N; i++) {
//     for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
//       char ijColor = board[i][j];
//       if(ijColor == '.') continue;
//       char isWin = 1;
//       for(int k = j + 1; k < j + NEED_TO_WIN; k++) {
//         if(ijColor != board[i][k]) {
//           isWin = 0;
//           break;
//         }
//       }
//       if(isWin) {
//         printf("%cの勝利\n", ijColor);
//         return 1;
//       }
//     }
//   }
//   //横
//   for(int i = 0; i < N; i++) {
//     for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
//       char ijColor = board[j][i];
//       if(ijColor == '.') continue;
//       char isWin = 1;
//       for(int k = j + 1; k < j + NEED_TO_WIN; k++) {
//         if(ijColor != board[k][i]) {
//           isWin = 0;
//           break;
//         }
//       }
//       if(isWin) {
//         printf("%cの勝利\n", ijColor);
//         return 1;
//       }
//     }

//   }
//   //左上から右下のななめ
//   for(int i = 0; i < N - NEED_TO_WIN + 1; i++) {
//     for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
//       char ijColor = board[i][j];
//       if(ijColor == '.') continue;
//       char isWin = 1;
//       for(int k = 0; k < NEED_TO_WIN; k++) {
//         if(ijColor != board[i+k][j+k]) {
//           isWin = 0;
//           break;
//         }
//       }
//       if(isWin) {
//         printf("%cの勝利\n", ijColor);
//         return 1;
//       }
//     }
//   }
//   //左上から左下のななめ
//   for(int i = 0; i < N - NEED_TO_WIN + 1; i++) {
//     for(int j = NEED_TO_WIN - 1; j < N ; j++) {
//       char ijColor = board[i][j];
//       if(ijColor == '.') continue;
//       char isWin = 1;
//       for(int k = 0; k < NEED_TO_WIN; k++) {
//         if(ijColor != board[i+k][j-k]) {
//           isWin = 0;
//           break;
//         }
//       }
//       if(isWin) {
//         printf("%cの勝利\n", ijColor);
//         return 1;
//       }
//     }
//   }
//   return 0;
// }

// int main() {
//   char board[N][N];

//   initBoard(board);
//   drawBoard(board);

//   char val = 'o';
//   int num;
//   char finished = 0;
//   while (!finished) {
//     printf("%c:", val);
//     scanf("%d", &num);
//     insert(board, num, val);
//     long binary[2];
//     convertBoardToBinary(board, binary);
//     char board2[N][N];
//     convertBinaryToBoard(board2, binary);
//     drawBoard(board2);
//     finished = judge(board);

//     val = (val == 'o' ? 'x' : 'o');
//   }

//   return 0;
// }
