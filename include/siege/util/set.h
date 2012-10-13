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

typedef SGint SG_EXPORT (SGSetCmp)(const void* a, const void* b, void* data);

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

void SG_EXPORT _sgSetDestroyNode(SGSetNode* node);

SGSetNode* SG_EXPORT _sgSetNodeSkew(SGSetNode* node);
SGSetNode* SG_EXPORT _sgSetNodeSplit(SGSetNode* node);

SGSetNode* SG_EXPORT _sgSetNodeInsert(SGSet* set, SGSetNode* root, SGSetNode* node);
SGSetNode* SG_EXPORT _sgSetNodeRemove(SGSet* set, SGSetNode* root, SGSetNode* node);

SGSet* SG_EXPORT sgSetCreate(SGSetCmp* cmp, void* data);
void SG_EXPORT sgSetDestroy(SGSet* set);

//size_t SG_EXPORT sgSetNumNodes(SGSet* set);

SGSetNode* SG_EXPORT sgSetSearch(SGSet* set, const void* item);

SGSetNode* SG_EXPORT sgSetInsert(SGSet* set, void* item);

void SG_EXPORT sgSetRemoveNode(SGSet* set, SGSetNode* node);
void SG_EXPORT sgSetRemoveItem(SGSet* set, void* item);

SGSetNode* SG_EXPORT sgSetGetRoot(SGSet* set);
SGSetNode* SG_EXPORT sgSetGetFirst(SGSet* set);
SGSetNode* SG_EXPORT sgSetGetLast(SGSet* set);

void* SG_EXPORT sgSetPopRoot(SGSet* set);
void* SG_EXPORT sgSetPopFirst(SGSet* set);
void* SG_EXPORT sgSetPopLast(SGSet* set);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_SET_H__
