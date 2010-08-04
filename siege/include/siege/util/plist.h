#ifndef __SIEGE_UTIL_PLIST_H__
#define __SIEGE_UTIL_PLIST_H__

#include "list.h"
#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

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

SGPList* SG_EXPORT sgPListCreate(SGenum flags);
void SG_EXPORT sgPListDestroy(SGPList* list);
void SG_EXPORT sgPListEach(SGPList* list, void* data, SGbool SG_EXPORT (*cb)(SGPList* list, void* item, void* data, size_t i, float p));
void SG_EXPORT sgPListAdd(SGPList* list, float p, void* item);
void SG_EXPORT sgPListRemoveIndex(SGPList* list, size_t i);
void SG_EXPORT sgPListRemoveSlice(SGList* list, size_t i1, size_t i2);
void SG_EXPORT sgPListRemoveItem(SGPList* list, void* item);
void SG_EXPORT sgPListRemovePriority(SGPList* list, float p);
void SG_EXPORT sgPListRemovePSlice(SGList* list, float p1, float p2);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_PLIST_H__
