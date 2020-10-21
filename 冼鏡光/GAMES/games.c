#include  <stdio.h>
#include  <stdlib.h>

#define   MAXSIZE    20
#define   ALWAYS      1
#define   YES         1
#define   NO          0
#define   SUCCESS     1
#define   FAIL       -1
#define   MAX_DISK   31

#define   MAXSIZE  30         /* no more than 30 vertices */

#define   FAILURE   0

/* ------------------------------------------------------ */
/*(1)__*/
/*             types and external variables               */
/* ------------------------------------------------------ */

typedef   struct node  Node;  /* trail node (linked list) */

struct node {                 /* a node consists of ...   */
     int   vertex;            /*    a vertex number field */
     Node  *next;             /*    and a next node ptr   */
};

int  connect[MAXSIZE][MAXSIZE];  /* the connection matrix */
int  deg[MAXSIZE];            /* degree array             */
int  n;                       /* number of vertices       */
Node *trail;                  /* pointer to Euler trail   */

/* ------------------------------------------------------ */
/* (1)             function prototypes                    */
/* ------------------------------------------------------ */

void  read_in(void);                      /*(1)-1*/
Node  *euler(void);                       /*(1)__*//*(1)-2*/
int   prepare(Node **, Node **);          /*(1)-3*/
int   find_next(Node **);                 /*(1)-4*/
void  find_trail(int, Node **, Node **);  /*(1)-5*/
void  display(void);                      /*(1)-6*/



/* ------------------------------------------------------ */
/* (1)                                                  */
/*PROGRAM  euler :                                        */
/*    This porgram accepts a multi-graph and finds an     */
/* Euler Trail if possible.                               */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/30/1989 */
/* ------------------------------------------------------ */
void  EULER(void)
{
     printf("\nEuler Trail Program");
     printf("\n===================\n");

     read_in();               /* get data                 */
     trail = euler();         /* compute Euler Trail      */
     display();               /* display result           */
}
     
/* ------------------------------------------------------ */
/*(1)-1                                                   */
/* FUNCTION  read_in :                                    */
/*    This function reads in the connection matrix and    */
/* then compute the degree array.                         */
/* ------------------------------------------------------ */

void  read_in(void)
{
     int  i, j;
     char line[100];

     gets(line);              /* get in number of vertices*/
     n = atoi(line);
     for (i = 0; i < n; i++) { /* clear the connection mtx*/
          deg[i] = 0;
          for (j = 0; j < n; j++)
               connect[i][j] = 0;
     }
     gets(line);              /* get 1st line of edge set */
     sscanf(line, "%d%d", &i, &j);
     while (i != 0 && j != 0) { /* end of file ?          */
          if (i != j) {       /* a loop ?                 */
               connect[i-1][j-1]++;   /* increase edge cnt*/
               connect[j-1][i-1]++;
               deg[i-1]++;    /* increase degree count    */
               deg[j-1]++;
          }
          else                /* ignore all self loops    */
               printf("\n*** ERROR *** A loop found.  Data ignored");
          gets(line);         /* get next edge            */
          sscanf(line, "%d%d", &i, &j);
     }
}

/* ------------------------------------------------------ */
/*(1)-2                                                   */
/* FUNCTION  euler :                                      */
/*    This is the main working routine of this program.   */
/* It calls prepare() to initialize various data field and*/
/* some checks.  Then compute the Euler Trail loop by loop*/
/* ------------------------------------------------------ */

Node  *euler(void)
{
     Node *current;           /* processing cursor        */
     Node *head, *tail;       /* bound a partial trail    */
     Node *p1, *p2;           /* working pointer variables*/
     int  VTX;

     if (prepare(&head, &tail) == FAIL) /* prepare data   */
          return NULL;        /* if fail, return NULL     */

     current = tail;          /* start from the tail      */
     while (ALWAYS) 
          if ((VTX = find_next(&current)) != FAIL) {
               find_trail(VTX, &p1, &p2);
               p2->next = current->next; /* join the trail*/
               current->next = p1;
               current = p1;  /* step to next node        */
          }
          else
               break;
     return head;             /* return the trail list    */
}

/* ------------------------------------------------------ */
/*(1)-3                                                   */
/* FUNCTION  prepare :                                    */
/*    This function checks to see if there are more two   */
/* odd degree vertices.  It reject a graph with more than */
/* two odd degree vertices.  Then it builds a preliminary */
/* trail list consisting of one node (if all vertices are */
/* even), or two nodes (for the two odd degree vertices). */
/* ------------------------------------------------------ */

