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
    return (SGSMap*)sgMapCreate((SGMapCmp*)_sgSMapMapCmp, NULL);
}
void SG_EXPORT sgSMapDestroy(SGSMap* smap)
{
    if(!smap) return;

    sgMapDestroy((SGMap*)smap);
}

void* SG_EXPORT sgSMapReplace(SGSMap* smap, const char* key, void* val)
{
    void* old;

    SGMapNode* mnode = sgMapFindNode((SGMap*)smap, key);
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

    sgMapAssign((SGMap*)smap, buf, val);
    return NULL;
}
void* SG_EXPORT sgSMapAssign(SGSMap* smap, const char* key, void* val)
{
    sgSMapReplace(smap, key, val);
    return val;
}
void* SG_EXPORT sgSMapFind(SGSMap* smap, const char* key)
{
    return sgMapFind((SGMap*)smap, key);
}
void* SG_EXPORT sgSMapRemove(SGSMap* smap, const char* key)
{
    SGSMapNode* node = sgSMapFindNode(smap, key);
    if(!node) return NULL;

    char* str = node->key;
    void* rem = sgMapRemove((SGMap*)smap, str);
    free(str);
    return rem;
}

SGSMapNode* SG_EXPORT sgSMapAssignNode(SGSMap* smap, const char* key, void* val)
{
    SGMapNode* node = sgMapFindNode((SGMap*)smap, key);
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

    return sgMapAssignNode((SGMap*)smap, buf, val);
}
SGSMapNode* SG_EXPORT sgSMapFindNode(SGSMap* smap, const char* key)
{
    return sgMapFindNode((SGMap*)smap, key);
}

SGSMapNode* SG_EXPORT sgSMapGetRoot(SGSMap* smap)
{
    return sgMapGetRoot((SGMap*)smap);
}
SGSMapNode* SG_EXPORT sgSMapGetFirst(SGSMap* smap)
{
    return sgMapGetFirst((SGMap*)smap);
}
SGSMapNode* SG_EXPORT sgSMapGetLast(SGSMap* smap)
{
    return sgMapGetLast((SGMap*)smap);
}

void* SG_EXPORT sgSMapPopRoot(SGSMap* smap)
{
    return sgMapPopRoot((SGMap*)smap);
}
void* SG_EXPORT sgSMapPopFirst(SGSMap* smap)
{
    return sgMapPopFirst((SGMap*)smap);
}
void* SG_EXPORT sgSMapPopLast(SGSMap* smap)
{
    return sgMapPopLast((SGMap*)smap);
}
