#include<stdlib.h>
#include "pentaroll.h"

Ban *ban;


void initTest(void) {
    initBan();
    ban->white = 0b10000001000010000011001011;
    ban->black = 0b1000000100010000001000100100100;
}
