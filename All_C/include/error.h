//
// Created by skf on 23-12-12.
//

#ifndef ALL_C_ERROR_H
#define ALL_C_ERROR_H
#include <stdio.h>
#include <stdlib.h>

#define raise_error(msg, file, func, line) {\
    fprintf(stderr, "Error: Raised at file: %s, func: %s  line: %d\n", file, func, line);\
    fprintf(stderr, "   Error message: %s\n", msg);\
    exit(EXIT_FAILURE);\
}\

#endif //ALL_C_ERROR_H
