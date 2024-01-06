//
// Created by skf on 24-1-6.
//

#ifndef DType
#error No DType defined
#else
#define CAT(A, B) A##_##B
#define CCAT(A, B) CAT(A, B)
#define C(class) CCAT(class, DType) // class name
#define F(func_name) CCAT(Class, func_name) // func name, we should define Class before
#define SF(func_name) CCAT(TClass, func_name) // shared func name, we should define TClass before
#endif


#ifndef ALL_C_TEMPLATE_H
#define ALL_C_TEMPLATE_H
#include <stdio.h>
#include "gnuc.h"

/* $Begin basic display function */
static inline void displayShort(short data) {
    printf("%hd", data);
}

static inline void displayInt(int data) {
    printf("%d", data);
}

static inline void displatUInt(unsigned int data) {
    printf("%u", data);
}

static inline void displayLong(long data) {
    printf("%ld", data);
}

static inline void displayULong(unsigned long data) {
    printf("%lu", data);
}

static inline void displayFloat(float data) {
    printf("%f", data);
}

static inline void displayDouble(double data) {
    printf("%lf", data);
}

static inline void displayChar(char data) {
    printf("%c", data);
}

static inline void displayString(char* data) {
    printf("%s", data);
}

static inline void displayPointer(void* data) {
    printf("%p", data);
}

#define DISPLAY(X) _Generic((X)0, \
    short: displayShort, \
    int: displayInt, \
    unsigned int: displatUInt, \
    long: displayLong, \
    unsigned long: displayULong, \
    float: displayFloat, \
    double: displayDouble, \
    char: displayChar, \
    char*: displayString, \
    void*: displayPointer,\
    default: NULL \
)

/* $End basic display function */
#endif