#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mcheck.h"

int main()
{
    //chkFunc = __FUNCTION__;

    size_t number;
    chkMemory* ptrs;
    char* ptr;
    size_t i;

    chkStart(4);

    ptr = malloc(4);
    printf("%.8X\n", *(unsigned int*)ptr);
    ptr = realloc(ptr, 4);
    printf("%.8X\n", *(unsigned int*)ptr);
    ptr = calloc(2, 4);
    printf("%.8X\n", *(unsigned int*)ptr);
    ptr[3] = 5;

    printf("Bounds check:\n");
    ptrs = chkBoundsM(&number);
    for(i = 0; i < number; i++)
        printf("FAIL %p %s:%d (%s)\n", ptrs[i].ptr, ptrs[i].file, ptrs[i].line, ptrs[i].func);

    printf("Leak check:\n");
    ptrs = chkEndM(&number);
    for(i = 0; i < number; i++)
        printf("FAIL %p %s:%d (%s)\n", ptrs[i].ptr, ptrs[i].file, ptrs[i].line, ptrs[i].func);

    return 0;
}
