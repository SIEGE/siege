#ifndef __SIEGE_UTIL_PLINKEDLIST_H__
#define __SIEGE_UTIL_PLINKEDLIST_H__

#include "../common.h"
#include "list.h"

#include <stddef.h>

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

typedef struct SGLinkedNode SGPLinkedNode;
typedef struct SGLinkedList SGPLinkedList;

SGPLinkedList* SG_EXPORT sgPLinkedListCreate(SGenum flags);

SGPLinkedNode* SG_EXPORT sgPLinkedListInsertPriority(SGPLinkedList* list, float priority, void* item);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_PLINKEDLIST_H__
