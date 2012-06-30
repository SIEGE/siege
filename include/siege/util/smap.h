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

/*
 * String map conveniency wrapper. Copies all string keys inside.
 *
 * TODO: Should this be renamed to SGDictionary or similar?
 */
typedef struct SGSMap
{
    SGMap* map;
} SGSMap;

SGSMap* SG_EXPORT sgSMapCreate(void);
void SG_EXPORT sgSMapDestroy(SGSMap* smap);

void* SG_EXPORT sgSMapReplace(SGSMap* smap, const char* key, void* val);
void* SG_EXPORT sgSMapAssign(SGSMap* smap, const char* key, void* val);
void* SG_EXPORT sgSMapFind(SGSMap* smap, const char* key);
void* SG_EXPORT sgSMapRemove(SGSMap* smap, const char* key);

void* SG_EXPORT sgSMapGetRoot(SGSMap* smap);
void* SG_EXPORT sgSMapGetFirst(SGSMap* smap);
void* SG_EXPORT sgSMapGetLast(SGSMap* smap);

void* SG_EXPORT sgSMapPopRoot(SGSMap* smap);
void* SG_EXPORT sgSMapPopFirst(SGSMap* smap);
void* SG_EXPORT sgSMapPopLast(SGSMap* smap);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_SMAP_H__
