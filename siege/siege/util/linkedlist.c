#define SG_BUILD_LIBRARY
#include <siege/util/linkedlist.h>

#include <stdlib.h>
#include <string.h>

SGLinkedList* SG_EXPORT sgLinkedListCreate(void)
{
    SGLinkedList* list = malloc(sizeof(SGLinkedList));
    if(list == NULL)
        return NULL;
    list->first = NULL;
    list->last = NULL;
    return list;
}
void SG_EXPORT sgLinkedListDestroy(SGLinkedList* list)
{
    if(list == NULL)
        return;

    while(list->first != NULL)
        sgLinkedListRemoveNode(list->first);
    free(list);
}

SGLinkedNode* SG_EXPORT sgLinkedListPrepend(SGLinkedList* list, void* ptr, SGLinkedNodeFree free)
{
    if(list == NULL)
        return NULL;

    SGLinkedNode* node = malloc(sizeof(SGLinkedNode));
    if(node == NULL)
        return NULL;

    node->list = list;
    node->prev = NULL;
    node->next = list->first;
    node->ptr = ptr;
    node->free = free;
    node->internal = NULL;

    list->first = node;
}
SGLinkedNode* SG_EXPORT sgLinkedListAppend(SGLinkedList* list, void* ptr, SGLinkedNodeFree free)
{
    if(list == NULL)
        return NULL;

    SGLinkedNode* node = malloc(sizeof(SGLinkedNode));
    if(node == NULL)
        return NULL;

    node->list = list;
    node->prev = list->last;
    node->next = NULL;
    node->ptr = ptr;
    node->free = free;
    node->internal = NULL;

    list->last = node;
}
void SG_EXPORT sgLinkedListRemoveNode(SGLinkedNode* node)
{
    if(node == NULL)
        return;

    if(node->list->first == node)
        node->list->first = node->next;
    if(node->list->last == node)
        node->list->last = node->prev;

    if(node->prev != NULL)
        node->prev->next = node->next;
    if(node->next != NULL)
        node->next->prev = node->prev;

    if(node->free != NULL)
        node->free(node);
    free(node);
}
