#include <stdio.h>
#include  <stdlib.h>          /* for malloc()             */
#include  <math.h>            /* for abs()                */

#define  MAX(x, y)  ((x) >= (y) ? (x) : (y))
#define  MIN(x, y)  ((x) <= (y) ? (x) : (y))

#define  MAXSIZE  100
#define  QUEUE_SIZE   100     /* size of a queue          */
#define  SAVED          1
#define  DELETED       -1
#define  STACK_SIZE    100
#define  YES             1
#define  NO              0
#define     NO_SINK     -1
#define     MAXSIZE    100
#define  max(x, y)   ((x) >= (y) ? (x) : (y))
/* ------------------------------------------------------ */
/*(1)                                                     */
/* FUNCTION find_one_to_one :                             */
/*    This function accepts accepts a table representing  */
/* a function and then construct a one-to-one function    */
/* from the given function table.  funct[] is the given   */
/* function table representing a function from [0,n-1] to */
/* [0,n-1].  status[] is an output vector containing SAVED*/
/* or DELETED, where SAVED means the corresponding point  */
/* should be kept while DELETED indicates it has to be    */
/* deleted.  counter[] is a working array.                */
/*    This is a rather complicated program.  Read my book */
/* before try to study it please.                         */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/01/1989 */
/* ------------------------------------------------------ */



void find_one_to_one(int  funct[], int status[], int counter[], int n)
{
     int  queue[QUEUE_SIZE];  /* we need a queue          */
     int  head, tail;         /* queue pointers           */
     int  i, j;

     for (i = 0; i < n; i++) { /* initialization          */
          counter[i] = 0;     /* size of inverse-images   */
          status[i]  = SAVED; /* assume all are SAVED     */
     }

     for (i = 0; i < n; i++)  /* count inverse-image size */
          counter[funct[i]]++;

     for (tail = -1, i = 0; i < n; i++) /* put all i such */
          if (counter[i] == 0) /* that counter[i]=0 to Q  */
               queue[++tail] = i; 

     head = 0;                /* main loop. start from H  */
     while (head <= tail) {   /* if there have elements   */
          j = queue[head++];  /* get it and put it to j   */
          status[j] = DELETED;/* delete it. no inv-image  */
          if (--counter[funct[j]] == 0)
               queue[++tail] = funct[j];
     }
}

/* ------------------------------------------------------ */
/*(2)                                                     */
/* FUNCTION  pos_neg_balance :                            */
/*    Given an integer array x[], this function computes  */
/* the largest section of the array with equal number of  */
/* positive and negative numbers.                         */
/*                                                        */
/* Copyright Ching-Kuang Shene                Aug/10/1989 */
/* ------------------------------------------------------ */


int  pos_neg_balance(int x[], int n)
{
     int  length;             /* maximum length so far    */
     int  neg_over;           /* #of neg - #of pos        */
     int  min_over;           /* min of neg_over so far   */
     int  max_over;           /* max of neg_over so far   */
     int  mid;                /* the middle item of work  */
     int  i;
     int  *loc;               /* addr. of working array   */

     length   = neg_over = min_over = max_over = 0;
     loc      = (int *) malloc(sizeof(int)*(n+n));
     mid      = n;
     loc[mid] = 0;            /* #of neg=#of pos at start */
     for (i = 0; i < n; i++) {/* for each element in x[]..*/
          if (x[i] < 0)       /* if negative              */
               neg_over++;    /* #of neg increased        */
          else if (x[i] > 0)  /* or if positive           */
               neg_over--;    /* #of neg. decreased       */
          if (neg_over < min_over) {  /* update min.      */
               min_over = neg_over;
               loc[mid+min_over] = i + 1; /* and store it */
          }
          else if (neg_over > max_over) { /* update max.  */
               max_over = neg_over;
               loc[mid+max_over] = i + 1;
          }
          length = MAX(length, i+1-loc[mid+neg_over]);
     }
     free(loc);
     return length;
}
/* ------------------------------------------------------ */
/*(3)                                                     */
/* FUNCTION  diameter :                                   */
/*    Given the length of each side of a polygon, this    */
/* function determines its diameter.  The diameter of a   */
/* polygon is the line segment joining from i to j, i < j,*/
/* such that absolute difference of d[i]+d[i+1]+...+d[j]  */
/* and d[j]+...+d[n-1]+d[0]+...+d[i-1] is minimal.        */
/*                                                        */
/* Copyright Ching-Kuang Shene               Sept/01/1989 */
/* ------------------------------------------------------ */

