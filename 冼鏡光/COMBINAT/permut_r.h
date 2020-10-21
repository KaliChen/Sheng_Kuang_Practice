#ifndef _PERMUT_R_H_
#define _PERMUT_R_H_

#define   MAXSIZE   20
#define   ROTATE(p) {  int  i, temp;              \
                       temp = perm[p];            \
                       for (i = p-1; i >= 0; i--) \
                            perm[i+1] = perm[i];  \
                       perm[0] = temp;            \
                    }
void permut_r();
#endif
