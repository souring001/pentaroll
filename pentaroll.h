#include<stdbool.h>

#define N 6
#define NEED_TO_WIN 5



typedef struct ban {
    long white;
    long black;
} Ban;

extern Ban *ban;
extern int count;
extern bool finished;
extern bool isWhiteTurn;
extern long rowFull;
extern long colFull;
extern long rowMask;
extern long colMask;
extern long leftDigMask;
extern long rightDigMask;

/** pentaroll.c */
extern char *ban2board(Ban *ban);
extern void initWinMask(void);
extern void initFullMask(void);
extern char maskBits(long bin, long mask);
extern void invMaskBits(long *bin, long mask, char buf);

/** io.c */ 
extern void initBan(void);
extern void drawBan(Ban *ban);
extern bool usrInsert(Ban *ban, bool isWhiteTurn);
extern void printBin(long bin);

/** test.c */
extern void initTest(void);

/** move.c */
extern bool checkInsert(Ban *ban, int num);
extern void insert(Ban *ban, int num, bool isWhiteTurn);
extern void insertAbove(Ban *ban, long mask, bool isWhiteTurn);

/** tree.c */
typedef struct node {
	Ban ban;
	struct node *branch;
	struct node *next;
} Node;
