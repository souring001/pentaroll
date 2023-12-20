#include<stdlib.h>
#include "pentaroll.h"

long rowFull;
long colFull;
long rowMask;
long colMask;
long leftDigMask;
long rightDigMask;



bool checkInsert(Ban *ban, int num) {
    bool allowInsert = false;
    long result;
    long all = ban->white | ban->black;

    if (1 <= num && num <= N) {
        /** check a column space */
        result = (all >> (num-1)) & colFull;
        if (result==colFull) return false;
    } else if (2*N+1 <= num && num <= 3*N) {
        /** check a column space */
        result = (all >> (3*N-num)) & colFull;
        if (result==colFull) return false;
    } else if (N+1 <= num && num <= 2*N) {
        /** check a row space */
        result = (all >> (num-1-N)) & rowFull;
        if (result==rowFull) return false;
    } else if (3*N+1 <= num && num <= 4*N) {
        /** check a row space */
        result = (all >> (4*N-num)) & rowFull;
        if (result==rowFull) return false;
    } else {
        /** invalid user input */
        return false;
    }
    return true;
}


void insert(Ban *ban, int num, bool isWhiteTurn) {
    long mask = 0;
    if (1 <= num && num <= N) {
        /** insertion from above */
        for (int i = 0; i < N; i++) mask = (mask << N) | (0x1 << (num-1));
        insertAbove(ban, mask, isWhiteTurn);
    } else if (2*N+1 <= num && num <= 3*N) {
        /** insertion from bottom */
        for (int i = 0; i < N; i++) mask = (mask << N) | (0x1 << (3*N-num));
    }
}


void insertAbove(Ban *ban, long mask, bool isWhiteTurn) {
    char white_buf = maskBits(ban->white, mask);
    char black_buf = maskBits(ban->black, mask);

    char white_res = 0;
    char black_res = 0;
    char pre_white = 0;
    char pre_black = 0;

    for (int i = 0; i < N; i++) {
        if (white_buf & (1 << i)) {
            if (~pre_white & ~pre_black) {
                white_res |= (1 << (i-1));
            } else {
                white_res |= (1 << i);
                pre_white = 1;
            }
        } else if (black_buf & (1 << i)) {
            if (~pre_white & ~pre_black) {
                black_res |= (1 << (i-1));
            } else {
                black_res |= (1 << i);
                pre_black = 1;
            }
        } else {
            pre_white = 0;
            pre_black = 0;
        }
    }

    if (isWhiteTurn) white_res |= 0b100000;
    else black_res |= 0b100000;
    invMaskBits(&ban->white, mask, white_res);
    invMaskBits(&ban->black, mask, black_res);
}
