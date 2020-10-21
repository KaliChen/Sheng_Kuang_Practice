#ifndef _GRAYCODE_H_
#define _GRAYCODE_H_

#define   MAXSIZE         20
#define   YES             1
#define   LOOP            1

#define   FLIP_DIGIT(x)   x = ((x) == '0' ? '1' : '0')
#define   FLIP(x)         x = (1 - (x))

void graycode();
#endif
