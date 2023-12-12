/* Created by skf on 23-12-4. */

#ifndef ALL_C_MATRIX_H
#define ALL_C_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "data.h"
#include "gnuc.h"


typedef struct Matrix{
    size_t row;
    size_t column;
    Elem * data;
} Matrix;


Matrix * matrix_new(size_t row, size_t column);
void matrix_delete(Matrix *m);

static inline Elem matrix_get(Matrix *m, long row, long column){
    size_t const row_max = m->row, column_max = m->column;
    if(unlikely(row >= row_max || column >= column_max)){
        raise_error("index out of range");
    }
    return m->data[row * column_max + column];
}

static inline void matrix_set(Matrix *m, size_t row, size_t column, Elem value){
    size_t const row_max = m->row, column_max = m->column;
    if(unlikely(row >= row_max || column >= column_max)){
        raise_error("index out of range");
    }
    m->data[row * m->column + column] = value;
}

void matrix_init(Matrix * m, Elem source[m->row][m->column]);
void matrix_display(Matrix const * const m);

#endif /* ALL_C_MATRIX_H */
