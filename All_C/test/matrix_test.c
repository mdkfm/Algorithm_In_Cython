//
// Created by skf on 23-12-14.
//

#include "../include/matrix.h"

int main(){
    Matrix *m = matrix_new(3, 3);
    double source[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8 ,9},
    };
    matrix_init(m, source);
    matrix_display(m);

    matrix_transpose(m);
    matrix_display(m);

    SparseMatrix *sm = sparseMatrix_new(3, 3);
    double sparse_source[3][3] = {
            {1, 0, 0},
            {2, 0, 0},
            {3, 9 ,0}
    };
    sparseMatrix_init(sm, sparse_source);
    sparseMatrix_display(sm, 1);

    sparseMatrix_transpose(sm);
    sparseMatrix_display(sm, 1);

    matrix_delete(m);
    sparseMatrix_delete(sm);
    return 0;
}
