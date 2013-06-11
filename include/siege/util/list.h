/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_LIST_H__
#define __SIEGE_UTIL_LIST_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGListNode
{
    struct SGListNode* prev;
    struct SGListNode* next;
    void* item;
} SGListNode;

typedef struct SGList
{
    struct SGListNode* head;
    struct SGListNode* tail;
} SGList;

SGList* SG_CALL sgListInit(SGList* list);
void SG_CALL sgListDeinit(SGList* list);

SGList* SG_CALL sgListCreate(void);
void SG_CALL sgListDestroy(SGList* list);

size_t SG_CALL sgListLength(SGList* list);

SGListNode* SG_CALL sgListFindItem(SGList* list, void* item);
SGListNode* SG_CALL sgListFindIndex(SGList* list, size_t index);

SGListNode* SG_CALL sgListInsertNode(SGList* list, SGListNode* after, void* item);
SGListNode* SG_CALL sgListInsertItem(SGList* list, void* after, void* item);
SGListNode* SG_CALL sgListInsertIndex(SGList* list, size_t after, void* item);
SGListNode* SG_CALL sgListPrepend(SGList* list, void* item);
SGListNode* SG_CALL sgListAppend(SGList* list, void* item);

void SG_CALL sgListRemoveNode(SGList* list, SGListNode* node);
void SG_CALL sgListRemoveItem(SGList* list, void* item);
void SG_CALL sgListRemoveIndex(SGList* list, size_t index);

SGListNode* SG_CALL sgListGetFirst(SGList* list);
SGListNode* SG_CALL sgListGetLast(SGList* list);

void* SG_CALL sgListPopFirst(SGList* list);
void* SG_CALL sgListPopLast(SGList* list);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LIST_H__
