#ifndef __LIST_H__
#define __LIST_H__

#include <siege/common.h>

#include <stddef.h>

union _SGListInternal
{
    void* ptr;
    SGuint ui;
    SGulong ul;
} ;

typedef struct SGList
{
    size_t numitems;
    void** items;
    union _SGListInternal internal;
} SGList;

SGList* sgListCreate(void);
void sgListDestroy(SGList* list);
void sgListEach(SGList* list, void* data, SGbool SG_EXPORT (*cb)(SGList* list, void* item, void* data, size_t i));
void sgListAppend(SGList* list, void* item);
void sgListInsert(SGList* list, size_t i, void* item);
void sgListRemoveIndex(SGList* list, size_t i);
void sgListRemoveSlice(SGList* list, size_t i1, size_t i2);
void sgListRemoveItem(SGList* list, void* item);

#endif // __LIST_H__