int   prepare(Node **first, Node **last)
{
     Node *p1, *p2;
     int  no, odd_no, i;
     int  odd[2];

     for (no = odd_no = i = 0; i < n; i++) /* test odd deg*/
          if (deg[i] % 2 != 0) {
               odd_no++;
               if (no < 2)
                    odd[no++] = i;
          }
     if (odd_no > 2) {        /* more than two odd deg VTX*/
          printf("\n*** ERROR *** too many odd degree vertices.");
          return FAIL;
     }
     if (odd_no == 2) {       /* exactly two odd VTX      */
          p1 = (Node *) malloc(sizeof(Node)); /* get mem. */
          p2 = (Node *) malloc(sizeof(Node));
          connect[odd[0]][odd[1]]--;  /* just remove this */
          connect[odd[1]][odd[0]]--;  /* odd degree edge  */
          deg[odd[0]]--;
          deg[odd[1]]--;
          p1->vertex = odd[0]; /* these two vertices are  */
          p1->next   = p2;     /* the must for first step */
          p2->vertex = odd[1]; /* thus put them into the  */
          p2->next   = NULL;   /* trail list              */
          *first = p1;         /* return this list        */
          *last  = p2;
     }
     else {                   /* all vertices are even    */
          p1 = (Node *) malloc(sizeof(Node)); /* get mem. */
          p1->vertex = 0;     /* it is the only one node  */
          p1->next   = NULL;  /* in the trail list        */
          *first = *last = p1;/* return the trail list    */
     }
     return SUCCESS;
}

/* ------------------------------------------------------ */
/*(1)-4                                                   */
/* FUNCTION  find_next :                                  */
/*    Given a pointer to some vertex which has already    */
/* been put into trail list, this function scans the trail*/
/* list in order to find a vertex with non-zero degree.   */
/* ------------------------------------------------------ */

int   find_next(Node **p)
{
     for (;(*p)!=NULL && deg[(*p)->vertex]==0; (*p)=(*p)->next)
          ;
     return ((*p) == NULL) ? FAIL : (*p)->vertex;
}

/* ------------------------------------------------------ */
/*(1)-5                                                   */
/* FUNCTION  find_trail :                                 */
/*    Given a vertex, this function computes a trail      */
/* starting from the given vertex and returns the trail   */
/* list found.                                            */
/* ------------------------------------------------------ */

void  find_trail(int start, Node **head, Node **tail)
{
     Node *first, *last, *ptr;
     int  p, i, done;

     first = last = NULL;     /* no node in list currently*/
     p     = start;           /* p is a moving vertex     */
     done  = NO;
     while (ALWAYS) {
          for (i = 0; i < n && !connect[p][i]; i++)
               ;              /* find a VTX adjacent to p */
          if (i < n) {        /* p->i is possible         */
               connect[p][i]--,  connect[i][p]--; 
               deg[p]--,         deg[i]--;
               ptr = (Node *) malloc(sizeof(Node));
               ptr->vertex = i;     /* make node and put  */
               ptr->next   = NULL;  /* it into the trail  */
               if (first == NULL)
                    first = last = ptr;
               else {
                    last->next = ptr;
                    last       = ptr;
               }
               p = i;         /* step to the next         */
          }
          else                /* if can not proceed, stop */
              break;
     }
     *head = first;           /* return the trail list    */
     *tail = last;
}

/* ------------------------------------------------------ */
/*(1)-6                                                   */
/* FUNCTION  display :                                    */
/*    Simple routine.  It display the Euler Trail.        */
/* ------------------------------------------------------ */

void  display(void)
{
     Node *ptr = trail;
     int  i = 0;

     if (trail == NULL) 
          return;
     printf("\nAn Euler Trail has been Found :\n");
     for ( ; ptr->next != NULL; ptr = ptr->next, i++) {
          if (i % 15 == 0)  printf("\n");
          printf("%2d->", ptr->vertex+1);
     }
     if (i % 15 == 0) printf("\n");   /* the last item    */
     printf("%2d", ptr->vertex+1);
}

