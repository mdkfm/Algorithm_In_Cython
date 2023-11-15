#include<malloc.h>

#define DEBUG 0

void *basic_memset(void *s, int c, size_t n){
    size_t cnt = 0;
    unsigned char *schar = s;
    while(cnt < n){
        schar[cnt] = (unsigned char) c;
        cnt++;
    }
    return s;
}

void *index_memset(void *s, int c, size_t n){
    int i;
    size_t cnt = 0;
    unsigned long value = 0, clong = c & 0xFF;
    size_t k = sizeof(unsigned long);
    for(i = 0; i < k; i++){
        value = value | clong;
        clong = clong << 8;
    }

    // align
    int rest = k - (unsigned long)s % k;
    unsigned char *schar = s, cchar = c;
    while(cnt < rest){
        *schar++ = cchar;
        cnt++;
    }
#if DEBUG
    printf("%lu\n", cnt);
#endif
    // set 
    unsigned long *slong = schar;
    for(i = 0; cnt < n - 16; i++){
        slong[i] = value;
        slong[i + 1] = value;
        cnt += 16;
    }
    
    // rest
    schar = (unsigned char *)slong;
#if DEBUG
    printf("%lu\n", cnt);
#endif
    for(i = cnt - rest; cnt < n; i++){
        schar[i] = cchar;
        cnt++;
    }
#if DEBUG
    printf("%lu\n", cnt);
#endif
    return s;
}

void *pointer_memset(void *s, int c, size_t n){
    int i;
    size_t cnt = 0;
    unsigned long value = 0, clong = c & 0xFF;
    size_t k = sizeof(unsigned long);
    for(i = 0; i < k; i++){
        value = value | clong;
        clong = clong << 8;
    }

    // align
    int rest = k - (unsigned long)s % k;
    unsigned char *schar = s, cchar = c;
    while(cnt < rest){
        *schar++ = cchar;
        cnt++;
    }
#if DEBUG
    printf("%lu\n", cnt);
#endif
    // set 
    unsigned long *slong = schar;
    while(cnt < n - 16){
        *slong++ = value;
        *slong++ = value;
        cnt += 16;
    }
    
    // rest
    schar = (unsigned char *)slong;
#if DEBUG
    printf("%lu\n", cnt);
#endif
    while(cnt < n){
        *schar++ = cchar;
        cnt++;
    }
#if DEBUG
    printf("%lu\n", cnt);
#endif
    return s;
}

#define N 1000000

void main(){
    char s[N];
    s[N] = 1;
    for(int i = 0; i < 100000; i++){
        basic_memset(s, 0, N);
        index_memset(s, 0, N);
        pointer_memset(s, 0, N);
    }
    printf("%d %d\n", s[N-1], s[N]);
}