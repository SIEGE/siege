#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ARR_REMOVE(arr, len, i)                                                     \
    {                                                                               \
        memmove(&(arr)[(i)], &(arr)[(i)+1], ((len) - ((i) + 1)) * sizeof(*(arr)));  \
        (arr) = realloc((arr), (--(len)) * sizeof(*(arr)));                         \
    }

#define ARR_ADD(arr, len, x)                                    \
    {                                                           \
        (arr) = realloc((arr), ((len) + 1) * sizeof(*(arr)));   \
        (arr)[(len)++] = (x);                                   \
    }

#define BOUNDS(from, to, at)                    \
    (((from) < (to))                            \
        ? (((from) < (at)) && ((at) < (to)))  \
        : (((to) < (at)) && ((at) < (from))))

#endif // __COMMON_H__
