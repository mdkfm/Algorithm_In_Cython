#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct {
    int * data;
    int length;
    int listsize;
} SqList;

SqList * empty_list(int listsize){
    // create a empty list with listsize
    SqList * L;
    L = (SqList *)malloc(sizeof(SqList));
    L->data = (int *)malloc(listsize * sizeof(int));
    L->length = 0;
    L->listsize = listsize;
    return L;
}

void write_to_list(SqList *L, int data[], int n){
    if(n > L->listsize){
        printf("ValueError: The length of data is over bound!");
        printf("The length is %d, the list size is %d. \n", n, L->listsize);
        exit(1);
    }
    else{
        int i = 0, k = 0;
        while (i < n){
            L->data[k++] = data[i++];
        }
        L->length = k;
    }
}

void destory_list(SqList *L){
    free(L->data);
    free(L);
}

int is_empty(SqList *L){
    return (L->length == 0);
}

int is_full(SqList *L){
    return (L->length == L->listsize);
}

void display_list(SqList * L){
    // display the elements in L->data
    int length = L->length;
    for(int i = 0; i < length; i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

int get_element_by_index(SqList *L, int index){
    // int i: the index
    if(index < 0 || index > L->length - 1){
        printf("IndexError: The index must >= 0 and < the length of list.");
        printf("The index is %d, the length is %d. \n", index, L->length);
        exit(1);
    }
    int e;
    e = L->data[index];
    return e;
}

int search_element(SqList *L, int e){
    // int e: the searched element
    int i = 0, length = L->length, *p = L->data;
    while(i < length && *p != e){
        i++; p++;
    }
    if (i == length){
        printf("ValueError: The element e is not in list! \n");
        exit(1);
    }
    else{
        return i;
    }
}

int list_insert(SqList *L, int i, int e){
    // insert element e into L at index i

    // examine the free space of L->data
    if(is_full(L)){
        printf("InserError: The list is full! \n");
        exit(1);
    }
    //examine the index i
    if(i < 0 || i > L->length - 1){
        printf("IndexError: The index i is too small or too big!");
        return 0;
    }
    int j;
    // move the last elements
    for(j = L->length; j > i; j--){
        L->data[j] = L->data[j - 1];
    }
    // save e
    L->data[i] = e;
    L->length++;
    return 1;
}

int list_pop(SqList *L, int index){
    // pop the element at index i
    //examine the index i
    if(index < 0 || index > L->length - 1){
        printf("IndexError: The index must >= 0 and < the length of list.");
        printf("The index is %d, the length is %d. \n", index, L->length);
        exit(1);
    }
    int e = L->data[index], j;
    for(j = index; j < L->length - 1; j++){
        L->data[j] = L->data[j+1];
    }
    L->length--;
    return e;
}

int main(){
    SqList *L;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int search_element(SqList * L, int n);
    L = empty_list(20);
    write_to_list(L, a, 10);
    list_insert(L, 2, 4);
    printf("%d\n", search_element(L, 4));
    return 0;
}