/* ------------------------------------------------------ */
/*(2)                                                     */
/* PROGRAM  Hamilton cycle finder :                       */
/*    Given an undirected graph with at least 3 vertices, */
/* this program dins out one of the Hamilton Cycle.  If   */
/* there is no such cycle at all, this result will also   */
/* be reported.  NOTE that Hamilton Cycle problem is a    */
/* NP-Complete problem and so don't expect any efficient  */
/* algorithm.  This program employs the backtrack method  */
/* used in previous problems.                             */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/23/1989 */
/* ------------------------------------------------------ */
/* ------------------------------------------------------ */
/*(2)-1                                                   */
/* FUNCTION  Hamilton_read_in :                                    */
/*    Read in the number of vertices and the edges.  Then */
/* build up the adjacenct matrix.  NOTE that because the  */
/* graph is undirected, an edga (s,t) will represent two  */
/* 'edges' in the graph, namely (s,t) and (t,s).  This    */
/* function reflects this fact by set two entries.        */
/* ------------------------------------------------------ */

void  Hamilton_read_in(int connected[][MAXSIZE], int *n)
{
     int  i, j;

     scanf("%d", n);          /* read in the number of VTX*/
     for (i = 0; i < *n; i++) /* clear the adjacent matrix*/
          for (j = 0; j < *n; j++)
               connected[i][j] = NO;

     scanf("%d%d", &i, &j);   /* read in first edge       */
     while (i != 0 && j != 0) {  /* end ?                 */
          connected[i-1][j-1] = YES; /* NO, setup two     */
          connected[j-1][i-1] = YES; /* symmetric edges   */
          scanf("%d%d", &i, &j); /* read next one         */
     }
     for (i = 0; i < *n; i++) /* clear diagonal           */
          connected[i][i] = NO;
}

/* ------------------------------------------------------ */
/*(2)-2                                                   */
/* FUNCTION  hamilton :                                   */
/*    Given the adjacent matrix connected[], the number   */
/* of vertices and the start vertex, this function finds  */
/* a Hamilton Cycle and stores it in cycle[].             */
/* ------------------------------------------------------ */

int  hamilton(int  connected[][MAXSIZE], int cycle[], int n, int start)
{
     int  *visited;           /* visited marks            */
     int  top, i;

     visited = (int *) malloc(sizeof(int)*n); /* get mem. */
     for (i = 0; i < n; i++)  /* clear marks to NO        */
          visited[i] = NO;
     visited[start] = YES;    /* but the start has visited*/

     cycle[0] = start;        /* the cycle has 'start'    */
     cycle[1] = 0;            /* next in cycle is VTX 0   */
     top      = 1;            /* the top working element  */

     while (ALWAYS) {         /* loop until done          */
          for (i = cycle[top]; i < n; i++) /* find next   */
               if (connected[cycle[top-1]][i] && !visited[i])
                    break;
          if (i < n) {        /* all neighbors tried?     */
               cycle[top] = i;/* NO, a new vertex in cycle*/
               visited[cycle[top]] = YES;
               if (top == n-1 && connected[cycle[top]][start]) {
                    free(visited); /* if all visited ...  */
                    return SUCCESS;/* return SUCCES       */
               }
               else           /* otherwise, advance.      */
                    cycle[++top] = 0;
          }
          else {              /* next not found .....     */
               visited[cycle[--top]] = NO; /* backtrack   */
               if (top == 0) { /* return to the start VTX?*/
                    free(visited); /* YES, failed.        */
                    return FAILURE;
               }
                    cycle[top]++;  /* NO, move to neighbr */
          }
     }
}

/* ------------------------------------------------------ */
/*(2)-3                                                   */
/* FUNCTION  Hamilton_display :                                    */
/*    Display the found cycle.                            */
/* ------------------------------------------------------ */

void  Hamilton_display(int cycle[], int n)
{
     int  i;
  
     printf("\n\nA Hamilton Cycle is Listed as Follows :");
     printf("\n\n%d", cycle[0]+1);
     for (i = 1; i < n; i++)
          printf("->%d", cycle[i]+1);
     printf("->%d", cycle[0]+1);
}


/* ------------------------------------------------------ */

void HAMILTON(void)
{
     int  connected[MAXSIZE][MAXSIZE];
     int  cycle[MAXSIZE];
     int  n;

     printf("\nHamilton Cycle Program");
     printf("\n======================");
     Hamilton_read_in(connected, &n);
     if (hamilton(connected, cycle, n, 0) == SUCCESS)
          Hamilton_display(cycle, n);
     else
          printf("\n\nNO Hamilton Cycle at all.");
}

