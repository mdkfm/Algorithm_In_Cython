# Basic containers
&emsp;&emsp;`list`, `rlist`(ringed list), `link`, 
`bitree`, `stree`(search tree), `matrix`.

## Link
&emsp;&emsp;`Link` is a bidirectional linked list.

&emsp;&emsp;Basic methods:
- `appendList`: append the Elements of a list to the right end of the link.
- `getLeft`, `getRight`: get the Element from left or right end.
- `insertLeft`, `insertRight`: add an Element at index from left or right end.
- `insertLeftFirst`, `insertRightFirst`: add an Element to left or right end.
- `popLeft`, `popRight`: pop the index Element from left or right end.
- `popLeftFirst`, `popRightFirst`: pop the left or right end Element.
- `search`: search the Element and return the index.
- `deleteAll`: delete all Elements equal to deleted.

## List
&emsp;&emsp;`List` is a normal list.

&emsp;&emsp;Basic methods:
- `isEmpty`, `isFull`: check if the list is empty or full.
- `size`, `freeSise`: get the size or free space of the list.
- `get`: get the Element at index.
- `append`: append an Element at index.
- `pop`: pop the index Element.

## RList
&emsp;&emsp;`RList` is a ringed list.

&emsp;&emsp;Basic methods, similar with `List`, and extra:
- `appendList`: append the Elements of a list to the right end of the rlist.
- `appendLeft`, `appendRight`: append an Element to left or right end.
- `popLeft`, `popRight`: pop the left or right end Element.


## Heap
&emsp;&emsp;`Heap` is a heap.
```c
typedef struct Heap{
    /* Complete Bi-Tree */
    Elem *data; /* use array to store the data */
    int (*cmp)(Elem const e0, Elem const e1);
    /* compare function, if e0 > e1 return 1,
     * this max-heap is constructed according to cmp */
    size_t size;
    size_t maxsize;
} Heap;
```

&emsp;&emsp;Basic methods:
- `top`: get the top Element.
- `pop`: pop the top Element.
- `append`: append an Element to the heap.
- `increase`: increase the value of the index Element.

