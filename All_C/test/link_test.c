/* Created by skf on 23-11-21. */
#include "../include/link.h"


int main(){
    long a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
    Link *L1 = link_new();
    link_initFromArray(L1, (Elem *)a, 12, 0);
    link_insertFirstLeft(L1, (Elem){.num_int64 = 100});
    link_display(L1);
    link_deleteAll(L1, (Elem){.num_int64 = 5});
    link_display(L1);
    link_insertRight(L1, 1, (Elem){.num_int64 = 5});
    link_display(L1);
}