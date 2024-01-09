//
// Created by skf on 24-1-6.
//

#include "macro.h"

#ifndef DType
#error No DType defined
#else

#define C(class_name) MCAT(class_name, DType) // class name
#define F(func_name) MCAT(Class, func_name) // func name, we should define Class before
#define SF(func_name) MCAT(TClass, func_name) // shared func name, we should define TClass before

#define FuncT_t F(FuncT_t)
#define FuncT F(funcT)
#define classFuncT(class_name, T) MCAT(MCAT(class_name, T), funcT)
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

static inline void displayUInt(unsigned int data) {
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
    unsigned int: displayUInt, \
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

/* $Begin basic compare function */
#include <string.h>
#define sign(X) ((X) > 0 ? 1 : ((X) == 0 ? 0 : -1))

static inline int cmpShort(short e0, short e1) {
    return sign(e0 - e1);
}

static inline int cmpInt(int e0, int e1) {
    return sign(e0 - e1);
}

static inline int cmpUInt(unsigned int e0, unsigned int e1) {
    return sign(e0 - e1);
}

static inline int cmpLong(long e0, long e1) {
    return sign(e0 - e1);
}

static inline int cmpULong(unsigned long e0, unsigned long e1) {
    return sign(e0 - e1);
}

static inline int cmpFloat(float e0, float e1) {
    return sign(e0 - e1);
}

static inline int cmpDouble(double e0, double e1) {
    return sign(e0 - e1);
}

static inline int cmpChar(char e0, char e1) {
    return sign(e0 - e1);
}

static inline int cmpString(char* e0, char* e1) {
    return strcmp(e0, e1);
}


#define CMP(X) _Generic((X)0, \
    short: cmpShort, \
    int: cmpInt, \
    unsigned int: cmpUInt, \
    long: cmpLong, \
    unsigned long: cmpULong, \
    float: cmpFloat, \
    double: cmpDouble, \
    char: cmpChar, \
    char*: cmpString, \
    default: NULL \
)
#endif