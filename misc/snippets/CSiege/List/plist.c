#include "plist.h"
#include "list.h"
#include <siege/common.h>

#include <stdlib.h>
#include <stddef.h>

SGbool SG_EXPORT _cbListEach(SGList* list, void* item, void* data, size_t i)
{
    SGPItem* pitem = (SGPItem*) item;

    SGbool SG_EXPORT (*cb)(SGPList* list, void* item, void* data, size_t i, float p) = ((void**)data)[1];

    return cb(list, pitem->item, ((void**)data)[0], i, pitem->priority);
}

SGPList* sgPListCreate(SGenum flags)
{
    SGPList* plist = sgListCreate();
    plist->internal.ui = flags;
    return plist;
}
void sgPListDestroy(SGPList* list)
{
    size_t i;
    for(i = 0; i < list->numitems; i++)
        free(list->items[i]);
    sgListDestroy(list);
}
void sgPListEach(SGPList* list, void* data, SGbool SG_EXPORT (*cb)(SGPList* list, void* item, void* data, size_t i, float p))
{
    void* tuple[2];
    tuple[0] = data;
    tuple[1] = cb;

    sgListEach(list, tuple, _cbListEach);
}
void sgPListAdd(SGPList* list, float p, void* item)
{
    SGPItem* pi = malloc(sizeof(SGPItem));
    pi->priority = p;
    pi->item = item;

    size_t i;
    SGbool op;
    for(i = 0; i < list->numitems; i++)
    {
        if(list->internal.ui & SG_PLIST_GT)
            op = ((SGPItem*)list->items[i])->priority > p;
        else if(list->internal.ui & SG_PLIST_GEQ)
            op = ((SGPItem*)list->items[i])->priority >= p;
        else if(list->internal.ui & SG_PLIST_LT)
            op = ((SGPItem*)list->items[i])->priority < p;
        else// if(flags & SG_PLIST_LEQ)
            op = ((SGPItem*)list->items[i])->priority <= p;
         // use:
         //     < to have new values with same priority go last (same priority: old value more important)
         //     > to reverse
        if(op)
        {
            sgListInsert(list, i, pi);
            return;
        }
    }

    //if(i == list->numitems) // the return handles this
    sgListAppend(list, pi);
}
void sgPListRemoveIndex(SGPList* list, size_t i)
{
    sgPListRemoveSlice(list, i, i + 1);
}
void sgPListRemoveSlice(SGList* list, size_t i1, size_t i2)
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

    size_t i;
    for(i = i1; i < i2; i++)
        free(list->items[i]);

    sgListRemoveSlice(list, i1, i2);
}
void sgPListRemoveItem(SGPList* list, void* item)
{
    SGPItem* pitem;
    size_t i;
    for(i = 0; i < list->numitems; i++)
    {
        pitem = (SGPItem*)list->items[i];
        if(pitem->item == item)
        {
            sgPListRemoveIndex(list, i);
            return;
        }
    }
}
void sgPListRemovePriority(SGPList* list, float p)
{
    sgPListRemovePSlice(list, p, p);
}
void sgPListRemovePSlice(SGPList* list, float p1, float p2)
{
    if(p1 > p2)
    {
        float tmp = p1;
        p1 = p2;
        p2 = tmp;
    }

    SGPItem* pitem;
    size_t i;
    ptrdiff_t i1 = -1;
    ptrdiff_t i2 = -1;
    for(i = 0; i < list->numitems; i++)
    {
        pitem = (SGPItem*)list->items[i];
        if(pitem->priority < p1) // didn't reach yet
            continue;
        if(pitem->priority > p2) // already past it
            break;

        if(i1 == -1)
            i1 = i;
        i2 = i;
    }

    sgPListRemoveSlice(list, i1, i2 + 1);
}
