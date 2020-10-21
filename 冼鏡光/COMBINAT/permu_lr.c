#include <stdio.h>
#include <stdlib.h>
#include "permu_lr.h"

void  again(int  perm[], int L, int R)
{
     int  i = R;

     while (LOOP) {
          if (R - L + 1 > 2) {
               again(perm, L+1, R);
               DISPLAY(R);
          }
          if (i > L ) {
               SWAP(perm[L], perm[i]);
               REVERSE(L+1, R);
               DISPLAY(R);
               i--;
          }
          else
               break;
     }
}


void permut(int perm[], int n)
{
     int  i;

     for (i = 0; i < n; i++)
          perm[i] = i + 1;
     again(perm, 0, n-1);
}


void permu_lr(void)
{
     int   perm[MAXSIZE];
     char  line[100];
     int   n;

     gets(line);
     n = atoi(line);
     permut(perm, n);
}
