#ifndef __SIEGE_UTIL_LINKEDLIST_H__
#define __SIEGE_UTIL_LINKEDLIST_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGLinkedNode;

typedef SG_EXPORT void (*SGLinkedNodeFree)(struct SGLinkedNode* node);

typedef struct SGLinkedNode
{
    struct SGLinkedList* list;
    struct SGLinkedNode* prev;
    struct SGLinkedNode* next;
    void* ptr;
    SGLinkedNodeFree free;
    void* internal;
} SGLinkedNode;

typedef struct SGLinkedList
{
    struct SGLinkedNode* first;
    struct SGLinkedNode* last;
} SGLinkedList;

SGLinkedList* SG_EXPORT sgLinkedListCreate(void);
void SG_EXPORT sgLinkedListDestroy(SGLinkedList* list);
SGLinkedNode* SG_EXPORT sgLinkedListPrepend(SGLinkedList* list, void* ptr, SGLinkedNodeFree free);
SGLinkedNode* SG_EXPORT sgLinkedListAppend(SGLinkedList* list, void* ptr, SGLinkedNodeFree free);
void SG_EXPORT sgLinkedListRemoveNode(SGLinkedNode* node);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LINKEDLIST_H__
