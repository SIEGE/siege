#ifndef __PLIST_H__
#define __PLIST_H__

#include "list.h"
#include <siege/common.h>

// [lower/greater]-[equal/than]
#define SG_PLIST_LEQ (1<<0)
#define SG_PLIST_LT  (1<<1)
#define SG_PLIST_GEQ (1<<2)
#define SG_PLIST_GT  (1<<3)

// [high/low]-first-[new/old]
#define SG_PLIST_HFN SG_PLIST_LEQ
#define SG_PLIST_HFO SG_PLIST_LT
#define SG_PLIST_LFN SG_PLIST_GEQ
#define SG_PLIST_LFO SG_PLIST_GT

typedef struct SGList SGPList;

typedef struct SGPItem
{
    float priority;
    void* item;
} SGPItem;

SGPList* sgPListCreate(SGenum flags);
void sgPListDestroy(SGPList* list);
void sgPListEach(SGPList* list, void* data, SGbool SG_EXPORT (*cb)(SGPList* list, void* item, void* data, size_t i, float p));
void sgPListAdd(SGPList* list, float p, void* item);
void sgPListRemoveIndex(SGPList* list, size_t i);
void sgPListRemoveSlice(SGList* list, size_t i1, size_t i2);
void sgPListRemoveItem(SGPList* list, void* item);
void sgPListRemovePriority(SGPList* list, float p);
void sgPListRemovePSlice(SGList* list, float p1, float p2);

#endif // __PLIST_H__
