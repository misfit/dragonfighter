#include "common.h"

int TCBLALB[] = {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,
3,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,4,3,3,3,4,8,4,4,4,4,3,2,2,2,2,2,3,4,8,4,8,8,4,
8,4,3,2,2,2,2,2,3,4,3,2,3,4,4,4,4,4,4,3,2,2,2,2,2,3,4,4,4,4,4,4,4,4,3,2,2,2,2,
2,3,4,3,1,3,4,4,4,4,4,4,3,2,2,3,2,2,3,3,3,3,2,2,3,3,3,3,2,2,3,2,2,3,4,4,4,8,8,
4,4,4,4,4,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,4,8,8,8,4,4,4,4,4,4,3,2,
2,2,2,2,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,3,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,2,3,2,2,
2,2,2,2,2,2,3,3,3,11,3,3,3,3,3,2,3,3,3,4,4,4,4,3,2,2,2,3,2,3,14,2,2,2,2,2,3,2,
3,2,2,2,2,2,2,2,2,2,2,2,3,4,4,4,4,3,2,2,2,2,2,3,2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,
2,2,2,2,2,3,4,4,4,4,3,2,2,2,3,2,3,3,3,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,2,2,3,4,
4,4,4,3,3,3,3,3,2,3,8,8,2,2,2,2,8,8,3,2,2,3,2,2,3,2,2,3,2,2,3,4,4,4,4,3,2,2,2,
3,2,3,8,8,2,2,2,2,8,8,3,2,2,3,2,2,3,2,2,3,2,2,3,4,4,4,4,3,2,2,2,3,2,3,8,4,2,2,
2,2,4,8,3,2,2,2,2,2,2,2,2,2,2,2,3,4,4,4,4,3,10,2,2,11,2,3,4,4,2,2,2,2,4,4,3,2,
2,2,2,2,2,2,2,2,2,2,3,4,4,4,4,3,2,10,2,3,2,3,4,4,2,2,2,2,4,4,3,2,2,3,2,2,3,2,
2,3,2,2,3,4,4,4,4,3,10,2,10,3,2,3,4,2,2,2,2,2,2,4,3,2,2,3,2,2,3,2,2,3,2,2,3,4,
4,4,4,3,3,3,3,3,2,3,4,2,7,7,7,7,2,4,3,3,3,3,3,3,3,3,3,3,2,3,3,4,4,4,4,3,2,2,2,
2,2,2,2,2,7,6,6,7,2,2,2,2,2,2,2,2,3,2,2,2,2,2,3,4,4,4,4,3,2,2,2,2,2,2,2,2,7,6,
6,7,2,2,2,2,2,2,2,2,3,6,6,6,6,6,3,4,4,4,4,3,3,3,2,2,3,3,3,2,7,7,7,7,2,3,3,2,2,
2,2,2,3,6,6,6,6,6,3,4,4,4,4,3,2,2,2,2,2,2,3,2,2,2,2,2,2,3,2,2,2,2,2,2,3,2,2,2,
2,2,3,4,4,4,4,3,2,2,2,2,2,2,3,3,2,2,2,2,3,3,3,3,3,3,2,2,3,2,2,2,2,2,3,4,4,4,4,
3,2,2,3,2,2,2,2,3,2,2,2,2,3,2,2,2,2,2,2,2,3,3,3,3,3,3,3,7,4,4,4,3,2,2,2,2,2,2,
2,3,2,2,2,2,3,2,2,2,2,2,2,2,3,7,7,7,7,7,7,7,4,4,4,3,2,7,7,2,2,3,2,3,2,2,2,2,3,
2,2,3,3,3,3,3,3,7,7,7,7,7,7,7,4,4,4,3,7,7,7,7,2,2,2,3,2,2,2,2,3,2,2,3,2,2,3,2,
3,7,7,7,7,7,7,7,4,4,4,3,7,7,7,7,2,2,2,3,3,2,2,3,3,2,2,2,2,2,1,2,3,7,7,7,7,7,7,
7,4,4,4,3,7,7,7,7,7,2,2,3,2,2,2,2,3,2,2,3,2,2,3,2,3,7,7,7,7,7,7,7,4,4,4,3,3,3,
3,3,3,3,3,3,3,2,2,3,3,3,3,3,3,3,3,3,3,7,7,7,7,7,7,7,4,4,4,7,7,4,4,4,4,4,4,4,4,
2,2,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7,7,12,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
};
int TCBstartx = 288;
int TCBstarty = 256;
