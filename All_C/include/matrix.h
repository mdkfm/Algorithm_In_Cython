/* Created by skf on 23-12-4. */

#ifndef ALL_C_MATRIX_H
#define ALL_C_MATRIX_H

#include "data.h"
#include <stdlib.h>

typedef struct Matrix{
    size_t row;
    size_t column;
    Elem * data;
} Matrix;


Matrix * matrix_new(size_t row, size_t column);
void matrix_delete(Matrix *m);

static inline Elem matrix_get(Matrix *m, size_t row, size_t column){
    row %= m->row;
    column %= m->column;
    return m->data[row * m->column + column];
}

static inline void matrix_set(Matrix *m, size_t row, size_t column, Elem value){
    row %= m->row;
    column %= m->column;
    m->data[row * m->column + column] = value;
}

void matrix_init(Matrix * m, Elem source[m->row][m->column]);

#endif /* ALL_C_MATRIX_H */