/* ------------------------------------------------------ */
/*(3)                                                     */
/* PROGRAM towers of hanoi :                              */
/*    Given the number of disk to be moved, this function */
/* moves the number of disks from pin 1 to pin 3 subject  */
/* to the restriction of the rules of the towers of Hanoi */
/* without recursion.  The basic idea behind this program */
/* is the Gray Code.  But the formulation of this program */
/* follows from an article of Don Perkins and H. Mayer.   */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/20/1989 */
/* ------------------------------------------------------ */
#define   MAX_DISK   31

int  which_disk(unsigned long *);

/* ------------------------------------------------------ */
/*(3)-1                                                   */
/* FUNCTION which_disk :                                  */
/*    Given the previous counter value, this function     */
/* computes the only one bit changed from 0 to 1 by adding*/
/* one.  This value corresponding to Gray Code.           */
/* ------------------------------------------------------ */

int  which_disk(unsigned long *counter)
{
     unsigned long a, b, c;
     int  i;

     a = *counter;
     *counter = b = a + 1;
     for (c = a^b, i = 0; c != 0; c >>= 1, i++)
          ;
     return i;
}

void  HANOI(void)
{
     int  number_of_disk;     /* the number of disks      */
     int  pin[MAX_DISK+1];    /* locations of disks       */
     int  dir[2];             /* directions; 0=pos,1=neg  */
     int  disk;               /* disk to be moved         */
     int  next;               /* next position of 'disk'  */
     int  index;              /* direction subscript      */
     unsigned long number_of_moves; /* number of moves    */
     unsigned long counter;   /* counter for Gray Code    */
     unsigned long i;         /* working                  */
     char line[100];          /* input line               */

     printf("\nIterative Towers of Hanoi Program");
     printf("\n=================================");
     printf("\n\nHow many disks (<=31) ? ");
     gets(line);

     number_of_disk  = atoi(line);
     number_of_moves = (0x01UL << number_of_disk) - 1;
     counter         = 0;       /* counter for Gray Code  */

     if (number_of_disk & 0x01) /* setup direction        */
          dir[0] = 0, dir[1] = 1;
     else
          dir[0] = 1, dir[1] = 0;

     for (i = 1; i <= number_of_disk; i++) /* set up loc. */
          pin[i] = 1;

     printf("\n   Step   Disk #    From      To");
     printf("\n   -----------------------------");

     for (i = 1; i <= number_of_moves; i++) {
          disk  = which_disk(&counter); /* get disk #     */
          index = disk & 0x01;  /* compute direction index*/
          next = (pin[disk] + dir[index]) % 3 + 1;
          printf("\n%6lu%8d%10d%8d", i, disk, pin[disk], next);
          pin[disk] = next;
     }
}

/* ------------------------------------------------------ */
/*(4)                                                     */
/* PROGRAM knight tour :                                  */
/*    Given a n*n chess board and a starting position,    */
/* this program will find a knight tour path passing      */
/* through each square on the chess board exactly once by */
/* using backtrack technique without recursion.  For      */
/* larger n, for example n > 6, it will take very long    */
/* time to find such path.  Therefore be patience please. */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/20/1989 */
/* ------------------------------------------------------ */

#define   MAXSIZE     10      /* max. board size          */
#define   MAX_STACK  100      /* stack size = board-size^2*/
#define   SUCCESS      1      /* return value for a succ. */
#define   FAILURE      0      /* for a failure.           */
#define   EMPTY       -1      /* value to indicate empty  */

/* ----------------- external variables ----------------- */

int  board[MAXSIZE+1][MAXSIZE+1];   /* chess board        */
int  n;                       /* working board size       */
int  offset_x[] = { 2,  1, -1, -2, -2, -1,  1,  2};
int  offset_y[] = { 1,  2,  2,  1, -1, -2, -2, -1};

int  path_x[MAX_STACK+1];     /* stack for x coordinate   */
int  path_y[MAX_STACK+1];     /* stack for y coordinate   */
int  direction[MAX_STACK+1];  /* stack for direction      */
int  top;                     /* stack pointer            */

/* ----------------- function prototype ----------------- */

void  knight_initial(void);
void  knight_display(void);
int   knight_try(int, int);

