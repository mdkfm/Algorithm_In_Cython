#include <stdio.h>

#include "../include/matrix.h"


/* TODO: more usage similar with numpy */

Matrix * matrix_new(size_t row, size_t column){
    if(row * column < row){
        // size_t overflow
        return NULL;
    }

    Matrix * new = (Matrix *) malloc(sizeof(Matrix));
    if(new == NULL)
        return NULL;

    Elem * data = (Elem *) calloc(row * column, sizeof(Elem));
    if(data == NULL){
        free(new);
        return NULL;
    }

    new->row = row;
    new->column = column;
    new->data = data;
    return new;
}

void matrix_delete(Matrix *m){
    free(m->data);
    free(m);
}


void matrix_init(Matrix * m, Elem source[m->row][m->column]){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            matrix_set(m, i, j, source[i][j]);
        }
    }
}

void matrix_display(Matrix const * const m){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            printf("%lf ", matrix_get(m, i, j).num_float64);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_transpose(Matrix *const m){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = i + 1; j < column; j++){
            Elem tmp = matrix_get(m, i, j);
            matrix_set(m, i, j, matrix_get(m, j, i));
            matrix_set(m, j, i, tmp);
        }
    }
}

SparseMatrix *sparseMatrix_new(size_t row, size_t column){
    if(row * column < row){
        // size_t overflow
        return NULL;
    }

    SparseMatrix * new = (SparseMatrix *) malloc(sizeof(SparseMatrix));
    if(new == NULL)
        return NULL;

    struct SparseMatrixItem * data = (struct SparseMatrixItem *) calloc(row * column, sizeof(struct SparseMatrixItem));
    if(data == NULL){
        free(new);
        return NULL;
    }

    size_t * row_index = (size_t *) calloc(row * column, sizeof(size_t));
    if(row_index == NULL){
        free(data);
        free(new);
        return NULL;
    }

    size_t * column_index = (size_t *) calloc(row * column, sizeof(size_t));
    if(column_index == NULL){
        free(data);
        free(row_index);
        free(new);
        return NULL;
    }

    new->row = row;
    new->column = column;
    new->length = 0;
    new->data = data;
    return new;
}

void sparseMatrix_delete(SparseMatrix *m){
    free(m->data);
    free(m);
}

void sparseMatrix_init(SparseMatrix * m, Elem source[m->row][m->column]){
    int i, j, row = m->row, column = m->column, length = m->length;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            Elem elem = source[i][j];
            if(elem.num_float64 != 0){
                m->data[length] = (struct SparseMatrixItem){i, j, elem};
                length++;
            }
        }
    }
    m->length = length;
}

int sparseMatrixItem_cmp(const void *a, const void *b){
    struct SparseMatrixItem *item_a = (struct SparseMatrixItem *) a;
    struct SparseMatrixItem *item_b = (struct SparseMatrixItem *) b;
    if(item_a->row == item_b->row){
        return item_a->column - item_b->column;
    }
    return item_a->row - item_b->row;
}

void sparseMatrix_transpose(SparseMatrix * const m){
    struct SparseMatrixItem *item = m->data;
    for(int i = 0; i < m->length; i++, item++){
        size_t tmp = item->row;
        item->row = item->column;
        item->column = tmp;
    }
    qsort(m->data, m->length, sizeof(struct SparseMatrixItem), sparseMatrixItem_cmp);
}

void matrix_initFromSparseMatrix(Matrix const * const m, SparseMatrix * const sm){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            matrix_set(m, i, j, (Elem){0});
        }
    }
    struct SparseMatrixItem *item = sm->data;
    for(i = 0; i < sm->length; i++, item++){
        matrix_set(m, item->row, item->column, item->value);
    }
}

void sparseMatrix_display(SparseMatrix const * const m, int const display_zero){
    if(display_zero) {
        Matrix *matrix = matrix_new(m->row, m->column);
        matrix_initFromSparseMatrix(matrix, m);
        matrix_display(matrix);
        matrix_delete(matrix);
        return;
    }
    for(int i = 0; i < m->length; i++){
        printf("%lu %lu %lf\n", m->data[i].row, m->data[i].column, m->data[i].value.num_float64);
    }
    printf("\n");
}