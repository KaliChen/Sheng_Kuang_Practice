#ifndef _PERMU_LR_H_
#define _PERMU_LR_H_

#define  LOOP         1
#define  MAXSIZE   20
#define  SWAP(a,b)    { int t; t = a; a = b; b = t; }
#define  REVERSE(a,b) { int i, j;                            \
                        for (i=(a), j=(b); i < j; i++, j--)  \
                             SWAP(perm[i], perm[j]);         \
                      }
#define  DISPLAY(n)   { int i;                               \
                        printf("\n");                        \
                        for (i = 0; i < n; i++)              \
                             printf("%d ", perm[i]);         \
                      }
                        
void permu_lr();
#endif
