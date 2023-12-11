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

