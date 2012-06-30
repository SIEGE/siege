/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/util/smap.h>

#include <stdlib.h>
#include <string.h>

static SGint SG_EXPORT _sgSMapMapCmp(const char* a, const char* b, void* data)
{
    return strcmp(a, b);
}

SGSMap* SG_EXPORT sgSMapCreate(void)
{
    SGSMap* smap = malloc(sizeof(SGSMap));
    if(!smap)
        return NULL;

    smap->map = sgMapCreate((SGMapCmp*)_sgSMapMapCmp, smap);
    if(!smap->map)
    {
        free(smap);
        return NULL;
    }

    return smap;
}
void SG_EXPORT sgSMapDestroy(SGSMap* smap)
{
    if(!smap) return;

    sgMapDestroy(smap->map);
}

void* SG_EXPORT sgSMapReplace(SGSMap* smap, const char* key, void* val)
{
    void* old;

    SGMapNode* mnode = sgMapFindNode(smap->map, key);
    if(mnode)
    {
        old = mnode->val;
        mnode->val = val;
        return old;
    }

    size_t len = strlen(key);
    char* buf = malloc(len + 1);
    if(!buf)
        return NULL;
    memcpy(buf, key, len + 1);

    sgMapAssign(smap->map, buf, val);
    return NULL;
}
void* SG_EXPORT sgSMapAssign(SGSMap* smap, const char* key, void* val)
{
    sgSMapReplace(smap, key, val);
    return val;
}
void* SG_EXPORT sgSMapFind(SGSMap* smap, const char* key)
{
    return sgMapFind(smap->map, key);
}
void* SG_EXPORT sgSMapRemove(SGSMap* smap, const char* key)
{
    return sgMapRemove(smap->map, key);
}

void* SG_EXPORT sgSMapGetRoot(SGSMap* smap)
{
    SGMapNode* mnode = sgMapGetRoot(smap->map);
    if(!mnode)
        return NULL;
    return mnode->val;
}
void* SG_EXPORT sgSMapGetFirst(SGSMap* smap)
{
    SGMapNode* mnode = sgMapGetFirst(smap->map);
    if(!mnode)
        return NULL;
    return mnode->val;
}
void* SG_EXPORT sgSMapGetLast(SGSMap* smap)
{
    SGMapNode* mnode = sgMapGetLast(smap->map);
    if(!mnode)
        return NULL;
    return mnode->val;
}

void* SG_EXPORT sgSMapPopRoot(SGSMap* smap)
{
    return sgMapPopRoot(smap->map);
}
void* SG_EXPORT sgSMapPopFirst(SGSMap* smap)
{
    return sgMapPopFirst(smap->map);
}
void* SG_EXPORT sgSMapPopLast(SGSMap* smap)
{
    return sgMapPopLast(smap->map);
}
