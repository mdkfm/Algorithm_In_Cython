#include<malloc.h>
#include<sys/time.h>

typedef long data_t;

typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len){
    /* Allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    data_t *data = NULL;
    if(result == NULL)
        // malloc failed
        return NULL;
    result->len = len;
    if(len > 0){
        data = (data_t *) calloc(len, sizeof(data_t));
        if(data == NULL){
            free((void *) result);
            return NULL;
        }
    }
    result->data = data;
    return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest){
    if(index < 0 || index >= v->len)
        return 0;
    *dest = v->data[index];
    return 1;
}

long vec_length(vec_ptr v){
    return v->len;
}

data_t *get_vec_start(vec_ptr v){
    return v->data;
}

#define IDENT 1
#define OP *

void combine1(vec_ptr v, data_t *dest){
    // optimization base
    long i;

    *dest = IDENT;
    for(i = 0; i < vec_length(v); i++){
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine2(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v); 
    // value of vec_length will not change
    // but if we put it in test-ecpr in for-loop
    // the compiler does not know it and will not optimize automatically 

    *dest = IDENT;

    for(i = 0; i < length; i++){
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

void combine3(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    // every times calling get_vec_element checks the index not beyond bounds
    // this is inefficient

    // in fact, this does not matter, because the if branch is predictable 

    for(i = 0; i < length ; i++){
        *dest = *dest OP data[i];
    }
}

void combine4(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    // dest points at memory
    // write in memory in every loop is inefficient

    // use a temporary variable, compiler will sotre it in register

    for(i = 0; i < length ; i++){
        acc = acc OP data[i];
    }
    *dest = acc;
}

// ******************* loop unroll ******************* //
// lopp with loop unroll and more tmp variables could preform better until cpu limit
// but it will change the calculation order, this might change the result

void combine5(vec_ptr v, data_t *dest){
    // 2 * 1 unroll
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    // branch jmp is inefficient, we could unroll the loop

    for(i = 0; i < length - 1; i += 2){
        acc = acc OP data[i];
        acc = acc OP data[i + 1];
    }

    for(; i < length; i++){
        acc = acc OP data[i];
    }
    *dest = acc;
}

void combine6(vec_ptr v, data_t *dest){
    // 2 * 2 unroll
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;

    // use more temporary variables
    for(i = 0; i < length - 1; i += 2){
        acc0 = acc0 OP data[i];
        acc1 = acc1 OP data[i + 1];
    }

    for(; i < length; i++){
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}


void combine7(vec_ptr v, data_t *dest){
    // 2 * 1a unroll
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    // different calculation combination might have different result
    // but it could be more effective
    // because the num of opratioins in main path decreases 

    // the efficiency of this method is same as 2 * 2 unroll 
    for(i = 0; i < length - 1; i += 2){
        acc = acc OP (data[i] OP data[i + 1]);
    }

    for(; i < length; i++){
        acc = acc OP data[i];
    }
    *dest = acc;
}

void clock(void (*func)(), vec_ptr x, data_t *result, char flag){
    struct timeval start, end;
    long timeuse;

    gettimeofday(&start, NULL);
    func(x, result);
    gettimeofday(&end, NULL);
    timeuse = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("time%c = %08ld us\n", flag, timeuse);
}

void main(){
    vec_ptr x = new_vec(1000000);
    long result = 0;
    int i;
    for(i = 0; i < 1000000; i++){
        x->data[i] = i;
    }

    struct timeval start, end;
    long timeuse;

    clock(&combine1, x, &result, '1');
    clock(&combine2, x, &result, '2');
    clock(&combine3, x, &result, '3');
    clock(&combine4, x, &result, '4');
    clock(&combine5, x, &result, '5');
    clock(&combine6, x, &result, '6');
    clock(&combine7, x, &result, '7');
}