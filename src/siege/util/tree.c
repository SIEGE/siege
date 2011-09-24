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
#include <siege/util/tree.h>

#include <stdlib.h>
#include <string.h>

/// \TODO Non-recursive variant of this function.
void SG_EXPORT _sgTreeDestroyNode(SGTreeNode* node)
{
    if(!node)
        return;
    _sgTreeDestroyNode(node->left);
    _sgTreeDestroyNode(node->right);
    free(node);
}

SGTreeNode* SG_EXPORT _sgTreeNodeSkew(SGTreeNode* node)
{
    SGTreeNode* ret;
    size_t level = node->left ? node->left->level : 0;
    if(level == node->level && node->level)
    {
        ret = node->left;
        node->left = ret ? ret->right : NULL;
        if(ret)
            ret->right = node;
        node = ret;
    }
    return node;
}
SGTreeNode* SG_EXPORT _sgTreeNodeSplit(SGTreeNode* node)
{
    SGTreeNode* ret;
    size_t level = node->right ? (node->right->right ? node->right->right->level : 0) : 0;
    if(level == node->level && node->level)
    {
        ret = node->right;
        node->right = ret ? ret->left : NULL;
        if(ret)
            ret->left = node;
        node = ret;
        node->level++;
    }
    return node;
}

/**
 * \TODO: Use a dynamic array for the stack...
 * Update: Maybe not. At stack size of 256,we have (I think?) up to
 * 2.31584178475e+77 values... Should be enough since this is *way* more than
 * the typical amount of memory in a computer, nevermind that a single node is
 * more than 1 byte.
 */
SGTreeNode* SG_EXPORT _sgTreeNodeInsert(SGTree* tree, SGTreeNode* root, SGTreeNode* node)
{
    SGTreeNode* curr;
    SGTreeNode* stack[256];
    ptrdiff_t top;
    int cmp;

    if(!root)
        root = node;
    else
    {
        curr = root;
        top = 0;
        cmp = 1;
        while(1)
        {
            stack[top++] = curr;
            cmp = tree->cmp(curr->item, node->item);

            if(!cmp)
                break;
            else if((cmp < 0) ? !curr->right : !curr->left)
                break;
            curr = (cmp < 0) ? curr->right : curr->left;
        }

        if(cmp == 0)
        {
            curr->item = node->item;
            free(node);
            return root;
        }

        if(cmp < 0)
            curr->right = node;
        else
            curr->left = node;

        while(--top >= 0)
        {
            if(top)
                cmp = (stack[top - 1]->right == stack[top]) ? -1 : 1;

            stack[top] = _sgTreeNodeSkew(stack[top]);
            stack[top] = _sgTreeNodeSplit(stack[top]);

            if(top)
            {
                if(cmp < 0)
                    stack[top - 1]->right = stack[top];
                else
                    stack[top - 1]->left = stack[top];
            }
            else
                root = stack[top];
        }
    }
    return root;
}
SGTreeNode* SG_EXPORT _sgTreeNodeRemove(SGTree* tree, SGTreeNode* root, SGTreeNode* node)
{
    SGTreeNode* remove;
    SGTreeNode* curr;
    SGTreeNode* stack[256];
    ptrdiff_t top;
    int tcmp;
    int cmp;
    SGTreeNode* heir;
    SGTreeNode* prev;
    size_t llevel;
    size_t rlevel;
    if(root)
    {
        curr = root;
        top = 0;
        cmp = 1;
        while(1)
        {
            stack[top++] = curr;

            if(!curr)
                return root;

            tcmp = tree->cmp(curr->item, node->item);
            if(!tcmp)
                break;
            cmp = tcmp;
            if(cmp < 0)
                curr = curr->right;
            else
                curr = curr->left;
        }

        if(!curr->left || !curr->right)
        {
            if(--top)
            {
                if(cmp < 0)
                    stack[top - 1]->right = curr->left ? curr->left : curr->right;
                else
                    stack[top - 1]->left = curr->left ? curr->left : curr->right;
            }
            else
                root = curr->right;
            remove = node;
        }
        else
        {
            heir = curr->right;
            prev = curr;

            while(heir->left)
            {
                stack[top++] = prev = heir;
                heir = heir->left;
            }

            curr->item = heir->item;
            if(prev == curr)
                prev->right = heir->right;
            else
                prev->left = heir->right;
            remove = heir;
        }

        while(--top >= 0)
        {
            if(top)
                cmp = (stack[top - 1]->right == stack[top]) ? -1 : 1;

            llevel = stack[top]->left ? stack[top]->left->level : 0;
            rlevel = stack[top]->right ? stack[top]->right->level : 0;

            if(llevel < stack[top]->level - 1
            || rlevel < stack[top]->level - 1)
            {
                if(rlevel > --stack[top]->level)
                    stack[top]->right->level = stack[top]->level; // if it's >, then it's definately not 0, thus not NULL

                if(stack[top])
                {
                    stack[top] = _sgTreeNodeSkew(stack[top]);
                    if(stack[top]->right)
                    {
                        stack[top]->right = _sgTreeNodeSkew(stack[top]->right);
                        if(stack[top]->right->right)
                            stack[top]->right->right = _sgTreeNodeSkew(stack[top]->right->right);
                    }
                    stack[top] = _sgTreeNodeSplit(stack[top]);
                    if(stack[top]->right)
                        stack[top]->right = _sgTreeNodeSplit(stack[top]->right);
                }
            }

            if(top)
            {
                if(cmp < 0)
                    stack[top - 1]->right = stack[top];
                else
                    stack[top - 1]->left = stack[top];
            }
            else
                root = stack[top];
        }
    }
    free(remove);
    return root;
}

