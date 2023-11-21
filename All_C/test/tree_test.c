//
// Created by skf on 23-11-21.
//
#include "../include/tree.h"

int main(){
    int i;
    int adj[6][6] = {
            {0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
    };
    int **test = (int **)malloc(6 * sizeof(int *));
    for (i = 0; i < 6; i++) {
        test[i] = adj[i];
    }
    Elem value[] = {0, 1, 2, 3, 4, 5};

    Tree *tree = createTreeFromAdj(test, value, 6);

    Queue* q1 = preOrder(tree);
    displayQueue(q1);

    Queue* q2 = postOrder(tree);
    displayQueue(q2);

    Queue* q3 = rightPostOrder(tree);
    displayQueue(q3);

    Queue* q4 = levelOrder(tree);
    displayQueue(q4);
    return 0;
}