void  diameter(int len[], int n, int *first, int *last)
{
     int  start, end;         /* [end,start] is the min   */
     int  lead, follow;       /* [follow,lead]-running min*/
     int  diff, abs_diff;     /* diff and absolute diff   */
     int  current_min;        /* current min - [end,start]*/
     int  i;

     for (i = diff = 0; i < n; diff -= len[i], i++)
          ;                    /* compute max. diff       */

     abs_diff = current_min = -diff; 
     for (lead = follow = start = end = 0; lead < n; ) {
          if (current_min >= abs_diff) {  /* update min   */
               current_min = abs_diff;
               start       = lead;
               end         = follow;
          }
          if (diff >= 0)      /* if diff > 0 ...          */
               diff -= 2*len[follow++]; /* too big, dec.  */
          else                /* if diff < 0 ...          */
               diff += 2*len[lead++];   /* too small, inc */
          abs_diff = abs(diff);  /* update absolute diff  */
     }
     *first = end;            /* return point number, NOT */
     *last  = start;          /* side number.             */
}

/* ------------------------------------------------------ */
/*(4)                                                     */
/* FUNCTION nearest_dominator :                           */
/*    Given an array, this function computes the right    */
/* nearest dominator of each element in the array.  A     */
/* right dominator of x[i] is any element x[j] with j > i */
/* and x[i] <= x[j].  The right nearest dominator is the  */
/* right dominator with smallest index.  You can define   */
/* the left nearest dominator in a similar way.           */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/01/1989 */
/* ------------------------------------------------------ */

void nearest_dominator(int x[], int dom[], int n)
{
     int  stack[STACK_SIZE];  /* the working stack        */
     int  top;                /* the stack pointer        */
     int  i;                  /* working variables        */

     for (i = 0; i < n; i++)  /* clear dominator array    */
          dom[i] = -1;        /* -1 means no dominator    */
     
     top        = 0;          /* stack initialization     */
     stack[top] = 0;
     for (i = 1; i < n; i++) { /* for each element :      */
          while (top >= 0 && x[stack[top]] <= x[i])
               dom[stack[top--]] = i;
          stack[++top] = i;   /* push i into stack        */
     }
}
/* ------------------------------------------------------ */
/*(5)                                                     */
/* FUNCTION  longest increasing subsequence :             */
/*    Given an integer sequence of length n, this function*/
/* determines the longest increasing subsequence in nlogn */
/* stpes with a dynamic programming technique.            */
/* ------------------------------------------------------ */
int longest_inc_sequence(int x[], int n)
{
     int  *last;              /* the last of a n-seubseq. */
     int  length;             /* current max inc. subseq. */
     int  left;               /* left bound for bin search*/
     int  right;              /* right bound              */
     int  mid;                /* the middle point.        */
     int  i;

     last = (int *) malloc(sizeof(int)*n); /* get work mem*/
     
     last[0] = x[0];          /* start from the beginning */
     length  = 0;             /* len=1 and x[0] in subseq */
     for (i = 1; i < n; i++)  /* scan all other items     */
          if (x[i] >= last[length]) /* higher than max?   */
               last[++length] = x[i]; /* YES, record it.  */
          else if (x[i] < last[0]) /* NO, less then 1st   */
               last[0] = x[i]; /* it would be the new head*/
          else {              /* now insert it with bin.sr*/
               for (left = 0, right = length; left != right-1; ) {
                    mid = (left + right) / 2;
                    (last[mid] <= x[i]) ? (left = mid) : (right = mid);
               }
               last[right] = x[i];
          }
     free(last);              /* finally release memory   */
     return length + 1;       /* return the true length   */
}