/* -------------------- main program -------------------- */

void  KNIGHT(void)
{
     int   row, column;
     char  line[100];

     printf("\nRecursive Knight Tour Problem");
     printf("\n=============================");
     printf("\n\nBoard Size ----> ");
     gets(line);
     n = atoi(line);
     printf(    "Start Row -----> ");
     gets(line);
     row = atoi(line);
     printf(    "Start Column --> ");
     gets(line);
     column = atoi(line);
 
     knight_initial();
     if (knight_try(row, column) == FAILURE)
          printf("\nNO SOLUTION AT ALL.");
     else
          knight_display();
}


/* ------------------------------------------------------ */
/*(4)-1                                                   */
/* FUNCTION knight_initial :                              */
/*    initialize the chess board to EMPTY.                */
/* ------------------------------------------------------ */

void  knight_initial(void)
{
     int  i, j;

     for (i = 1; i <= n; i++)
          for (j = 1; j <= n; j++)
               board[i][j] = EMPTY;
}


/* ------------------------------------------------------ */
/*(4)-2                                                   */
/* FUNCTION knight_display :                              */
/*    display to chess board.                             */
/* ------------------------------------------------------ */

#define  DRAWGRID(N)     { int i;                          \
                           printf("\n+");                  \
                           for (i = 1; i <= N; i++)        \
                                printf("--+");             \
                         }


#define  DRAWLINE(N, r)  { int i;                          \
                           printf("\n|");                  \
                           for (i = 1; i <= N; i++)        \
                                printf("%2d|",board[r][i]);\
                         }


void  knight_display(void)
{
     int  r;

     printf("\n\nHere is One Possible Solution :\n");
     DRAWGRID(n);
     for (r = 1; r <= n; r++) {
          DRAWLINE(n,r);
          DRAWGRID(n);
     }
}


/* ------------------------------------------------------ */
/*(4)-3                                                   */
/* FUNCTION try :                                         */
/*    The main non-recursive backtrack working routine.   */
/* ------------------------------------------------------ */

#define  YES          1
#define  NO           0
#define  BOARD(x,y)   (1<=x) && (x<=n) && (1<=y) && (y<=n)
#define  CHECK(x,y)   board[x][y] == EMPTY
#define  PUSH(x,y)    { top++;                             \
                        path_x[top] = x; path_y[top] = y;  \
                        direction[top] = 0;                \
                        board[x][y] = top;                 \
                      }

int  knight_try(int x, int y)
{
     int  new_x, new_y;
     int  found;

     top = -1;                /* initial to empty         */
     PUSH(x, y);              /* push first pos. and dir. */
     while (top < n*n-1) {    /* loop until the board full*/
          found = NO;         
          while (direction[top] < 8) { /* try all 8 pos.  */
               new_x = path_x[top] + offset_x[direction[top]];
               new_y = path_y[top] + offset_y[direction[top]];
               if (BOARD(new_x,new_y) && CHECK(new_x,new_y)) {
                    PUSH(new_x, new_y); /* a new pos. PUSH*/
                    found = YES;        /* set flag       */
                    break;              /* try next pos.  */
               }
               else
                    direction[top]++;   /* OR try next dir*/
          }
          if (!found)         /* if no new pos. is found  */
               if (top > 0) { /* do we have prev. item?   */
                    board[path_x[top]][path_y[top]] = EMPTY;
                    direction[--top]++; /* YES, backtrack */
               }
               else
                    return FAILURE; /* otherwise, FAILURE */
     }
     return SUCCESS;          /* all pos. visited. DONE   */
}

/* ------------------------------------------------------ */
/*(5)-1                                                   */
/* PROGRAM  game of life :                                */
/*    This is a finite implementation of John H. Conway's */
/* Game of Life.  Refere to my book for detail please.    */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/25/1989 */
/* ------------------------------------------------------ */
#define   MAXSIZE      50     /* board size               */
#define   OCCUPIED      1     /* occupied flag            */
#define   UNOCCUPIED    0
#define   YES           1
#define   NO            0

char  cell[MAXSIZE][MAXSIZE];      /* the board           */
char  workcopy[MAXSIZE][MAXSIZE];  /* a working copy      */
int   row;                    /* No. of rows you want     */
int   column;                 /* no. of columns you want  */
int   generations;            /* maximum no. of generation*/

