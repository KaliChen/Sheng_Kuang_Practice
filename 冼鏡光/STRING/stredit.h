#ifndef _stredit_H_
#define _stredit_H_

#define   INSERT_COST       1 /* cost for inserting a char*/
#define   DELETE_COST       1 /* cost for deleting a char */
#define   EXCHANGE_COST     2 /* cost for exchanging chars*/

#define   MIN(x, y, z)      ((x) <= (y) ?                   \
                                 ((x) <= (z) ? (x) : (z)) : \
                                 ((y) <= (z) ? (y) : (z))   \
                            )
#define   MAX(x, y)   ((x) >= (y) ? (x) : (y))
#define   SWAP(a, b)   { t = a; a = b; b = t; }
void stredit();
#endif
