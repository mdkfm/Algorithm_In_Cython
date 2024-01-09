//
// Created by skf on 24-1-9.
//

#define STATIC_LINK_DType int

#define STACK_DType size_t
#include "../container/stack.h"
#undef STACK_DType

#define DType STATIC_LINK_DType
#include "../basic/gnuc.h"
#include "../basic/template.h"

#define TClass Static_link

typedef struct Static_link Static_link;

struct Static_link{
    size_t maxsize, size;
    size_t front, rear;
    Stack *unused;
    FPtr_t display;
    DType *data;
};

DPtr(Static_link);

#ifndef ALL_C_STATIC_LINK_H
#define ALL_C_STATIC_LINK_H

#endif //ALL_C_STATIC_LINK_H