/* ------------------------------------------------------ */
/*(5)-2                                                   */
/* FUNCTION  read_in :                                    */
/*    This function reads in the number of generations,   */
/* the number of rows, the number of columns and finally  */
/* the initial configuration (the generation 0).  Then put*/
/* your configuration to the center of the board.         */
/* ------------------------------------------------------ */

void  read_in(void)
{
     int  max_row, max_col;   /* max # of row and col.    */
     int  col_gap, row_gap;   /* incremnet of row and col */
     int  i, j;
     char line[100];

     gets(line);              /* read in gens, row and col*/
     sscanf(line, "%d%d%d", &generations, &row, &column);
     for (i = 0; i < row; i++)/* clear the board          */
          for (j = 0; j < column; j++)
               cell[i][j] = UNOCCUPIED;
     max_col = 0;             /* read in the config.      */
     for (max_row = 0; gets(line) != NULL; max_row++) {
          for (i = 0; line[i] != '\0'; i++)
               if (line[i] != ' ')
                    cell[max_row][i] = OCCUPIED;
          max_col = (max_col < i) ? i : max_col;
     }
     row_gap = (row - max_row)/2;    /* the moving gap    */
     col_gap = (column - max_col)/2;
     for (i = max_row + row_gap - 1; i >= row_gap; i--) {
          for (j = max_col + col_gap - 1; j >= col_gap; j--)
               cell[i][j] = cell[i-row_gap][j-col_gap];
          for ( ; j >= 0; j--)
               cell[i][j] = UNOCCUPIED;
     }
     for ( ; i >= 0; i--)
          for (j = 0; j < column; j++)
               cell[i][j] = UNOCCUPIED;
}

/* ------------------------------------------------------ */
/*(5)-3                                                   */
/* FUNCTION  display :                                    */
/*    Display the board.                                  */
/* ------------------------------------------------------ */

#define   DRAW_BOARDER(n) { int i;                    \
                            printf("\n+");            \
                            for (i = 0; i < n; i++)   \
                                 printf("-");         \
                            printf("+");              \
                          }
void  display(int gen_no)
{
     int  i, j;

     if (gen_no == 0)
          printf("\n\nInitial Generation :\n");
     else
          printf("\n\nGeneration %d :\n", gen_no);

     DRAW_BOARDER(column);
     for (i = 0; i < row; i++) {
          printf("\n|");
          for (j = 0; j < column; j++)
               printf("%c", (cell[i][j] == OCCUPIED) ? '*' : ' ');
          printf("|");
     }
     DRAW_BOARDER(column);
}

/* ------------------------------------------------------ */
/*(5)-4                                                   */
/* FUNCTION  game_of_life :                               */
/*    This is the main function of Game of Life.          */
/* ------------------------------------------------------ */

void  game_of_life(void)
{
     int  stable;             /* stable flag              */
     int  iter;               /* iteration count          */
     int  top, bottom, left, right; /* neighborhood bound */
     int  neighbors;          /* # of neighbors           */
     int  cell_count;         /* # of cells count         */
     int  done;
     int  i, j, p, q;

     display(0);              /* display initial config.  */
     done = NO;
     for (iter = 1; iter <= generations && !done; iter++) {
          memmove(workcopy, cell, MAXSIZE*MAXSIZE); /*copy*/
          stable     = YES;   /* assume it is in stable   */
          cell_count = 0;     /* # of survived cells = 0  */
          for (i = 0; i < row; i++) { /* scan each cell...*/
               top    = (i == 0) ? 0 : i - 1;
               bottom = (i == row - 1) ? row-1 : i + 1;
               for (j = 0; j < column; j++) {
                    left  = (j == 0) ? 0 : j - 1;
                    right = (j == column - 1) ? column-1 : j + 1;

                    /* compute number of neighbors        */

                    neighbors = 0;
                    for (p = top; p <= bottom; p++)
                         for (q = left; q <= right; q++)
                              neighbors += workcopy[p][q];
                    neighbors -= workcopy[i][j];

                    /* determine life or dead             */

                    if (workcopy[i][j] == OCCUPIED) 
                         if (neighbors == 2 || neighbors == 3) {
                              cell[i][j] = OCCUPIED;
                              cell_count++;
                         }
                         else
                              cell[i][j] = UNOCCUPIED;
                    else if (neighbors == 3) {
                         cell[i][j] = OCCUPIED;
                         cell_count++;
                    }
                    else
                         cell[i][j] = UNOCCUPIED;
                    stable = stable && (workcopy[i][j] == cell[i][j]);
               }
          }
          if (cell_count == 0) {
               printf("\n\nAll cells die out.");
               done = YES;
          }
          else if (stable) {
               printf("\n\nSystem enters a stable state.");
               done = YES;
          }
          else
               display(iter);
     }
}

