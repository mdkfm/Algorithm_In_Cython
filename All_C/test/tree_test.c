/* Created by skf on 23-11-21. */

#include "../include/rlist.h"
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

    Tree *tree = tree_new();
    tree_initFromAdj(tree, test, value, 6);

    Queue* q1 = tree_preOrder(tree);
    queue_display(q1);

    Queue* q2 = tree_postOrder(tree);
    queue_display(q2);

    Queue* q3 = tree_rightPostOrder(tree);
    queue_display(q3);

    Queue* q4 = tree_levelOrder(tree);
    queue_display(q4);

    queue_delete(q1);
    queue_delete(q2);
    queue_delete(q3);
    queue_delete(q4);
    return 0;
}