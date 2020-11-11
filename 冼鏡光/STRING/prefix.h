#ifndef _prefix_H_
#define _prefix_H_

#define   LINE_SIZE      100  /* line buffer length       */
 
#define   STACK_BOTTOM     0  /* stack bottom indicator   */
#define   OPERAND          1  /* operand symbol indicator */
#define   OPERATOR         2  /* operator symbol indicator*/

/* ------------------------------------------------------ */
/*               stack management package                 */
/* ------------------------------------------------------ */

#define  STACK_SIZE    100    /* stack size               */

void prefix();
#endif
