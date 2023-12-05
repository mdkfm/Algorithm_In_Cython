#include "../include/rlist.h"

void main(){
    RList *rlist = rlist_new(10);
    rlist_appendLeft(rlist, (Elem)(long)1);
    rlist_appendLeft(rlist, (Elem)(long)2);
    Elem buf;
    rlist_get(rlist, &buf, 0, 0);
    printf("%ld\n", buf.num_int64);
    rlist_display(rlist);
}