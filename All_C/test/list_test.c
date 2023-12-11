//
// Created by skf on 23-12-10.
//

#include "../include/list.h"

int main(){
    long s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    List *const list = list_new(10);
    list_write(list, (ListSlice){0, 0, 1}, (Elem*)s, 10);
    list_display(list);

    List *const view = list_view(list, (ListSlice){0, 0, -3});
    list_set(view, 2, (Elem){.num_int64 = 100});
    list_display(view);

    list_write(view, (ListSlice){0, 0, 1}, (Elem*)s, 10);
    list_display(view);
    list_display(list);

    list_delete(list);
}