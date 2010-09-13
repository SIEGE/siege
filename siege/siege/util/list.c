#define SG_BUILD_LIBRARY
#include <siege/util/list.h>

#include <stdlib.h>
#include <string.h>

SGLinkedList* SG_EXPORT sgLinkedListCreate(void)
{
    SGLinkedList* list = malloc(sizeof(SGLinkedList));
    if(list == NULL)
        return NULL;
    list->first = NULL;
    list->last = NULL;
    list->internal = NULL;
    return list;
}
void SG_EXPORT sgLinkedListDestroy(SGLinkedList* list)
{
    if(list == NULL)
        return;

    while(list->first != NULL)
        sgLinkedListRemoveNode(list, list->first);

    if(list->internalFree != NULL)
        list->internalFree(list->internal);
    free(list);
}

size_t SG_EXPORT sgLinkedListLength(SGLinkedList* list)
{
    if(list == NULL)
        return 0;

    size_t i;
    SGLinkedNode* node = list->first;
    for(i = 0; node != NULL; i++)
        node = node->next;
    return i;
}

SGLinkedNode* SG_EXPORT sgLinkedListFindItem(SGLinkedList* list, void* item)
{
    if(list == NULL)
        return NULL;

    SGLinkedNode* node;
    for(node = list->first; node != NULL; node = node->next)
        if(node->item == item)
            return node;
    return NULL;
}
SGLinkedNode* SG_EXPORT sgLinkedListFindIndex(SGLinkedList* list, size_t index)
{
    if(list == NULL)
        return NULL;

    size_t i;
    SGLinkedNode* node;
    for(node = list->first, i = 0; node != NULL; node = node->next, i++)
        if(i == index)
            return node;
    return NULL;
}

SGLinkedNode* SG_EXPORT sgLinkedListInsertNode(SGLinkedList* list, SGLinkedNode* after, void* item)
{
    if(list == NULL)
        return NULL;

    SGLinkedNode* node = malloc(sizeof(SGLinkedNode));
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
SGLinkedNode* SG_EXPORT sgLinkedListInsertItem(SGLinkedList* list, void* after, void* item)
{
    SGLinkedNode* node = sgLinkedListFindItem(list, after);
    if(node == NULL)
        return NULL;
    return sgLinkedListInsertNode(list, node, item);
}
SGLinkedNode* SG_EXPORT sgLinkedListInsertIndex(SGLinkedList* list, size_t after, void* item)
{
    SGLinkedNode* node = sgLinkedListFindIndex(list, after);
    if(node == NULL)
        return NULL;
    return sgLinkedListInsertNode(list, node, item);
}
SGLinkedNode* SG_EXPORT sgLinkedListPrepend(SGLinkedList* list, void* item)
{
    return sgLinkedListInsertNode(list, NULL, item);
}
SGLinkedNode* SG_EXPORT sgLinkedListAppend(SGLinkedList* list, void* item)
{
    return sgLinkedListInsertNode(list, list->last, item);
}

void SG_EXPORT sgLinkedListRemoveNode(SGLinkedList* list, SGLinkedNode* node)
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
void SG_EXPORT sgLinkedListRemoveItem(SGLinkedList* list, void* item)
{
    SGLinkedNode* node = sgLinkedListFindItem(list, item);
    if(node != NULL)
        sgLinkedListRemoveNode(list, node);
}
void SG_EXPORT sgLinkedListRemoveIndex(SGLinkedList* list, size_t index)
{
    SGLinkedNode* node = sgLinkedListFindIndex(list, index);
    if(node != NULL)
        sgLinkedListRemoveNode(list, node);
}

SGLinkedNode* SG_EXPORT sgLinkedListGetFirst(SGLinkedList* list)
{
    if(list == NULL)
        return NULL;
    return list->first;
}
SGLinkedNode* SG_EXPORT sgLinkedListGetLast(SGLinkedList* list)
{
    if(list == NULL)
        return NULL;
    return list->last;
}

void* SG_EXPORT sgLinkedListPopFirst(SGLinkedList* list)
{
    if(list == NULL)
        return NULL;
    if(list->first == NULL)
        return NULL;
    void* item = list->first->item;
    sgLinkedListRemoveNode(list, list->first);
    return item;
}
void* SG_EXPORT sgLinkedListPopLast(SGLinkedList* list)
{
    if(list == NULL)
        return NULL;
    if(list->last == NULL)
        return NULL;
    void* item = list->last->item;
    sgLinkedListRemoveNode(list, list->last);
    return item;
}
