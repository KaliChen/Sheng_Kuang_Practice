#include "bm.h"
#include "distseq.h"
#include "h_seq.h"
#include "kmp.h"
#include "lcs.h"
#include "max_reps.h"
#include "parcount.h"
#include "polish.h"
int main(){
    bm();
    distseq();
    //h_seq();
    //kmp();
    lcs();
    max_reps();
    parcount();
    polish();
    return 0;

}