/* ------------------------------------------------------ */

void  LIFE(void)
{
     read_in();
     game_of_life();
}

/* ------------------------------------------------------ */
/*(6)                                                     */
/* PROGRAM  doubly even magic builder :                   */
/*    Given an integer n = 4*m, m > 0, this program builds*/
/* up a magic square of order n.                          */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/23/1989 */
/* ------------------------------------------------------ */

#include  <stdio.h>
#include  <stdlib.h>

#define   MAXSIZE   20        /* square size              */
#define   MARK      -1        /* marker for build up      */

void  MAGIC_DE(void)
{
     int  square[MAXSIZE][MAXSIZE]; /* the square         */
     int  n;                  /* order of the magic square*/
     int  count, inv_count;   /* 1 -> n^2 and n^2 -> 1    */
     int  marker;             /* working marker 1,-1,1,-1 */
     int  i, j;
     char line[100];

     printf("\nDoubly-Even Magic Square");
     printf("\n========================");
     printf("\n\nOrder (4*m, m>0) please --> ");
     gets(line);
     n = atoi(line);
     if (n % 4 != 0)
          printf("\n*** Illegal Order *****");
     else {
          marker = MARK;      /* mark the upper part      */
          for (i = 0; i < n/2; i++, marker = -marker)
               for (j = 0; j < n/2; j++, marker = -marker)
                    square[i][j] = square[i][n-1-j] = marker;

          count     = 1;      /* upward counter           */
          inv_count = n*n;    /* downward counter         */
          for (i = 0; i < n/2; i++)
               for (j = 0; j < n; j++)
                    if (square[i][j] != MARK) {  /* marked*/
                         square[i][j] = count++;
                         square[n-1-i][n-1-j] = inv_count--;
                    }
                    else {    /* unmarked                 */
                         square[i][j] = inv_count--;
                         square[n-1-i][n-1-j] = count++;
                    }
          printf("\n");
          for (i = 0; i < n; i++) {
               for (j = 0; j < n; j++)
                    printf("%4d", square[i][j]);
               printf("\n");
          }
     }
}

/* ------------------------------------------------------ */
/*(7)                                                     */
/* PROGRAM magic square of odd order :                    */
/*    This program will fills a matrix of order n*n with  */
/* integers of 1 to n*n such that the sums of rows,       */
/* columns and two disgonals are all the same.  DON'T     */
/* READ THIS PROGRAM before read my book.                 */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/03/1989 */
/* ------------------------------------------------------ */

#include  <stdio.h>
#include  <stdlib.h>

#define   MAXSIZE   20

void MAGIC_O(void)
{
     int  matrix[MAXSIZE][MAXSIZE]; /* the magic square   */
     int  count;                    /* 1..n*n counting    */
     int  row;                      /* row index          */
     int  column;                   /* column index       */
     int  order;                    /* input order        */
     char line[100];

     printf("\nOdd Order Magic Square Generator");
     printf("\n================================");
     printf("\n\nOrder Please --> ");
     gets(line);
     order = atoi(line);

     if (order > MAXSIZE)
          printf("\n*** ERROR ***  Order should be <= %d", MAXSIZE);
     else if (order % 2 == 0)
          printf("\n*** ERROR ***  Order must be an odd integer");
     else {
          row    = 0;         /* start of from the middle */
          column = order/2;   /* of the first row.        */
          for (count = 1; count <= order*order; count++) {
               matrix[row][column] = count; /* put next # */
               if (count % order == 0)  /* move down ?    */
                    row++;    /* YES, move down one row   */
               else {         /* compute next indices     */
                    row    = (row == 0) ? order - 1 : row - 1;
                    column = (column == order-1) ? 0 : column + 1;
               }
          }
          printf("\n\nMagic Square of order %d :\n\n", order);
          for (row = 0; row < order; row++) {
               for (column = 0; column < order; column++)
                    printf("%4d", matrix[row][column]);
               printf("\n");
          }
     }
}

