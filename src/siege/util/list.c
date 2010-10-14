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

#define SG_BUILD_LIBRARY
#include <siege/util/list.h>

#include <stdlib.h>
#include <string.h>

SGList* SG_EXPORT sgListCreate(void)
{
    SGList* list = malloc(sizeof(SGList));
    if(list == NULL)
        return NULL;
    list->first = NULL;
    list->last = NULL;
    list->internal = NULL;
    return list;
}
void SG_EXPORT sgListDestroy(SGList* list)
{
    if(list == NULL)
        return;

    while(list->first != NULL)
        sgListRemoveNode(list, list->first);

    if(list->internalFree != NULL)
        list->internalFree(list->internal);
    free(list);
}

size_t SG_EXPORT sgListLength(SGList* list)
{
    if(list == NULL)
        return 0;

    size_t i;
    SGListNode* node = list->first;
    for(i = 0; node != NULL; i++)
        node = node->next;
    return i;
}

SGListNode* SG_EXPORT sgListFindItem(SGList* list, void* item)
{
    if(list == NULL)
        return NULL;

    SGListNode* node;
    for(node = list->first; node != NULL; node = node->next)
        if(node->item == item)
            return node;
    return NULL;
}
SGListNode* SG_EXPORT sgListFindIndex(SGList* list, size_t index)
{
    if(list == NULL)
        return NULL;

    size_t i;
    SGListNode* node;
    for(node = list->first, i = 0; node != NULL; node = node->next, i++)
        if(i == index)
            return node;
    return NULL;
}

SGListNode* SG_EXPORT sgListInsertNode(SGList* list, SGListNode* after, void* item)
{
    if(list == NULL)
        return NULL;

    SGListNode* node = malloc(sizeof(SGListNode));
    if(node == NULL)
        return NULL;

    node->list = list;

    if(after == NULL) // first item
    {
        node->prev = NULL;
        node->next = list->first;
        if(list->first)
            list->first->prev = node;
        list->first = node;
    }
    else // not first item
    {
        node->prev = after;
        node->next = after->next;
        if(after->next)
            after->next->prev = node;
        after->next = node;

        if(after == list->last)
            list->last = node;
    }

    node->item = item;
    node->internal = NULL;
    return node;
}
SGListNode* SG_EXPORT sgListInsertItem(SGList* list, void* after, void* item)
{
    SGListNode* node = sgListFindItem(list, after);
    if(node == NULL)
        return NULL;
    return sgListInsertNode(list, node, item);
}
SGListNode* SG_EXPORT sgListInsertIndex(SGList* list, size_t after, void* item)
{
    SGListNode* node = sgListFindIndex(list, after);
    if(node == NULL)
        return NULL;
    return sgListInsertNode(list, node, item);
}
SGListNode* SG_EXPORT sgListPrepend(SGList* list, void* item)
{
    return sgListInsertNode(list, NULL, item);
}
SGListNode* SG_EXPORT sgListAppend(SGList* list, void* item)
{
    return sgListInsertNode(list, list->last, item);
}

void SG_EXPORT sgListRemoveNode(SGList* list, SGListNode* node)
{
    if(list == NULL)
        return;
    if(node == NULL)
        return;

    if(list->first == node)
        list->first = node->next;
    if(list->last == node)
        list->last = node->prev;

    if(node->prev != NULL)
        node->prev->next = node->next;
    if(node->next != NULL)
        node->next->prev = node->prev;

    if(node->internalFree != NULL)
        node->internalFree(node->internal);
    free(node);
}
void SG_EXPORT sgListRemoveItem(SGList* list, void* item)
{
    SGListNode* node = sgListFindItem(list, item);
    if(node != NULL)
        sgListRemoveNode(list, node);
}
void SG_EXPORT sgListRemoveIndex(SGList* list, size_t index)
{
    SGListNode* node = sgListFindIndex(list, index);
    if(node != NULL)
        sgListRemoveNode(list, node);
}

SGListNode* SG_EXPORT sgListGetFirst(SGList* list)
{
    if(list == NULL)
        return NULL;
    return list->first;
}
SGListNode* SG_EXPORT sgListGetLast(SGList* list)
{
    if(list == NULL)
        return NULL;
    return list->last;
}

void* SG_EXPORT sgListPopFirst(SGList* list)
{
    if(list == NULL)
        return NULL;
    if(list->first == NULL)
        return NULL;
    void* item = list->first->item;
    sgListRemoveNode(list, list->first);
    return item;
}
void* SG_EXPORT sgListPopLast(SGList* list)
{
    if(list == NULL)
        return NULL;
    if(list->last == NULL)
        return NULL;
    void* item = list->last->item;
    sgListRemoveNode(list, list->last);
    return item;
}
