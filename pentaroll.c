#include<stdlib.h>
#include "pentaroll.h"

long rowFull;
long colFull;
long rowMask;
long colMask;
long leftDigMask;
long rightDigMask;



char *ban2board(Ban *ban) {
    char *board = (char *)malloc(N*N*sizeof(char));;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(((long)1 << (j+N*i)) & ban->white) board[j+N*i] = 'o';
            else if(((long)1 << (j+i*N)) & ban->black) board[j+N*i] = 'x';
            else board[j+N*i] = '.';
        }
    }
    return board;
}


void initWinMask(void) {
    rowMask = 1;
    colMask = 1;
    leftDigMask = 1;
    rightDigMask = 0b10000;
    for (int i = 0; i < NEED_TO_WIN-1; i++) rowMask = (rowMask << 1) | 1;
    for (int i = 0; i < NEED_TO_WIN-1; i++) colMask = (colMask << N) | 1;
    for (int i = 0; i < NEED_TO_WIN-1; i++) leftDigMask = (leftDigMask << (N+1)) | 1;
    for (int i = 0; i < NEED_TO_WIN-1; i++) rightDigMask = (rightDigMask << (N-1)) | (1 << 4);
}


void initFullMask(void) {
    rowFull = 1;
    colFull = 1;
    for (int i = 0; i < N-1; i++) rowFull = (rowFull << 1) | 1;
    for (int i = 0; i < N-1; i++) colFull = (colFull << N) | 1;
}


char maskBits(long bin, long mask) {
    char result = 0;
    for (int i = 0; i < N*N; i++) {
        if ((mask >> i) & 1) {
            result = result << 1;
            result |= (bin >> i) & 1;
        }
    }
    return result;
}


void invMaskBits(long *bin, long mask, char buf) {
    *bin &= ~mask;
    for (int i = 0; i < N*N; i++) {
        if ((mask >> i) & 1) {
            if (buf & 0x20) *bin |= ((long)1 << i);
            buf = buf << 1;
        }
    }
}


bool checkWinMask(long val, long mask) {
    return (val & mask) == mask;
}

bool checkWinPlayer(long val) {
    // 行
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
            if(checkWinMask(val, rowMask << (j + i*N))) return true;
        }
    }
    // 列
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
            if(checkWinMask(val, colMask << (i + j*N))) return true;
        }
    }
    // 斜め
    for(int i = 0; i < N - NEED_TO_WIN + 1; i++) {
        for(int j = 0; j < N - NEED_TO_WIN + 1; j++) {
            if(checkWinMask(val, rightDigMask << (i + j*N)) || checkWinMask(val, leftDigMask << (i + j*N))) return true;
        }
    }

    return false;
}

int checkWin(Ban *ban) {
    if((ban->white & ban->black) == 0b111111111111111111111111111111111111) {
        printf("引き分け!\n");
        return 3;
    }
    bool checkBlack = checkWinPlayer(ban->black);
    bool checkWhite = checkWinPlayer(ban->white);
    if(checkBlack && checkWhite) {
        printf("引き分け!\n");
        return 3;
    }
    if(checkBlack) {
        printf("黒の勝利!\n");
        return 2;
    }
    if(checkWhite) {
        printf("白の勝利!\n");
        return 1;
    }
    return 0;
}

Ban* copyBan(Ban *old) {
    Ban *new = malloc(sizeof(Ban));
    new->black = old->black;
    new->white = old->white;
    return new;
}