/* ------------------------------------------------------ */
/* PROGRAM  singly-even magic square :                    */
/*    Given an integer of form 2*(2k+1), this program     */
/* builds up a magic square with numbers from 1 to n*n.   */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/23/1989 */
/* ------------------------------------------------------ */

#define    MAXSIZE   30

void  singly_even(int [][MAXSIZE], int);
void  magic_o(int [][MAXSIZE], int);
void  exchange(int [][MAXSIZE], int);

/* ------------------------------------------------------ */
/* FUNCTION  singly_even :                                */
/*    This is the driver program.  It fills the upper-left*/
/* lower-right, upper-right and lower-left parts by using */
/* odd order magic square routine.  Then exchange some    */
/* parts in each routine in order to maintain the magic   */
/* properties.                                            */
/* ------------------------------------------------------ */

void  singly_even(int matrix[][MAXSIZE], int n)
{
     int  half = n/2;

     magic_o(matrix, half);
     exchange(matrix, n);
}


/* ------------------------------------------------------ */
/*(8)                                                     */
/* FUNCTION  magic_o :                                    */
/*    Odd order magic square routine.  It fills the block */
/* bounded by left, right, top and bottom with numbers    */
/* starting from 'start'.  Otherwise all are the same as  */
/* the magic square routine discussed before.             */
/* ------------------------------------------------------ */

void  magic_o(int matrix[][MAXSIZE], int n)
{
     int  count;                    /* fill counting      */
     int  row;                      /* row index          */
     int  column;                   /* column index       */

     row    = 0;              /* start of from the middle */
     column = n/2;               /* of the first row.     */
     for (count = 1; count <= n*n; count++) {
          matrix[row][column] = count;      /* put # in A */
          matrix[row+n][column+n] = count + n*n; /* in B  */
          matrix[row][column+n] = count + 2*n*n; /* in C  */
          matrix[row+n][column] = count + 3*n*n; /* in D  */
          if (count % n == 0) /* move downward ?          */
               row++;         /* YES, move down one row   */
          else {              /* compute next indices     */
               row    = (row == 0) ? n - 1 : row - 1;
               column = (column == n-1) ? 0 : column + 1;
          }
     }
}


/* ------------------------------------------------------ */
/* FUNCTION  exchange :                                   */
/*    This function exchanges some parts in each row in   */
/* order to maintain the magic square properties.         */
/* ------------------------------------------------------ */

#define   SWAP(x,y)   { int t; t = x; x = y; y = t;}

void  exchange(int x[][MAXSIZE], int n)
{
     int  width  = n / 4;
     int  width1 = width - 1;
     int  i, j;

     for (i = 0; i < n/2; i++)
          if (i != width) {   /* if not the width-row    */
               for (j = 0; j < width; j++) 
                    SWAP(x[i][j], x[n/2+i][j]);
               for (j = 0; j < width1; j++)
                    SWAP(x[i][n-1-j], x[n/2+i][n-1-j]);
          }
          else {              /* width-row is special    */
               for (j = 1; j <= width; j++)
                    SWAP(x[width][j], x[n/2+width][j]);
               for (j = 0; j < width1; j++)
                    SWAP(x[width][n-1-j], x[n/2+width][n-1-j]);
          }
}

/* ------------------------------------------------------ */

void  MAGIC_SE(void)
{
     int  matrix[MAXSIZE][MAXSIZE];
     int  n;
     int  i, j;
     char line[100];

     printf("\nSingly-Even Order Magic Square");
     printf("\n==============================");
     printf("\n\nOrder Please (must be 2*(2k+1)) --> ");
     gets(line);
     n = atoi(line);

     if (n % 2 == 0 && (n/2) % 2 == 1) {
          singly_even(matrix, n);
          printf("\n");
          for (i = 0; i < n; i++) {
               for (j = 0; j < n; j++)
                    printf("%4d", matrix[i][j]);
               printf("\n");
          }
     }
     else
          printf("\n*** Illegal Order ***");
}

void  EULER();
void  HAMILTON();
void  HANOI();
void  KNIGHT();
void  LIFE();
void  MAGIC_DE();
void  MAGIC_O();
void  MAGIC_SE();

void main(){
    //EULER();
    //HAMILTON();
    //HANOI();
    //KNIGHT();
    LIFE();
    MAGIC_DE();
    MAGIC_O();
    MAGIC_SE();
}
