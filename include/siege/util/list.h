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

SGList* SG_EXPORT sgListCreate(void);
void SG_EXPORT sgListDestroy(SGList* list);

size_t SG_EXPORT sgListLength(SGList* list);

SGListNode* SG_EXPORT sgListFindItem(SGList* list, void* item);
SGListNode* SG_EXPORT sgListFindIndex(SGList* list, size_t index);

SGListNode* SG_EXPORT sgListInsertNode(SGList* list, SGListNode* after, void* item);
SGListNode* SG_EXPORT sgListInsertItem(SGList* list, void* after, void* item);
SGListNode* SG_EXPORT sgListInsertIndex(SGList* list, size_t after, void* item);
SGListNode* SG_EXPORT sgListPrepend(SGList* list, void* item);
SGListNode* SG_EXPORT sgListAppend(SGList* list, void* item);

void SG_EXPORT sgListRemoveNode(SGList* list, SGListNode* node);
void SG_EXPORT sgListRemoveItem(SGList* list, void* item);
void SG_EXPORT sgListRemoveIndex(SGList* list, size_t index);

SGListNode* SG_EXPORT sgListGetFirst(SGList* list);
SGListNode* SG_EXPORT sgListGetLast(SGList* list);

void* SG_EXPORT sgListPopFirst(SGList* list);
void* SG_EXPORT sgListPopLast(SGList* list);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LIST_H__
