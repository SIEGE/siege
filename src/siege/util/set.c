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
#include <siege/util/set.h>

#include <stdlib.h>
#include <string.h>

/// \TODO Non-recursive variant of this function.
void SG_EXPORT _sgSetDestroyNode(SGSetNode* node)
{
    if(!node)
        return;
    _sgSetDestroyNode(node->left);
    _sgSetDestroyNode(node->right);
    free(node);
}

SGSetNode* SG_EXPORT _sgSetNodeSkew(SGSetNode* node)
{
    SGSetNode* ret;
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
SGSetNode* SG_EXPORT _sgSetNodeSplit(SGSetNode* node)
{
    SGSetNode* ret;
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
SGSetNode* SG_EXPORT _sgSetNodeInsert(SGSet* set, SGSetNode* root, SGSetNode* node)
{
    SGSetNode* curr;
    SGSetNode* stack[256];
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
            cmp = set->cmp(curr->item, node->item, set->data);

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

            stack[top] = _sgSetNodeSkew(stack[top]);
            stack[top] = _sgSetNodeSplit(stack[top]);

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
SGSetNode* SG_EXPORT _sgSetNodeRemove(SGSet* set, SGSetNode* root, SGSetNode* node)
{
    SGSetNode* remove = NULL;
    SGSetNode* curr;
    SGSetNode* stack[256];
    ptrdiff_t top;
    int tcmp;
    int cmp;
    SGSetNode* heir;
    SGSetNode* prev;
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

            tcmp = set->cmp(curr->item, node->item, set->data);
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
                    stack[top] = _sgSetNodeSkew(stack[top]);
                    if(stack[top]->right)
                    {
                        stack[top]->right = _sgSetNodeSkew(stack[top]->right);
                        if(stack[top]->right->right)
                            stack[top]->right->right = _sgSetNodeSkew(stack[top]->right->right);
                    }
                    stack[top] = _sgSetNodeSplit(stack[top]);
                    if(stack[top]->right)
                        stack[top]->right = _sgSetNodeSplit(stack[top]->right);
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

SGSet* SG_EXPORT sgSetCreate(SGSetCmp* cmp, void* data)
{
    SGSet* set = malloc(sizeof(SGSet));
    if(!set)
        return NULL;
    set->root = NULL;
    set->cmp = cmp;
    set->data = data;
    return set;
}
void SG_EXPORT sgSetDestroy(SGSet* set)
{
    if(!set)
        return;
    _sgSetDestroyNode(set->root);
    free(set);
}

//size_t SG_EXPORT sgSetNumNodes(SGSet* set);

SGSetNode* SG_EXPORT sgSetSearch(SGSet* set, const void* item)
{
    SGSetNode* node = set->root;
    int cmp;
    while(node)
    {
        cmp = set->cmp(node->item, item, set->data);
        if(!cmp)
            break;
        if(cmp < 0)
            node = node->right;
        else
            node = node->left;
    }
    return node;
}
SGSetNode* SG_EXPORT SG_HINT_DEPRECATED sgSetFindItem(SGSet* set, const void* item)
{
    return sgSetSearch(set, item);
}

SGSetNode* SG_EXPORT sgSetInsert(SGSet* set, void* item)
{
    SGSetNode* node = malloc(sizeof(SGSetNode));
    if(!node)
        return NULL;
    //node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->level = 1;
    node->item = item;
    set->root = _sgSetNodeInsert(set, set->root, node);
    return node;
}

void SG_EXPORT sgSetRemoveNode(SGSet* set, SGSetNode* node)
{
    set->root = _sgSetNodeRemove(set, set->root, node);
}
void SG_EXPORT sgSetRemoveItem(SGSet* set, void* item)
{
    SGSetNode* node = sgSetSearch(set, item);
    if(!node)
        return;
    sgSetRemoveNode(set, node);
}

SGSetNode* SG_EXPORT sgSetGetRoot(SGSet* set)
{
    return set->root;
}
SGSetNode* SG_EXPORT sgSetGetFirst(SGSet* set)
{
    SGSetNode* curr = set->root;
    if(curr)
        while(curr->left)
            curr = curr->left;
    return curr;
}
SGSetNode* SG_EXPORT sgSetGetLast(SGSet* set)
{
    SGSetNode* curr = set->root;
    if(curr)
        while(curr->right)
            curr = curr->right;
    return curr;
}

void* SG_EXPORT sgSetPopRoot(SGSet* set)
{
    SGSetNode* node = sgSetGetRoot(set);
    if(!node)
        return NULL;
    void* item = node->item;
    sgSetRemoveNode(set, node);
    return item;
}
void* SG_EXPORT sgSetPopFirst(SGSet* set)
{
    SGSetNode* node = sgSetGetFirst(set);
    if(!node)
        return NULL;
    void* item = node->item;
    sgSetRemoveNode(set, node);
    return item;
}
void* SG_EXPORT sgSetPopLast(SGSet* set)
{
    SGSetNode* node = sgSetGetLast(set);
    if(!node)
        return NULL;
    void* item = node->item;
    sgSetRemoveNode(set, node);
    return item;
}
