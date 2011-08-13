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

#ifndef __SIEGE_UTIL_TREE_H__
#define __SIEGE_UTIL_TREE_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef SGint SG_EXPORT (SGTreeNodeCmp)(const void* a, const void* b);

typedef struct SGTreeNode
{
    //struct SGTreeNode* parent;
    struct SGTreeNode* left;
    struct SGTreeNode* right;
    size_t level;
    void* item;
} SGTreeNode;

typedef struct SGTree
{
    SGTreeNode* root;
    SGTreeNodeCmp* cmp;
} SGTree;

void SG_EXPORT _sgTreeDestroyNode(SGTreeNode* node);

SGTreeNode* SG_EXPORT _sgTreeNodeSkew(SGTreeNode* node);
SGTreeNode* SG_EXPORT _sgTreeNodeSplit(SGTreeNode* node);

SGTreeNode* SG_EXPORT _sgTreeNodeInsert(SGTree* tree, SGTreeNode* root, SGTreeNode* node);
SGTreeNode* SG_EXPORT _sgTreeNodeRemove(SGTree* tree, SGTreeNode* root, SGTreeNode* node);

SGTree* SG_EXPORT sgTreeCreate(SGTreeNodeCmp* cmp);
void SG_EXPORT sgTreeDestroy(SGTree* tree);

//size_t SG_EXPORT sgTreeNumNodes(SGTree* tree);

SGTreeNode* SG_EXPORT sgTreeFindItem(SGTree* tree, void* item);

SGTreeNode* SG_EXPORT sgTreeInsert(SGTree* tree, void* item);

void SG_EXPORT sgTreeRemoveNode(SGTree* tree, SGTreeNode* node);
void SG_EXPORT sgTreeRemoveItem(SGTree* tree, void* item);

SGTreeNode* SG_EXPORT sgTreeGetRoot(SGTree* tree);
SGTreeNode* SG_EXPORT sgTreeGetFirst(SGTree* tree);
SGTreeNode* SG_EXPORT sgTreeGetLast(SGTree* tree);

void* SG_EXPORT sgTreePopRoot(SGTree* tree);
void* SG_EXPORT sgTreePopFirst(SGTree* tree);
void* SG_EXPORT sgTreePopLast(SGTree* tree);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_TREE_H__
