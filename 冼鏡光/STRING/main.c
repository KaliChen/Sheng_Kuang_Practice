#include "bm.h"
#include "distseq.h"
#include "h_seq.h"
#include "kmp.h"
#include "lcs.h"
#include "max_reps.h"
#include "parcount.h"
#include "polish.h"
#include "prefix.h"
#include "rh_seq.h"
#include "sub_seq.h"

int main(){
    bm();
    distseq();
    //h_seq();
    //kmp();
    lcs();
    max_reps();
    parcount();
    polish();
    prefix();
    rh_seq();
    sub_seq();
    return 0;

}
