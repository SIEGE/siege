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

typedef SGint SG_CALL (SGMapCmp)(const void* a, const void* b, void* data);

typedef struct SGMapNode
{
    void* key;
    void* val;
} SGMapNode;

typedef struct SGMap
{
    SGSet set;
    SGMapCmp* cmp;
    void* data;
} SGMap;

SGMap* SG_CALL sgMapInit(SGMap* map, SGMapCmp* cmp, void* data);
void SG_CALL sgMapDeinit(SGMap* map);

SGMap* SG_CALL sgMapCreate(SGMapCmp* cmp, void* data);
void SG_CALL sgMapDestroy(SGMap* map);

void* SG_CALL sgMapReplace(SGMap* map, void* key, void* val);
void* SG_CALL sgMapAssign(SGMap* map, void* key, void* val);
void* SG_CALL sgMapFind(SGMap* map, const void* key);
void* SG_CALL sgMapRemove(SGMap* map, const void* key);

SGMapNode* SG_CALL sgMapAssignNode(SGMap* map, void* key, void* val);
SGMapNode* SG_CALL sgMapFindNode(SGMap* map, const void* key);

SGMapNode* SG_CALL sgMapGetRoot(SGMap* map);
SGMapNode* SG_CALL sgMapGetFirst(SGMap* map);
SGMapNode* SG_CALL sgMapGetLast(SGMap* map);

void* SG_CALL sgMapPopRoot(SGMap* map);
void* SG_CALL sgMapPopFirst(SGMap* map);
void* SG_CALL sgMapPopLast(SGMap* map);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_MAP_H__
