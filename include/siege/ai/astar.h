/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_AI_ASTAR_H__
#define __SIEGE_AI_ASTAR_H__

#include "../common.h"
#include "../util/list.h"

#include <stdlib.h>

struct SGAStarNode;

typedef float  SG_EXPORT (*SGAStarScore)(struct SGAStarNode*, struct SGAStarNode*);
typedef SGbool SG_EXPORT (*SGAStarIsGoal)(struct SGAStarNode*, struct SGAStarNode*);

typedef struct SGAStarNode
{
    struct SGAStarNode* from;
    SGLinkedList* links;
    void* data; // userdata

    struct
    {
        float g;
        float h;
        float f;
    } score;
} SGAStarNode;

typedef struct SGAStar
{
    struct
    {
        SGLinkedList* open;
        SGLinkedList* closed;
    } set;
    SGLinkedList* path;
    struct SGAStarNode* current;
    struct SGAStarNode* goal;

    struct
    {
        SGAStarScore g;
        SGAStarScore h;
        SGAStarIsGoal isgoal;
    } cb;
} SGAStar;

SGAStar* SG_EXPORT SGAStarCreate(SGAStarNode* start, SGAStarNode* goal, SGAStarScore g, SGAStarScore h, SGAStarIsGoal isgoal);
void SG_EXPORT SGAStarDestroy(SGAStar* search);
int SG_EXPORT SGAStarStep(SGAStar* search);
SGLinkedList* SG_EXPORT SGAStarPath(SGAStar* search, SGuint* pathlen); // reconstruct the path from the current node to the start; current node need not be the goal

SGAStarNode* SG_EXPORT SGAStarNodeCreate(void* data);
void SG_EXPORT SGAStarNodeDestroy(SGAStarNode* node);
void SG_EXPORT SGAStarNodeLink(SGAStarNode* from, SGAStarNode* to);
void SG_EXPORT SGAStarNodeDLink(SGAStarNode* one, SGAStarNode* two);
void SG_EXPORT SGAStarNodeUnlink(SGAStarNode* from, SGAStarNode* to);
void SG_EXPORT SGAStarNodeDUnlink(SGAStarNode* one, SGAStarNode* two);

#endif // __SIEGE_AI_ASTAR_H__
