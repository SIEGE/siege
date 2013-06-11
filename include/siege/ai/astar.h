/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_AI_ASTAR_H__
#define __SIEGE_AI_ASTAR_H__

#include "../common.h"
#include "../util/list.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct SGAStarNode;

typedef float  SG_CALL (*SGAStarScore)(struct SGAStarNode*, struct SGAStarNode*);
typedef SGbool SG_CALL (*SGAStarIsGoal)(struct SGAStarNode*, struct SGAStarNode*);

typedef struct SGAStarNode
{
    struct SGAStarNode* from;
    SGList* links;
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
        SGList* open;
        SGList* closed;
    } set;
    SGList* path;
    struct SGAStarNode* current;
    struct SGAStarNode* goal;
    SGbool gfound;

    struct
    {
        SGAStarScore g;
        SGAStarScore h;
        SGAStarIsGoal isgoal;
    } cb;
} SGAStar;

SGAStar* SG_CALL sgAStarCreate(SGAStarNode* start, SGAStarNode* goal, SGAStarScore g, SGAStarScore h, SGAStarIsGoal isgoal);
void SG_CALL sgAStarDestroy(SGAStar* search);
SGbool SG_CALL sgAStarStep(SGAStar* search);
SGbool SG_CALL sgAStarGoalFound(SGAStar* search);
SGList* SG_CALL sgAStarPath(SGAStar* search, size_t* pathlen); // reconstruct the path from the current node to the start; current node need not be the goal

SGAStarNode* SG_CALL sgAStarNodeCreate(void* data);
void SG_CALL sgAStarNodeDestroy(SGAStarNode* node);
void SG_CALL sgAStarNodeLink(SGAStarNode* from, SGAStarNode* to);
void SG_CALL sgAStarNodeDLink(SGAStarNode* one, SGAStarNode* two);
void SG_CALL sgAStarNodeUnlink(SGAStarNode* from, SGAStarNode* to);
void SG_CALL sgAStarNodeDUnlink(SGAStarNode* one, SGAStarNode* two);

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AI_ASTAR_H__
