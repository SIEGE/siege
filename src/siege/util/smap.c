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

static SGint SG_CALL _sgSMapMapCmp(const char* a, const char* b, void* data)
{
    return strcmp(a, b);
}

SGSMap* SG_CALL sgSMapInit(SGSMap* smap)
{
    if(!smap) return NULL;

    if(!sgMapInit(&smap->map, (SGMapCmp*)_sgSMapMapCmp, NULL))
        return NULL;
    return smap;
}
void SG_CALL sgSMapDeinit(SGSMap* smap)
{
    if(!smap) return;

    sgMapDeinit(&smap->map);
}

SGSMap* SG_CALL sgSMapCreate(void)
{
    return sgSMapInit(malloc(sizeof(SGSMap)));
}
void SG_CALL sgSMapDestroy(SGSMap* smap)
{
    sgSMapDeinit(smap);
    free(smap);
}

void* SG_CALL sgSMapReplace(SGSMap* smap, const char* key, void* val)
{
    void* old;

    SGMapNode* mnode = sgMapFindNode(&smap->map, key);
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

    sgMapAssign(&smap->map, buf, val);
    return NULL;
}
void* SG_CALL sgSMapAssign(SGSMap* smap, const char* key, void* val)
{
    sgSMapReplace(smap, key, val);
    return val;
}
void* SG_CALL sgSMapFind(SGSMap* smap, const char* key)
{
    return sgMapFind(&smap->map, key);
}
void* SG_CALL sgSMapRemove(SGSMap* smap, const char* key)
{
    SGSMapNode* node = sgSMapFindNode(smap, key);
    if(!node) return NULL;

    char* str = node->key;
    void* rem = sgMapRemove(&smap->map, str);
    free(str);
    return rem;
}

SGSMapNode* SG_CALL sgSMapAssignNode(SGSMap* smap, const char* key, void* val)
{
    SGMapNode* node = sgMapFindNode(&smap->map, key);
    if(node)
    {
        node->val = val;
        return node;
    }

    size_t len = strlen(key);
    char* buf = malloc(len + 1);
    if(!buf)
        return NULL;
    memcpy(buf, key, len + 1);

    return sgMapAssignNode(&smap->map, buf, val);
}
SGSMapNode* SG_CALL sgSMapFindNode(SGSMap* smap, const char* key)
{
    return sgMapFindNode(&smap->map, key);
}

SGSMapNode* SG_CALL sgSMapGetRoot(SGSMap* smap)
{
    return sgMapGetRoot(&smap->map);
}
SGSMapNode* SG_CALL sgSMapGetFirst(SGSMap* smap)
{
    return sgMapGetFirst(&smap->map);
}
SGSMapNode* SG_CALL sgSMapGetLast(SGSMap* smap)
{
    return sgMapGetLast(&smap->map);
}

void* SG_CALL sgSMapPopRoot(SGSMap* smap)
{
    return sgMapPopRoot(&smap->map);
}
void* SG_CALL sgSMapPopFirst(SGSMap* smap)
{
    return sgMapPopFirst(&smap->map);
}
void* SG_CALL sgSMapPopLast(SGSMap* smap)
{
    return sgMapPopLast(&smap->map);
}
