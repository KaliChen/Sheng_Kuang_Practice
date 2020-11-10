/* ------------------------------------------------------ */
/* PROGRAM reversed polish form translator :              */
/*    Given a string containing an arithmetic exoression, */
/* this program translates it to reversed Polish form by  */
/* using a stack.                                         */
/*                                                        */
/* Copyright Ching-Kuang Shene               July/12/1989 */
/* ------------------------------------------------------ */

#include  <stdio.h>           /* for I/O operation        */
#include  <stddef.h>          /* for EXIT_FAULAIR & ...   */
#include  <ctype.h>           /* for isspace() & ...      */
#include  "polish.h"



void initial(void);           /* initial stack            */
char stack_top(void);         /* return top of prec. stack*/
void push(char, char);        /* push opr and its preced. */
char pop(void);               /* pop operator only        */


void initial(void)            /* initialize operator stack*/
{
     top = 0;
     code[top] = BOTTOM;
}

char stack_top(void)          /* ret. top element of prec */
{
     return code[top];
}


void push(char operator, char opr_code) /* push opr & pre */
{
     if (++top == MAX_DEPTH) {
          printf("\n*** ERROR *** Stack Overflow.");
          exit(1);
     }
     else {
          stack[top] = operator; 
          code[top]  = opr_code;
     }
}

char pop(void)                /* pop up operator only     */
{
     if (top == 0) {
          printf("\n*** ERROR *** Stack Underflow.");
          exit(1);
     }
     else 
          return stack[top--];
}

int polish(void)                /* main routine starts here */
{
     char  line[100];         /* input line               */
     char  *p;                /* line cursor              */
     char  opr, t;

     printf("\nCompile to Reversed Polish Program");
     printf("\n==================================");
     printf("\n\nYour Input --> ");
     p = gets(line);
     printf("\n\nAnswer is ---> ");

     initial();               /* initialize the two stacks*/
     for (; ; p++) {          /* loop for each char.      */
          if (isalpha(*p))    /* is it an operator        */
               printf("%c ", *p);  /* YES, output it      */
          else if (*p == '(') /* or, is it a '('          */
               push(*p, LEFT_PAR); /* YES! push it.       */
          else if (!isspace(*p)) { /* or, not a space?    */
               switch(*p) {   /* it must be an operator   */
                    case '+' :         /* handle + and -  */
                    case '-' : opr = PLUS_MINUS;
                               break;
                    case '*' :         /* handle * and /  */
                    case '/' : opr = MUL_DIV;
                               break;
                    case ')' : opr = RIGHT_PAR; /* ')'    */
                               break;
                    case '\0': opr = EOL;       /* EOL    */
                               break;
                    default  : printf("*** Unrecognizable char ***");
                               exit(EXIT_FAILURE);
               }
               while ((t=stack_top()) >= opr) /* pop low  */
                    printf("%c ", pop());     /* & print  */
               if (t == LEFT_PAR && opr == RIGHT_PAR)
                    (void) pop();      /* remove ( and )  */
               else if (opr == EOL)    /* end of parsing  */
                    exit(EXIT_SUCCESS);
               else
                    push(*p, opr);     /* otherwise, push */
          }
     }
}

