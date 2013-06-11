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

#ifndef __SIEGE_UTIL_SMAP_H__
#define __SIEGE_UTIL_SMAP_H__

#include "../common.h"
#include "map.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef SGMapNode SGSMapNode;

/*
 * String map conveniency wrapper. Copies all string keys inside.
 *
 * TODO: Should this be renamed to SGDictionary or similar?
 *
 * Implementation note:
 *  The only reason we're not direcly doing "typedef SGSMap SGMap" is to enable
 *  the compiler to warn the user if he uses SMap functions with Map and
 *  vice-versa, as there are some subtle differences, mostly regarding key
 *  string allocation.
 */
typedef struct SGSMap
{
    SGMap map;
} SGSMap;

SGSMap* SG_CALL sgSMapInit(SGSMap* smap);
void SG_CALL sgSMapDeinit(SGSMap* smap);

SGSMap* SG_CALL sgSMapCreate(void);
void SG_CALL sgSMapDestroy(SGSMap* smap);

void* SG_CALL sgSMapReplace(SGSMap* smap, const char* key, void* val);
void* SG_CALL sgSMapAssign(SGSMap* smap, const char* key, void* val);
void* SG_CALL sgSMapFind(SGSMap* smap, const char* key);
void* SG_CALL sgSMapRemove(SGSMap* smap, const char* key);

SGSMapNode* SG_CALL sgSMapAssignNode(SGSMap* smap, const char* key, void* val);
SGSMapNode* SG_CALL sgSMapFindNode(SGSMap* smap, const char* key);

SGSMapNode* SG_CALL sgSMapGetRoot(SGSMap* smap);
SGSMapNode* SG_CALL sgSMapGetFirst(SGSMap* smap);
SGSMapNode* SG_CALL sgSMapGetLast(SGSMap* smap);

void* SG_CALL sgSMapPopRoot(SGSMap* smap);
void* SG_CALL sgSMapPopFirst(SGSMap* smap);
void* SG_CALL sgSMapPopLast(SGSMap* smap);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_SMAP_H__