/* ------------------------------------------------------ */
/*(6)                                                     */
/* FUNCTION  maxcover :                                   */
/*    Given an integer, this function computes the max.   */
/* cover interval length of the array.  A cover interval  */
/* of an element of the array, say x[i], is an interval   */
/* [j,i], j <= i, such that for all k, j<=k<=i, we have   */
/* x[k] <= abs(x[i]).  A maximal cover interval is an     */
/* interval with maximum length.                          */
/*                                                        */
/* Copyright Ching-Kuang Shene                Aug/11/1989 */
/* ------------------------------------------------------ */
int  maxcover(int x[], int n)
{
     int  length;             /* max. interval length     */
     int  bound;              /* last element searched    */
     int  i;

     length = 1;              /* min. length is one       */
     bound  = n - 1;          /* start from n-1 th item   */
     for (i = n - 2; i >= 0; i--) { /* for each item...   */
          for ( ; x[i] > abs(x[bound]); bound--) /* bound?*/
               ;              /* now x[i] <= x[bound] ... */
          length = MAX(length, bound-i+1); /* update len. */
     }
     return length;
}

/* ------------------------------------------------------ */
/*(7)                                                     */
/* FUNCTION max_prod :                                    */
/*    This function accepts an integer array and computes */
/* the maximum consecutive product.  If the maximum is    */
/* negative, this programs returns one.                   */
/*                                                        */
/* Copyright Ching-Kuang Shene               Sept/01/1989 */
/* ------------------------------------------------------ */
int  max_prod(int  x[], int n)
{
     int  max_ending_here = 1;/* max. computed ended here */
     int  min_ending_here = 1;/* min. computed ended here */
     int  max_so_far      = 1;/* global maximum so far    */
     int  temp, i;

     for (i = 0; i < n; i++) {/* scan each element in turn*/
          if (x[i] > 0) {     /* if x[i] is positive ...  */
               max_ending_here *= x[i]; /* max will incr. */
               min_ending_here = MIN(min_ending_here*x[i],1);
          } 
          else if (x[i] == 0) { /* if zero, reset         */
               max_ending_here = 1;
               min_ending_here = 0;
          }
          else {              /* x[i] < 0                 */
               temp            = max_ending_here;
               max_ending_here = MAX(min_ending_here*x[i],1);
               min_ending_here = temp * x[i];
          }
          max_so_far = MAX(max_so_far, max_ending_here);
     }
     return max_so_far;
}

/* ------------------------------------------------------ */
/*(8)                                                     */
/* FUNCTION max_sum :                                     */
/*    This function accepts an integer array and computes */
/* the maximum consecutive sum.  If the maximum sum is    */
/* negative, this programs returns zero.                  */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/01/1989 */
/* ------------------------------------------------------ */
int  max_sum(int  x[], int n)
{
     int  max_ending_here = 0;/* max. computed ended here */
     int  max_so_far      = 0;/* global maximum so far    */
     int  i;

     for (i = 0; i < n; i++) {/* scan each element in turn*/
          if (max_ending_here + x[i] < 0) /* sum positive?*/
               max_ending_here = 0;  /* NO, set it to 0   */
          else                /* else update the max. sum */
               max_ending_here += x[i]; /* ended here and */
          if (max_ending_here > max_so_far) /* sum inc?   */
               max_so_far = max_ending_here;/* YES, update*/
     }
     return max_so_far;
}

/* ------------------------------------------------------ */
/*(9)                                                     */
/* FUNCTION max_sum1 :                                     */
/*    Another slower solution of the max_sum problem with */
/* order O(n log(n)).  Not only it is slower, but also its*/
/* program is much longer.                                */
/*    Note the difference in the function head.  This one */
/* requires 'left', the left boundary pointer, and 'right'*/
/* the right boundary pointer.                            */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/01/1989 */
/* ------------------------------------------------------ */



