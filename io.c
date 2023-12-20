#include<stdio.h>
#include<stdlib.h>
#include "pentaroll.h"

Ban *ban;
int count;
bool finished;
bool isWhiteTurn;



void initBan(void) {
    /** intialize ban */
    ban = (Ban *)malloc(sizeof(Ban));
    if (ban == NULL) exit(EXIT_FAILURE);
    ban->white = (long)0;
    ban->black = (long)0;
    /** initialize other params */
    count = 1;
    finished = false;
    isWhiteTurn = true;
    initWinMask();
    initFullMask();
}


void drawBan(Ban *ban) {
    // system("clear");
    char *board = ban2board(ban);
    for (int i = 0; i < N+2; i++) {
        if (i == 0) {
            printf(" ");
            for (int j = 0; j < N; j++) printf(" %2d", j+1);
        } else if (i == N + 1) {
            printf("  ");
            for (int j = 0; j < N; j++) printf(" %2d", 3*N-j);
        } else {
            for (int j = 0; j < N + 2; j++) {
                if (j == 0) printf("%2d|", 4*N-i+1);
                else if (j == N + 1) printf("%2d", i+N);
                else printf(" %c|", board[j-1+N*(i-1)]);
            }
        }
        printf("\n");
    }
    free(board);
}


bool usrInsert(Ban *ban, bool isWhiteTurn) {
    int num;
    bool allowInsert = false;
    while (!allowInsert) {
        /** Receive input from user(human) and check for possible placement. */
        printf("入力して下さい。\n>> ");
        scanf("%d", &num);
        allowInsert = checkInsert(ban, num);
        if (!allowInsert) {
            printf("%dに%cを配置できません。\nもう一度", num, (isWhiteTurn ? 'o':'x'));
            continue;
        }
        /** Make changes to ban if available for placement. */
        insert(ban, num, isWhiteTurn);
    }
    return (isWhiteTurn ? false : true);
}


void printBin(long bin) {
    int bits = sizeof(long)*8;
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (bin >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}