SGTree* SG_EXPORT sgTreeCreate(SGTreeNodeCmp* cmp)
{
    SGTree* tree = malloc(sizeof(SGTree));
    if(!tree)
        return NULL;
    tree->root = NULL;
    tree->cmp = cmp;
    return tree;
}
void SG_EXPORT sgTreeDestroy(SGTree* tree)
{
    if(!tree)
        return;
    _sgTreeDestroyNode(tree->root);
    free(tree);
}

//size_t SG_EXPORT sgTreeNumNodes(SGTree* tree);

SGTreeNode* SG_EXPORT sgTreeFindItem(SGTree* tree, void* item)
{
    SGTreeNode* node = tree->root;
    int cmp;
    while(node)
    {
        cmp = tree->cmp(node->item, item);
        if(!cmp)
            break;
        if(cmp < 0)
            node = node->right;
        else
            node = node->left;
    }
    return node;
}

SGTreeNode* SG_EXPORT sgTreeInsert(SGTree* tree, void* item)
{
    SGTreeNode* node = malloc(sizeof(SGTreeNode));
    if(!node)
        return NULL;
    //node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->level = 1;
    node->item = item;
    tree->root = _sgTreeNodeInsert(tree, tree->root, node);
    return node;
}

void SG_EXPORT sgTreeRemoveNode(SGTree* tree, SGTreeNode* node)
{
    tree->root = _sgTreeNodeRemove(tree, tree->root, node);
}
void SG_EXPORT sgTreeRemoveItem(SGTree* tree, void* item)
{
    SGTreeNode* node = sgTreeFindItem(tree, item);
    if(!node)
        return;
    sgTreeRemoveNode(tree, node);
}

SGTreeNode* SG_EXPORT sgTreeGetRoot(SGTree* tree)
{
    return tree->root;
}
SGTreeNode* SG_EXPORT sgTreeGetFirst(SGTree* tree)
{
    SGTreeNode* curr = tree->root;
    if(curr)
        while(curr->left)
            curr = curr->left;
    return curr;
}
SGTreeNode* SG_EXPORT sgTreeGetLast(SGTree* tree)
{
    SGTreeNode* curr = tree->root;
    if(curr)
        while(curr->right)
            curr = curr->right;
    return curr;
}

void* SG_EXPORT sgTreePopRoot(SGTree* tree)
{
    SGTreeNode* node = sgTreeGetRoot(tree);
    if(!node)
        return NULL;
    void* item = node->item;
    sgTreeRemoveNode(tree, node);
    return item;
}
void* SG_EXPORT sgTreePopFirst(SGTree* tree)
{
    SGTreeNode* node = sgTreeGetFirst(tree);
    if(!node)
        return NULL;
    void* item = node->item;
    sgTreeRemoveNode(tree, node);
    return item;
}
void* SG_EXPORT sgTreePopLast(SGTree* tree)
{
    SGTreeNode* node = sgTreeGetLast(tree);
    if(!node)
        return NULL;
    void* item = node->item;
    sgTreeRemoveNode(tree, node);
    return item;
}
