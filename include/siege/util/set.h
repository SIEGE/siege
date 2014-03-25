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

#ifndef __SIEGE_UTIL_SET_H__
#define __SIEGE_UTIL_SET_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef SGint SG_CALL (SGSetCmp)(const void* a, const void* b, void* data);

typedef struct SGSetNode
{
    //struct SGSetNode* parent;
    struct SGSetNode* left;
    struct SGSetNode* right;
    size_t level;
    void* item;
} SGSetNode;

typedef struct SGSet
{
    SGSetNode* root;
    SGSetCmp* cmp;
    void* data;
} SGSet;

void SG_CALL _sgSetDestroyNode(SGSetNode* node);

SGSetNode* SG_CALL _sgSetNodeSkew(SGSetNode* node);
SGSetNode* SG_CALL _sgSetNodeSplit(SGSetNode* node);

SGSetNode* SG_CALL _sgSetNodeInsert(SGSet* set, SGSetNode* root, SGSetNode** cnode);
SGSetNode* SG_CALL _sgSetNodeRemove(SGSet* set, SGSetNode* root, SGSetNode* node);

SGSet* SG_CALL sgSetInit(SGSet* set, SGSetCmp* cmp, void* data);
void SG_CALL sgSetDeinit(SGSet* set);

SGSet* SG_CALL sgSetCreate(SGSetCmp* cmp, void* data);
void SG_CALL sgSetDestroy(SGSet* set);

//size_t SG_CALL sgSetNumNodes(SGSet* set);

SGSetNode* SG_CALL sgSetSearch(SGSet* set, const void* item);

SGSetNode* SG_CALL sgSetInsert(SGSet* set, void* item);

void SG_CALL sgSetRemoveNode(SGSet* set, SGSetNode* node);
void SG_CALL sgSetRemoveItem(SGSet* set, void* item);

SGSetNode* SG_CALL sgSetGetRoot(SGSet* set);
SGSetNode* SG_CALL sgSetGetFirst(SGSet* set);
SGSetNode* SG_CALL sgSetGetLast(SGSet* set);

void* SG_CALL sgSetPopRoot(SGSet* set);
void* SG_CALL sgSetPopFirst(SGSet* set);
void* SG_CALL sgSetPopLast(SGSet* set);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_SET_H__
