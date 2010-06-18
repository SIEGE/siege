#include "array.h"
#include <siege/common.h>

#include <stdlib.h>
#include <string.h>

SGArray* sgArrayCreate(size_t isize)
{
    SGArray* array = malloc(sizeof(SGArray));
    array->length = 0;
    array->ptr = NULL;
    array->isize = isize;
    return array;
}
void sgArrayDestroy(SGArray* array)
{
    free(array->ptr);
    free(array);
}
void* sgArrayIndex(SGArray* array, size_t i)
{
    if(i > array->length)
        return SG_ARRAY_ERR; // we should throw an error here, later

    return array->ptr + i * array->isize;
}
SGArray* sgArrayCopy(SGArray* array)
{
    SGArray* newarray = malloc(sizeof(SGArray));
    newarray->length = array->length;
    newarray->ptr = malloc(array->length * array->isize);
    memcpy(newarray->ptr, array->ptr, array->length * array->isize);
    newarray->isize = array->isize;
    return newarray;
}
SGArray* sgArrayCopySlice(SGArray* array, size_t i1, size_t i2)
{
    if(i1 > array->length)
        return NULL;
    if(i2 > array->length)
        return NULL;

    if(i1 > i2)
    {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    SGArray* newarray = malloc(sizeof(SGArray));
    newarray->length = i2 - i1;
    newarray->ptr = malloc((i2 - i1) * array->isize);
    memcpy(newarray->ptr + i1, array->ptr + i1, (array->length - i2) * array->isize);
    newarray->isize = array->isize;
    return newarray;
}
void sgArrayEach(SGArray* array, void* data, SGbool (*cb)(SGArray* array, void* item, void* data, size_t i))
{
    size_t i;
    for(i = 0; i < array->length; i++)
        if(!cb(array, array->ptr + i*array->isize, data, i))
            return;
}
void sgArrayAppend(SGArray* array, void* item)
{
    array->ptr = realloc(array->ptr, (array->length + 1) * array->isize);
    memcpy(array->ptr + array->length * array->isize, item, array->isize);
    array->length++;
}
void sgArrayInsert(SGArray* array, size_t i, void* item)
{
    if(i >= array->length)
    {
        sgArrayAppend(array, item);
        return;
    }

    array->ptr = realloc(array->ptr, (array->length + 1) * array->isize);
    memmove(array->ptr + (i + 1) * array->isize, array->ptr + i * array->isize, (array->length - i) * array->isize);
    memcpy(array->ptr + i * array->isize, item, array->isize);
    array->length++;
}
void sgArrayRemoveIndex(SGArray* array, size_t i)
{
    sgArrayRemoveSlice(array, i, i + 1);
}
void sgArrayRemoveSlice(SGArray* array, size_t i1, size_t i2)
{
    if(i1 > array->length)
        return;
    if(i2 > array->length)
        return;

    if(i1 > i2)
    {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    memmove(array->ptr + i1 * array->isize, array->ptr + i2 * array->isize, (array->length - i2) * array->isize);
    array->ptr = realloc(array->ptr, (array->length - (i2 - i1)) * array->isize);
    array->length -= (i2 - i1);
}
void sgArrayRemoveItem(SGArray* array, void* item)
{
    size_t i;
    for(i = 0; i < array->length; i++)
        if(memcmp(array->ptr + i * array->isize, item, array->isize) == 0)
        {
            sgArrayRemoveIndex(array, i);
            return;
        }
}
