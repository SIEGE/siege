#ifndef __SIEGE_UTIL_LIST_H__
#define __SIEGE_UTIL_LIST_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

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

SGList* SG_EXPORT sgListCreate(void);
void SG_EXPORT sgListDestroy(SGList* list);
void SG_EXPORT sgListEach(SGList* list, void* data, SGbool SG_EXPORT (*cb)(SGList* list, void* item, void* data, size_t i));
void SG_EXPORT sgListAppend(SGList* list, void* item);
void SG_EXPORT sgListInsert(SGList* list, size_t i, void* item);
void SG_EXPORT sgListRemoveIndex(SGList* list, size_t i);
void SG_EXPORT sgListRemoveSlice(SGList* list, size_t i1, size_t i2);
void SG_EXPORT sgListRemoveItem(SGList* list, void* item);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LIST_H__
