//
// Created by skf on 23-11-21.
//
#include "../include/link_list.h"


int main(){
     Elem a[12] = {0, 1, 2, 3, 4, 5, 5, 5, 7, 8, 9, 11};
     LinkNode *L1;
     L1 = createFromArray(a, 12, 0);
     printf("L1: ");
     displayList(L1);

     Elem b[8] = {3, 4, 6, 7, 8, 10, 11, 45};
     LinkNode *L2;
     L2 = createFromArray(b, 8, 0);
     printf("L2: ");
     displayList(L2);
}