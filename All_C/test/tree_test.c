/* Created by skf on 23-11-21. */

#include "../include/stack.h"
#include "../include/tree.h"

int main(){
    int i;
    long adj[6][6] = {
            {0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0}
    };
    long **test = (long **)malloc(6 * sizeof(long *));
    for (i = 0; i < 6; i++) {
        test[i] = adj[i];
    }
    Elem value[] = {0, 1, 2, 3, 4, 5};

    RAII(tree_raii) Tree *tree = tree_new();
    tree_initFromAdj(tree, test, value, 6);

    RAII(stack_raii) Stack* q1 = stack_new(6);
    tree_preOrder(tree, q1);
    stack_display(q1);

    RAII(stack_raii) Stack* q2 = stack_new(6);
    tree_postOrder(tree, q2);
    stack_display(q2);

    RAII(stack_raii) Stack* q3 = stack_new(6);
    tree_rightPostOrder(tree, q3);
    stack_display(q3);

    RAII(stack_raii) Stack* q4 = stack_new(6);
    tree_levelOrder(tree, q4);
    stack_display(q4);
    return 0;
}