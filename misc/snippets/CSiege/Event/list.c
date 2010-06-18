#include "list.h"
#include <siege/common.h>

#include <stdlib.h>
#include <string.h>

SGList* sgListCreate(void)
{
    SGList* list = malloc(sizeof(SGList));
    list->numitems = 0;
    list->items = NULL;
    return list;
}
void sgListDestroy(SGList* list)
{
    free(list->items);
    free(list);
}
void sgListEach(SGList* list, void* data, SGbool (*cb)(SGList* list, void* item, void* data, size_t i))
{
    size_t i;
    for(i = 0; i < list->numitems; i++)
        if(!cb(list, list->items[i], data, i))
            return;
}
void sgListAppend(SGList* list, void* item)
{
    list->items = realloc(list->items, (list->numitems + 1) * sizeof(void*));
    list->items[list->numitems] = item;
    list->numitems++;
}
void sgListInsert(SGList* list, size_t i, void* item)
{
    if(i >= list->numitems)
    {
        sgListAppend(list, item);
        return;
    }

    list->items = realloc(list->items, (list->numitems + 1) * sizeof(void*));
    memmove(list->items + i + 1, list->items + i, (list->numitems - i) * sizeof(void*));
    list->items[i] = item;
    list->numitems++;
}
void sgListRemoveIndex(SGList* list, size_t i)
{
    sgListRemoveSlice(list, i, i + 1);
}
void sgListRemoveSlice(SGList* list, size_t i1, size_t i2)
{
    if(i1 > list->numitems)
        return;
    if(i2 > list->numitems)
        return;

    if(i1 > i2)
    {
        size_t tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    memmove(list->items + i1, list->items + i2, (list->numitems - i2) * sizeof(void*));
    list->items = realloc(list->items, (list->numitems - (i2 - i1)) * sizeof(void*));
    list->numitems -= (i2 - i1);
}
void sgListRemoveItem(SGList* list, void* item)
{
    size_t i;
    for(i = 0; i < list->numitems; i++)
        if(list->items[i] == item)
        {
            sgListRemoveIndex(list, i);
            return;
        }
}
