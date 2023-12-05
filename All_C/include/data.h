/* Created by skf on 23-11-21 */

#ifndef ALL_C_DATA_H
#define ALL_C_DATA_H
#include <stddef.h>

typedef union Elem{
    long unsigned num_uint64;
    long num_int64;
    double num_float64;
    void *ptr;
    char str;
} Elem;

#endif /*ALL_C_DATA_H */
