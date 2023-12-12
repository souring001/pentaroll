#include <stdio.h>

#define N 6
#define NEED_TO_WIN 5

void drawBoard(char board[N][N]) {
  for (int i = 0; i < N + 2; i++) {
    if (i == 0) {
      printf("  ");
      for (int j = 0; j < N; j++) {
        printf(" %2d", j+1);
      }
    } else if (i == N + 1) {
      printf("  ");
      for (int j = 0; j < N; j++) {
        printf(" %2d", 3*N-j);
      }
    } else {
      for (int j = 0; j < N + 2; j++) {
        if (j == 0) {
          printf("%2d|", 4*N-i+1);
        } else if (j == N + 1) {
          printf("%2d", i+N);
        } else {
          printf(" %c|", board[i-1][j-1]);
        }
      }
    }
    printf("\n");
  }
  printf("\n");
}

void initBoard(char board[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = '.';
    }
  }
}

int insert_line(char line[N], char val) {
  int hasSpace = 0;
  for (int i = 0; i < N; i++) {
    if (line[i] == '.') {
      hasSpace = 1;
    }
  }
  if (!hasSpace) {
    // 列が埋まっている
    return 1;
  }

  int firstSpaceIdx = 0;
  for (int i = 0; i < N; i++) {
    if (line[i] == '.') {
      firstSpaceIdx = i;
      break;
    }
  }
  for (int i = firstSpaceIdx; i > 0; i--) {
    line[i] = line[i-1];
  }
  line[0] = val;

  return 0;
}

int insert(char board[N][N], int num, char val) {
  char buf[N];
  
  // 上段(1~N)
  if (1 <= num && num <= N) {
    for (int i = 0; i < N; i++) {
      buf[i] = board[i][num-1];
    }
  }

  // 右段(N+1~2N)
  if (N+1 <= num && num <= 2*N) {
    for (int i = 0; i < N; i++) {
      buf[i] = board[num-(N+1)][N-1-i];
    }
  }

  // 下段(2N+1~3N)
  if (2*N+1 <= num && num <= 3*N) {
    for (int i = 0; i < N; i++) {
      buf[i] = board[N-1-i][N-1-(num-(2*N+1))];
    }
  }

  // 左段(3N+1~4N)
  if (3*N+1 <= num && num <= 4*N) {
    for (int i = 0; i < N; i++) {
      buf[i] = board[N-1-(num-(3*N+1))][i];
    }
  }

  if (insert_line(buf, val)) {
    printf("%dに%cを配置できません\n", num, val);
    return 1;
  }
  
  // 上段(0~N-1)
  if (1 <= num && num <= N) {
    for (int i = 0; i < N; i++) {
      board[i][num-1] = buf[i];
    }
  }

  // 右段(N~2N-1)
  if (N+1 <= num && num <= 2*N) {
    for (int i = 0; i < N; i++) {
      board[num-(N+1)][N-1-i] = buf[i];
    }
  }

  // 下段(2N+1~3N)
  if (2*N+1 <= num && num <= 3*N) {
    for (int i = 0; i < N; i++) {
      board[N-1-i][N-1-(num-(2*N+1))] = buf[i];
    }
  }

  // 左段(3N+1~4N)
  if (3*N+1 <= num && num <= 4*N) {
    for (int i = 0; i < N; i++) {
      board[N-1-(num-(3*N+1))][i] = buf[i];
    }
  }

  return 0;
}

int judge(char board[N][N]) {
  //横
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
      char ijColor = board[i][j];
      if(ijColor == '.') continue;
      char isWin = 1;
      for(int k = j + 1; k < j + NEED_TO_WIN; k++) {
        if(ijColor != board[i][k]) {
          isWin = 0;
          break;
        }
      }
      if(isWin) {
        printf("%cの勝利\n", ijColor);
        return 1;
      }
    }
  }
  //横
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
      char ijColor = board[j][i];
      if(ijColor == '.') continue;
      char isWin = 1;
      for(int k = j + 1; k < j + NEED_TO_WIN; k++) {
        if(ijColor != board[k][i]) {
          isWin = 0;
          break;
        }
      }
      if(isWin) {
        printf("%cの勝利\n", ijColor);
        return 1;
      }
    }

  }
  //左上から右下のななめ
  for(int i = 0; i < N - NEED_TO_WIN + 1; i++) {
    for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
      char ijColor = board[i][j];
      if(ijColor == '.') continue;
      char isWin = 1;
      for(int k = 0; k < NEED_TO_WIN; k++) {
        if(ijColor != board[i+k][j+k]) {
          isWin = 0;
          break;
        }
      }
      if(isWin) {
        printf("%cの勝利\n", ijColor);
        return 1;
      }
    }
  }
  //左上から左下のななめ
  for(int i = 0; i < N - NEED_TO_WIN + 1; i++) {
    for(int j = NEED_TO_WIN - 1; j < N ; j++) {
      char ijColor = board[i][j];
      if(ijColor == '.') continue;
      char isWin = 1;
      for(int k = 0; k < NEED_TO_WIN; k++) {
        if(ijColor != board[i+k][j-k]) {
          isWin = 0;
          break;
        }
      }
      if(isWin) {
        printf("%cの勝利\n", ijColor);
        return 1;
      }
    }
  }
  return 0;
}

int test() {
  char board[N][N];

  initBoard(board);

  insert(board, 7, 'x');
  drawBoard(board);

  insert(board, 3, 'o');
  drawBoard(board);

  insert(board, 2, 'x');
  drawBoard(board);

  insert(board, 3, 'o');
  drawBoard(board);

  insert(board, 7, 'x');
  drawBoard(board);

  insert(board, 7, 'o');
  drawBoard(board);

  insert(board, 7, 'x');
  drawBoard(board);

  insert(board, 12, 'o');
  drawBoard(board);
  
  insert(board, 13, 'x');
  drawBoard(board);
  
  insert(board, 18, 'o');
  drawBoard(board);

  insert(board, 24, 'x');
  drawBoard(board);

  insert(board, 19, 'o');
  drawBoard(board);

  insert(board, 23, 'x');
  drawBoard(board);

  insert(board, 19, 'o');
  drawBoard(board);

  return 0;
}

int main() {
  char board[N][N];

  initBoard(board);
  drawBoard(board);

  char val = 'o';
  int num;
  char finished = 0;
  while (!finished) {
    printf("%c:", val);
    scanf("%d", &num);
    insert(board, num, val);
    drawBoard(board);
    finished = judge(board);

    val = (val == 'o' ? 'x' : 'o');
  }

  return 0;
}
