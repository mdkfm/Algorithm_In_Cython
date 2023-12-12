# GNU C
&emsp;&emsp;Head file `gnuc.h` is a collection of some useful macros of GNU C.

## `RAII` and `auto_ptr`
&emsp;&emsp;Macro `RAII(func)` is a package of `__attribute__((cleanup(func)))`.
```c
#define RAII(func) __attribute__((cleanup(func)))
void free_func(class* ptr);
RAII(free_func) class p;
```
when the variable `p` is out of scope, `free(&p)` will be called automatically.

&emsp;&emsp;Macro `auto_ptr(class)` is `RAII(class##_raii) class##_class_ptr`.
```c
#define auto_ptr(class) RAII(class##_raii) class##_class_ptr

typedef class * const class##_class_ptr;
void class##_raii(class##_class_ptr *p);

auto_ptr(class) p = malloc(sizeof(class));
```
where for `class` we should define a corresponding const pinter type 
and realize the `class##_raii` function.

# Basic containers
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

## Stack
&emsp;&emsp;`List` is a normal stack.

&emsp;&emsp;Basic methods:
- `isEmpty`, `isFull`: check if the list is empty or full.
- `size`, `freeSise`: get the size or free space of the list.
- `get`: get the Element at index.
- `append`: append an Element at index.
- `pop`: pop the index Element.

## Deque
&emsp;&emsp;`Deque` is a ringed list.

&emsp;&emsp;Basic methods, similar with `Deque`, and extra:
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


## List
&emsp;&emsp;`List` is a list that supports slicing.

&emsp;&emsp;Basic methods:
- `set`: set the Element at index.
- `get`: get the Element at index.
- `write`: write the Elements of a list to the list according to slice.
- `view`: view the Elements of a list according to slice.

