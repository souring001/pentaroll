#include<stdlib.h>
#include "pentaroll.h"

Ban *ban;


void initTest(void) {
    initBan();
    ban->white = 0b11000001000010;
    ban->black = 0b1000000000010000001;
}
