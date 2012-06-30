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

#ifndef __SIEGE_UTIL_MAP_H__
#define __SIEGE_UTIL_MAP_H__

#include "../common.h"
#include "set.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef SGint SG_EXPORT (SGMapCmp)(const void* a, const void* b, void* data);

typedef struct SGMapNode
{
    void* key;
    void* val;
} SGMapNode;

typedef struct SGMap
{
    SGSet* set;
    SGMapCmp* cmp;
    void* data;
} SGMap;

SGMap* SG_EXPORT sgMapCreate(SGMapCmp* cmp, void* data);
void SG_EXPORT sgMapDestroy(SGMap* map);

void* SG_EXPORT sgMapReplace(SGMap* map, void* key, void* val);
void* SG_EXPORT sgMapAssign(SGMap* map, void* key, void* val);
void* SG_EXPORT sgMapFind(SGMap* map, const void* key);
void* SG_EXPORT sgMapRemove(SGMap* map, const void* key);

SGMapNode* SG_EXPORT sgMapAssignNode(SGMap* map, void* key, void* val);
SGMapNode* SG_EXPORT sgMapFindNode(SGMap* map, const void* key);

SGMapNode* SG_EXPORT sgMapGetRoot(SGMap* map);
SGMapNode* SG_EXPORT sgMapGetFirst(SGMap* map);
SGMapNode* SG_EXPORT sgMapGetLast(SGMap* map);

void* SG_EXPORT sgMapPopRoot(SGMap* map);
void* SG_EXPORT sgMapPopFirst(SGMap* map);
void* SG_EXPORT sgMapPopLast(SGMap* map);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_MAP_H__