int  max_sum1(int x[], int left, int right)
{
     int middle;              /* the middle element       */
     int max_to_left;         /* max found in [left,mid]  */
     int max_to_right;        /* max found in [mid+1,rig] */
     int max_crossing;        /* max found cross middle   */
     int sum;                 /* working variable         */
     int left_max;            /* left max from recursion  */
     int right_max;           /* right max from recursion */
     int result, i;

     if (left > right)        /* no element remains?      */
          result = 0;         /* result must be zero      */
     else if (left == right)  /* exactly one element?     */
          result = (x[left] > 0) ? x[left] : 0; /* ret max*/
     else {                   /* now we have many element */
          middle    = (left + right) / 2; /* get the mid. */
          left_max  = max_sum1(x, left, middle); /* left   */
          right_max = max_sum1(x, middle+1, right); /* rig.*/

          sum = 0;            /* compute max from mid down*/
          max_to_left = 0;
          for (i = middle; i >= left; i--) {
               sum += x[i];
               if (max_to_left < sum)
                    max_to_left = sum;
          }

          sum = 0;            /* compute max from mid+1 up*/
          max_to_right = 0;
          for (i = middle+1; i <= right; i++) {
               sum += x[i];
               if (max_to_right < sum)
                    max_to_right = sum;
          }

          max_crossing = max_to_left+max_to_right; /*cross*/
          if (max_crossing >= max_to_left) /* get the max */
               result = max(max_crossing, max_to_right);
          else
               result = max(max_to_left, max_to_right);
     }
     return result;
}
/* ------------------------------------------------------ */
/*(10)                                                    */
/* FUNCTION  find_rectangle :                             */
/*    Given a consecutive length of arcs of a circle, this*/
/* function determines if there exists a rectangle formed */
/* by these end points of arcs.                           */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/25/1989 */
/* ------------------------------------------------------ */

int  find_rectangle(int len[], int n)
{
     int  total;              /* total arc length         */
     int  half;               /* half = total/2           */
     int  sum;                /* running sum              */
     int  start;              /* running index #1         */
     int  end;                /* running index #2         */
     int  count;              /* counter of diametrical pt*/
     int  i;

     for (total = i = 0; i < n; i++)  /* compute total len*/
          total += len[i];
     half = total/2;           /* and its half            */

     count = start = end = 0;  /* initialization          */
     sum   = len[start];       /* running sum = 1st arc   */
     while (start < n - 1)         
          if (sum < half)      /* if shorter -> increase  */
               sum += len[++start];
          else if (sum > half) /* if longer -> decrease   */
               sum -= len[end++];
          else                 /* got one and inc.        */
               sum += len[++start], count++;
     return count;
}
/* ------------------------------------------------------ */
/*(11)                                                    */
/* FUNCTION  sink :                                       */
/*    Given a matrix containing who-knows-who information */
/* this function check the matrix to see if there exists  */
/* the sink, or the celebrity.                            */
/*                                                        */
/* Copyright Ching-Kuang Shene                Aug/27/1989 */
/* ------------------------------------------------------ */

int sink(char know[MAXSIZE][MAXSIZE], int n)
{
     int  candidate;          /* possible candidate       */
     int  next;               /* working; points to next  */
     int  wrong;              /* a loop control variable  */
     int  the_sink;
     int  i, j, k;

     the_sink = NO_SINK;      /* suppose there is no sink */
     candidate = 0;           /* ask question from the 0th*/
     for (i = 1; i < n; i++)
          if (know[candidate][i]) candidate = i;

     for (wrong = NO, k = 0; (k < n) && !wrong; k++) {
          if (know[candidate][k]) /* cand. knows nobody   */
               wrong = YES;   /* so the cand. is wrong    */
          if (!know[k][candidate] && candidate != k)
               wrong = YES;   /* also wring if no one know*/
     }
     if (!wrong)
        the_sink = candidate;
     return the_sink;
}
/* ------------------------------------------------------ */
/*(12)                                                    */
/* FUNCTION  turns :                                      */
/*    Given a sequence of points on the plane and a robot */
/* at the first point facing the X-axi direction, this    */
/* function determines the number of counter-clock turns  */
/* along the tour of all points.  The tour starts from the*/
/* first point.  At any point, the robot makes a counter- */
/* clock-wise turn in order to face the next point.  After*/
/* a turn, it proceeds to next point.  The final position */
/* is the first point facing the X-axi.                   */
/*                                                        */
/* Copyright Ching-Kuang Shene               Sept/01/1989 */
/* ------------------------------------------------------ */

