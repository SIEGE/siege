#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <siege/common.h>

#include <stddef.h>

#define SG_ARRAY_ERR ((void*)-1)

union _SGArrayInternal
{
    void* ptr;
    SGuint ui;
    SGulong ul;
} ;

typedef struct SGArray
{
    size_t length;
    SGubyte* ptr;
    size_t isize;
    union _SGArrayInternal internal;
} SGArray;

SGArray* sgArrayCreate(size_t isize);
void sgArrayDestroy(SGArray* array);
void* sgArrayIndex(SGArray* array, size_t i);
SGArray* sgArrayCopy(SGArray* array);
SGArray* sgArrayCopySlice(SGArray* array, size_t i1, size_t i2);
void sgArrayEach(SGArray* array, void* data, SGbool SG_EXPORT (*cb)(SGArray* array, void* item, void* data, size_t i));
void sgArrayAppend(SGArray* array, void* item);
void sgArrayInsert(SGArray* array, size_t i, void* item);
void sgArrayRemoveIndex(SGArray* array, size_t i);
void sgArrayRemoveSlice(SGArray* array, size_t i1, size_t i2);
void sgArrayRemoveItem(SGArray* array, void* item);

#endif // __ARRAY_H__
