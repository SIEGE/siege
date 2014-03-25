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
#include <siege/util/map.h>

#include <stdlib.h>
#include <string.h>

static SGint _sgMapSetCmp(const SGMapNode* a, const SGMapNode* b, void* data)
{
    SGMap* map = data;
    return map->cmp(a->key, b->key, map->data);
}

SGMap* SG_CALL sgMapInit(SGMap* map, SGMapCmp* cmp, void* data)
{
    if(!map) return NULL;

    if(!sgSetInit(&map->set, (SGSetCmp*)_sgMapSetCmp, map))
        return NULL;
    map->cmp = cmp;
    map->data = data;
    return map;
}
void SG_CALL sgMapDeinit(SGMap* map)
{
    if(!map) return;

    sgSetDeinit(&map->set);
}

SGMap* SG_CALL sgMapCreate(SGMapCmp* cmp, void* data)
{
    return sgMapInit(malloc(sizeof(SGMap)), cmp, data);
}
void SG_CALL sgMapDestroy(SGMap* map)
{
    sgMapDeinit(map);
    free(map);
}

void* SG_CALL sgMapReplace(SGMap* map, void* key, void* val)
{
    SGMapNode search;
    search.key = key;

    void* old;

    SGMapNode* mnode;
    SGSetNode* snode = sgSetSearch(&map->set, &search);
    if(snode)
    {
        mnode = snode->item;
        old = mnode->val;

        mnode->key = key;
        mnode->val = val;

        return old;
    }

    mnode = malloc(sizeof(*mnode));
    if(!mnode) return NULL;

    mnode->key = key;
    mnode->val = val;

    sgSetInsert(&map->set, mnode);
    return NULL;
}
void* SG_CALL sgMapAssign(SGMap* map, void* key, void* val)
{
    sgMapReplace(map, key, val);
    return val;
}
void* SG_CALL sgMapFind(SGMap* map, const void* key)
{
    SGMapNode* node = sgMapFindNode(map, key);
    if(!node)
        return NULL;
    return node->val;
}
void* SG_CALL sgMapRemove(SGMap* map, const void* key)
{
    SGMapNode search;
    search.key = (void*)key;

    SGMapNode* mnode;
    SGSetNode* snode = sgSetSearch(&map->set, &search);
    if(!snode)
        return NULL;

    mnode = snode->item;
    sgSetRemoveNode(&map->set, snode);

    void* val = mnode->val;
    free(mnode);
    return val;
}

SGMapNode* SG_CALL sgMapAssignNode(SGMap* map, void* key, void* val)
{
    SGMapNode search;
    search.key = key;

    SGMapNode* mnode;
    SGSetNode* snode = sgSetSearch(&map->set, &search);
    if(snode)
    {
        mnode = snode->item;

        mnode->key = key;
        mnode->val = val;

        return mnode;
    }

    mnode = malloc(sizeof(*mnode));
    if(!mnode) return NULL;

    mnode->key = key;
    mnode->val = val;

    sgSetInsert(&map->set, mnode);
    return mnode;
}
SGMapNode* SG_CALL sgMapFindNode(SGMap* map, const void* key)
{
    SGMapNode search;
    search.key = (void*)key;

    SGSetNode* snode = sgSetSearch(&map->set, &search);
    if(snode)
        return snode->item;
    return NULL;
}

SGMapNode* SG_CALL sgMapGetRoot(SGMap* map)
{
    SGSetNode* snode = sgSetGetRoot(&map->set);
    if(!snode)
        return NULL;
    return snode->item;
}
SGMapNode* SG_CALL sgMapGetFirst(SGMap* map)
{
    SGSetNode* snode = sgSetGetFirst(&map->set);
    if(!snode)
        return NULL;
    return snode->item;
}
SGMapNode* SG_CALL sgMapGetLast(SGMap* map)
{
    SGSetNode* snode = sgSetGetLast(&map->set);
    if(!snode)
        return NULL;
    return snode->item;
}

void* SG_CALL sgMapPopRoot(SGMap* map)
{
    SGMapNode* mnode = sgSetPopRoot(&map->set);
    if(!mnode)
        return NULL;
    return mnode->val;
}
void* SG_CALL sgMapPopFirst(SGMap* map)
{
    SGMapNode* mnode = sgSetPopFirst(&map->set);
    if(!mnode)
        return NULL;
    return mnode->val;
}
void* SG_CALL sgMapPopLast(SGMap* map)
{
    SGMapNode* mnode = sgSetPopLast(&map->set);
    if(!mnode)
        return NULL;
    return mnode->val;
}