int  turns(int x[], int y[], int n)
{
     int  X     = 1;          /* robot's previous direct X*/
     int  Y     = 0;          /* robot's previous direct Y*/
     int  TURNS = 0;          /* # of 90 turns to 1st Q.  */
     int  count;              /* # of complete 360 turns  */
     int  new_x;              /* ronot's next direct. X   */
     int  new_y;              /* robot's next direct. Y   */
     int  new_turns;          /* # of 90 turns to 1st Q.  */
     int  i, temp;            /* working                  */

     for (count = i = 0; i <= n; i++) { /* scan all points*/
          new_x     = x[(i+1) % n] - x[i % n]; /* new dir.*/
          new_y     = y[(i+1) % n] - y[i % n];
          new_turns = 0;      /* assume no 90 turn.       */
          while (new_x <= 0 || new_y < 0) { /* turn it to */
               temp  = new_x; /* first quartant           */
               new_x = new_y;
               new_y = -temp;
               new_turns++;
          }
          if (TURNS > new_turns || (TURNS == new_turns && Y*new_x > new_y*X))
               count++;       /* crossing X-axi, inc ocunt*/
          X     = new_x;      /* proceed to next point    */
          Y     = new_y;
          TURNS = new_turns;
     }
     return count;            /* return # of 360 turns    */
}

/* ------------------------------------------------------ */
/*(13)                                                    */
/* FUNCTION majority :                                    */
/*    Given vote[] containing a voting record, say x[i]=j */
/* meaning that person i votes person j, this function    */
/* determine if there is any one is a majority.  There is */
/* no limit to the value of j.  In other words, anybody   */
/* can vote someone else and there is no fixed candidate. */
/* Thus value in x[] could be very large, or even larger  */
/* than the size of x[].  'Majority' means that there is  */
/* a guy such that more than n/2 persons votes for him.   */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/01/1989 */
/* ------------------------------------------------------ */

int majority(int vote[], int n)
{
     int  candidate;          /* current candidate        */
     int  vote_count;         /* vote count for the cand. */
     int  count;              /* final count              */
     int  answer;             /* final answer             */
     int  i;

     candidate  = vote[0];    /* assume the guy voted by  */
     vote_count = 1;          /* #1 is the candidate      */
     for (i = 1; i < n; i++)  /* for all other people ... */
          if (vote_count == 0) {  /* if current no count  */
               candidate  = vote[i]; /* pick up a new can.*/
               vote_count = 1; /* give him count 1        */
          }
          else if (candidate == vote[i]) /* is he a candi?*/
               vote_count++;  /* increase his count       */
          else
               vote_count--;  /* NO, decrease his count   */

     if (vote_count == 0)     /* finally check if the cand*/
          answer = 0;       /* is the guy with majority */
     else {
          for (i = 0, count = 0; i < n; i++)
               if (vote[i] == candidate)
                    count++;
          answer = (count > (int)(n / 2.0 + 0.5)) ? candidate : 0;
     }
     return answer;
}

void VOTING(void)
{
     int  x[] = { 2, 2, 4, 2, 1, 2, 5, 2, 2, 8 };
     int  n = sizeof(x)/sizeof(int);
     int  answer, i;

     printf("\nMajority Counting Program");
     printf("\n=========================");
     printf("\n\n  No   Vote");
     printf(  "\n  --   ----");
     for (i = 0; i < n; i++)
          printf("\n%4d%6d", i, x[i]);

     answer = majority(x, n);

     printf("\n");
     if (answer > 0)
          printf("\nMajority is %d", answer);
     else
          printf("\nThere is no majority");
}

void  TURNS(void)
{
     int  x[] = { 0, 5, 7, 5, 8, 1, 4, 6, 2, 0 };
     int  y[] = { 0, 1, 5, 6, 7, 7, 5, 2, 4, 3 };
     int  n = sizeof(x)/sizeof(int);
     int  i;

     printf("\nNumber of 360 turns along a route");
     printf("\n=================================");
     printf("\n\nPoint#    x      y");
     printf(  "\n------------------");
     for (i = 0; i < n; i++)
          printf("\n%5d%6d%7d", i+1, x[i], y[i]);

     printf("\n\nThere are %d complete 360 turns", turns(x, y, n));
}

