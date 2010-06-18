#include <stdio.h>
#include <stdlib.h>

#include "array.h"

SGbool dump(SGArray* array, void* item, void* data, size_t i)
{
    printf("%d: %d\n", i, *(int*)item);
    return SG_TRUE;
}

int main()
{
    SGArray* array = sgArrayCreate(sizeof(int));

    int i = 0;
    sgArrayAppend(array, &i); i++;
    sgArrayAppend(array, &i); i++;
    sgArrayAppend(array, &i); i++;

    sgArrayAppend(array, &i); i++;
    sgArrayAppend(array, &i); i++;
    sgArrayAppend(array, &i); i++;

    sgArrayEach(array, NULL, dump);
    printf("----------\n");
    sgArrayRemoveSlice(array, 1, 3);
    sgArrayEach(array, NULL, dump);
    printf("----------\n");
    sgArrayRemoveIndex(array, 2);
    sgArrayEach(array, NULL, dump);

    sgArrayDestroy(array);

    return 0;
}
