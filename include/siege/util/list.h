/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_UTIL_LINKEDLIST_H__
#define __SIEGE_UTIL_LINKEDLIST_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGLinkedNode
{
    struct SGLinkedList* list;
    struct SGLinkedNode* prev;
    struct SGLinkedNode* next;
    void* item;

    void* internal;
    void (*internalFree)(void*);
} SGLinkedNode;

typedef struct SGLinkedList
{
    struct SGLinkedNode* first;
    struct SGLinkedNode* last;

    void* internal;
    void (*internalFree)(void*);
} SGLinkedList;

SGLinkedList* SG_EXPORT sgLinkedListCreate(void);
void SG_EXPORT sgLinkedListDestroy(SGLinkedList* list);

size_t SG_EXPORT sgLinkedListLength(SGLinkedList* list);

SGLinkedNode* SG_EXPORT sgLinkedListFindItem(SGLinkedList* list, void* item);
SGLinkedNode* SG_EXPORT sgLinkedListFindIndex(SGLinkedList* list, size_t index);

SGLinkedNode* SG_EXPORT sgLinkedListInsertNode(SGLinkedList* list, SGLinkedNode* after, void* item);
SGLinkedNode* SG_EXPORT sgLinkedListInsertItem(SGLinkedList* list, void* after, void* item);
SGLinkedNode* SG_EXPORT sgLinkedListInsertIndex(SGLinkedList* list, size_t after, void* item);
SGLinkedNode* SG_EXPORT sgLinkedListPrepend(SGLinkedList* list, void* item);
SGLinkedNode* SG_EXPORT sgLinkedListAppend(SGLinkedList* list, void* item);

void SG_EXPORT sgLinkedListRemoveNode(SGLinkedList* list, SGLinkedNode* node);
void SG_EXPORT sgLinkedListRemoveItem(SGLinkedList* list, void* item);
void SG_EXPORT sgLinkedListRemoveIndex(SGLinkedList* list, size_t index);

SGLinkedNode* SG_EXPORT sgLinkedListGetFirst(SGLinkedList* list);
SGLinkedNode* SG_EXPORT sgLinkedListGetLast(SGLinkedList* list);

void* SG_EXPORT sgLinkedListPopFirst(SGLinkedList* list);
void* SG_EXPORT sgLinkedListPopLast(SGLinkedList* list);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LINKEDLIST_H__