void SINK(void)
{
     char  know[MAXSIZE][MAXSIZE] 
                      = { { NO,  NO, YES, YES, YES},
                          {YES,  NO, YES, YES, YES},
                          { NO, YES,  NO, YES,  NO},
                          { NO,  NO,  NO,  NO,  NO},
                          {YES,  NO, YES, YES, YES}};
     int   n = 5;
     int   answer, i, j;

     printf("\nSink Finding Program");
     printf("\n====================");
     printf("\n\nGiven know[*,*] Matrix:\n");
     for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
           printf(" %s", know[i][j] ? " Y" : " N");
        printf("\n");
     }
     answer = sink(know, n);
     if (answer >=0)
          printf("\n\nThe sink is %d", answer + 1);
     else
          printf("\n\nNO!, there is no sink");
}
void FIND_RECTANGLE(void)
{
     int  x[] = { 1, 3, 1, 1, 4, 1, 2, 1, 2, 2, 2};
     int  n   = sizeof(x)/sizeof(int);
     int  y[] = { 2, 2, 2, 3, 3};
     int  m   = sizeof(y)/sizeof(int);
     int  z[] = { 10, 2, 2, 2, 2 };
     int  mn  = sizeof(z)/sizeof(int);
     int  i;

     printf("\nRectangle Finding Program");
     printf("\n=========================");
     printf("\n\nFirst Arc Length Set  :");
     for (i = 0; i < n; i++)
          printf("%3d", x[i]);
     printf("\nThere are %d pairs diametrical points.",
             find_rectangle(x, n));

     printf("\n\nSecond Arc Length Set :");
     for (i = 0; i < m; i++)
          printf("%3d", y[i]);
     printf("\nThere are %d pairs diametrical points.",
             find_rectangle(y, m));

     printf("\n\nThird  Arc Length Set :");
     for (i = 0; i < mn; i++)
          printf("%3d", z[i]);
     printf("\nThere are %d pairs diametrical points.",
             find_rectangle(z, mn));
}
void MAXSUM1(void)
{
     int  x[] = { 2, -3, 1, -1, 3, -2, -3, 3};
     int  n   = sizeof(x)/sizeof(int);
     int  i;

     printf("\nMaximum Consecutive Elements Sum Program");
     printf("\n========================================");
     printf("\n\nGiven Array :");

     for (i = 0; i < n; i++)
          printf("%4d", x[i]);

     printf("\n\nMaximum Sum is %d", max_sum1(x, 0, n-1));
}

void MAXSUM(void)
{
     int  x[] = { 2, -3, 1, -1, 3, -2, -3, 3};
     int  n   = sizeof(x)/sizeof(int);
     int  i;

     printf("\nMaximum Consecutive Elements Sum Program");
     printf("\n========================================");
     printf("\n\nGiven Array :");

     for (i = 0; i < n; i++)
          printf("%4d", x[i]);

     printf("\n\nMaximum Sum is %d", max_sum(x, n));
}
void MAXPROD(void)
{
     int  x[] = { 2, -3, 0, -4, 3, -2, -3, 3};
     int  n   = sizeof(x)/sizeof(int);
     int  i;

     printf("\nMaximum Consecutive Elements Producr Program");
     printf("\n============================================");
     printf("\n\nGiven Array :");

     for (i = 0; i < n; i++)
          printf("%4d", x[i]);

     printf("\n\nMaximum Product is %d", max_prod(x, n));
}

void  MAXCOVER(void)
{
     int  x[] = { 1, 6, 2, 1, -2, 3, 5, 2, -4, 3};
     int  n   = sizeof(x)/sizeof(int);
     int  i;

     printf("\nMaximum Cover Interval of an Array");
     printf("\n==================================");
     printf("\n\nGiven Array :\n");
     for (i = 0; i < n; i++)
          printf("%d ", x[i]);
     printf("\n\nMaximum Interval Length = %d", maxcover(x, n));
}

