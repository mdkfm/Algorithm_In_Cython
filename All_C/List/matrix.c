#include "../include/data.h"
#include <malloc.h>

/* TODO: more usage similar with numpy */

typedef struct Matrix{
    Elem * data;
    size_t row;
    size_t column;
} Matrix;


Matrix * newMatrix(size_t row, size_t column){
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

    new->data = data;
    new->row = row;
    new->column = column;
    return new;
}

void deleteMatrix(Matrix *m){
    free(m->data);
    free(m);
}

void initMatrix(Matrix * m, Elem source[m->row][m->column]){
    int i, j, row = m->row, column = m->column;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            m->data[i * column + j] = source[i][j];
        }
    }
}

Elem getElem(Matrix *m, size_t row, size_t column){
    row %= m->row;
    column %= m->column;
    return m->data[row * m->column + column];
}

void setElem(Matrix *m, size_t row, size_t column, Elem value){
    row %= m->row;
    column %= m->column;
    m->data[row * m->column + column] = value;
}