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

struct SparseMatrixItem{
    size_t row;
    size_t column;
    Elem value;
};

typedef struct SparseMatrix{
    size_t row;
    size_t column;
    size_t length;
    struct SparseMatrixItem *data;
} SparseMatrix;

Matrix * matrix_new(size_t row, size_t column);
void matrix_delete(Matrix *m);

static inline Elem matrix_get(Matrix const*const m, long const row, long const column){
    size_t const row_max = m->row, column_max = m->column;
    if(unlikely(row >= row_max || column >= column_max)){
        raise_error("index out of range", __FILE__, __func__, __LINE__);
    }
    return m->data[row * column_max + column];
}

#define MATRIX_SET_DEBUG 0
static inline void matrix_set(Matrix *const m, size_t const row, size_t const column, Elem const value){
#if MATRIX_SET_DEBUG
    printf("set %lu %lu %lf\n", row, column, value.num_float64);
#endif
    size_t const row_max = m->row, column_max = m->column;
    if(unlikely(row >= row_max || column >= column_max)){
        raise_error("index out of range", __FILE__, __func__, __LINE__);
    }
    m->data[row * m->column + column] = value;
}

void matrix_init(Matrix * m, Elem source[m->row][m->column]);
void matrix_display(Matrix const * const m);
void matrix_transpose(Matrix *const m);

SparseMatrix *sparseMatrix_new(size_t row, size_t column);
void sparseMatrix_delete(SparseMatrix *m);
void sparseMatrix_init(SparseMatrix * m, Elem source[m->row][m->column]);
void sparseMatrix_transpose(SparseMatrix * const m);

void matrix_initFromSparseMatrix(Matrix const * const m, SparseMatrix * const sm);

void sparseMatrix_display(SparseMatrix const * const m, int const display_zero);
#endif /* ALL_C_MATRIX_H */