void LIS(void)
{
     int  x[] = { 1, 3, 2, 1, 5, 7, 8, 6, 5, 9, 4, 10, 6 };
     int  n = sizeof(x)/sizeof(int);
     int  i;

     printf("\nLongest Increasing Sequence Program");
     printf("\n===================================\n");
     printf("\nGiven Array : ");
     for (i = 0; i < n; i++)
          printf("%4d", x[i]);
     printf("\n\nLength of L.I.S. is %d", longest_inc_sequence(x, n));
}



void DOMINATR(void)
{
     int  x[] = { 6, 1, 4, 3, 6, 2, 4, 7, 3, 5};
     int  n   = sizeof(x)/sizeof(int);
     int  dom[sizeof(x)/sizeof(int)];
     int  i;

     printf("\nRight Nearest Dominator Program");
     printf("\n===============================\n");
     printf("\n             Dominator   Dominator");
     printf("\n  #   Data      Loc        Value  ");
     printf("\n --   ----   ---------   ---------");

     nearest_dominator(x, dom, n);

     for (i = 0; i < n; i++) {
          printf("\n%3d%6d", i, x[i]);
          if (dom[i] >= 0)
               printf("%10d%12d", dom[i], x[dom[i]]);
          else
               printf("        --          --");
     }
}

void  DIAMETER(void)
{
     int  len[] = { 1, 2, 2, 1, 3, 2, 4, 1, 1, 2, 2, 3};
     int  n = sizeof(len)/sizeof(int);
     int  start, end, i;

     printf("\nPolygon Diameter Computation");
     printf("\n============================");
     printf("\n\nSide #     Length");
     printf(  "\n-----------------");
     for (i = 0; i < n; i++)
          printf("\n%5d%11d", i, len[i]);

     diameter(len, n, &start, &end);
     printf("\n\nDiameter is generated from point %d to %d", start, end);
}
void  balance(void)
{
     int  x[] = { 1, 1, -1, -2, 0, 1, 3, -1, 2, -1};
     int  n   = sizeof(x)/sizeof(int);
     int  i;

     printf("\nMaximum Interval of Balanced Positive/Negative Numbers");
     printf("\n======================================================");
     printf("\n\nGiven Array :\n");
     for (i = 0; i < n; i++)
          printf("%d ", x[i]);
     printf("\n\nInterval Length = %d", pos_neg_balance(x, n));
}


void one_to_one(void)
{
     int  funct_table[7] = { 2, 0, 0, 4, 4, 3, 5};
     int  n              = sizeof(funct_table)/sizeof(int);
     int  status[sizeof(funct_table)/sizeof(int)];
     int  counter[sizeof(funct_table)/sizeof(int)];
     int  i;
     printf("\n(1)");
     printf("\nOne-To-One Function Construction Program");
     printf("\n========================================\n");
     printf("\nDomain    Range    Status");
     printf("\n------    -----    ------");

     find_one_to_one(funct_table, status, counter, n);

     for (i = 0; i < n; i++) {
          printf("\n%4d%10d", i, funct_table[i]);
          if (status[i] == SAVED)
               printf("        SAVED");
          else
               printf("       DELETED");
     }

     printf("\n\nConstructed New 1-1 Function\n");
     printf("\nDomain    Range");
     printf("\n------    -----");
     for (i = 0; i < n; i++)
          if (status[i] == SAVED)
               printf("\n%4d%10d", i, funct_table[i]);
}
void one_to_one();
void balance();
void DIAMETER();
void DOMINATR();
void LIS();
void MAXCOVER();
void MAXPROD();
void MAXSUM();
void MAXSUM1();
void FIND_RECTANGLE();
void SINK();
void VOTING();
void main(){
    one_to_one();
    balance();
    DIAMETER();	
    DOMINATR();
    LIS();
    MAXCOVER();
    MAXPROD();
    MAXSUM();
    MAXSUM1();
    FIND_RECTANGLE();
    SINK();
    VOTING();
}
