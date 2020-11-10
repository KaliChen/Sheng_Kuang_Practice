#ifndef _polish_H_
#define _polish_H_

#define   BOTTOM        '\0'  /* precedence of stack bot. */
#define   EOL           '\1'  /* precedence of end-of-line*/
#define   LEFT_PAR      '\2'  /* precedence of (          */
#define   RIGHT_PAR     '\3'  /* precedence of )          */
#define   PLUS_MINUS    '\4'  /* precedence of + and -    */
#define   MUL_DIV       '\5'  /* precedence of * and /    */

#define   EXIT_SUCCESS     1  /* remove it if ANSI C      */
#define   EXIT_FAILURE     0  /* remove it if ANSI C      */

#define  MAX_DEPTH  100
#define  BOTTOM     '\0'
static char  stack[MAX_DEPTH];/* operator stack           */
static char  code[MAX_DEPTH]; /* operator precedence stack*/
static int   top;             /* stack pointer            */

int polish();
#endif
