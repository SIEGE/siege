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

#ifndef __SIEGE_AI_GRID_H__
#define __SIEGE_AI_GRID_H__

#include "../common.h"
#include "astar.h"

#include <stdlib.h>

#define SG_PATH_GRID_CLEAR 0
#define SG_PATH_GRID_WALL  1
#define SG_PATH_GRID_START 2
#define SG_PATH_GRID_GOAL  3

typedef struct SGPathGridData
{
    SGuint x;
    SGuint y;
    SGenum type;
    float cost;
} SGPathGridData;

typedef struct SGPathGrid
{
    SGAStar* search;
    SGAStarNode*** grid;
    SGuint width;
    SGuint height;

    SGLinkedList* path;
    SGAStarNode* start;
    SGAStarNode* goal;

    SGbool done;
    SGbool diag;
    SGbool wdiag;
} SGPathGrid;

float SG_EXPORT _sgPathGridG(SGAStarNode* from, SGAStarNode* to);
float SG_EXPORT _sgPathGridH(SGAStarNode* from, SGAStarNode* to);
SGbool SG_EXPORT _sgPathGridGoal(SGAStarNode* from, SGAStarNode* to);

SGPathGrid* SG_EXPORT sgPathGridCreate(size_t width, size_t height, char diag, char wdiag);
void SG_EXPORT sgPathGridDestroy(SGPathGrid* grid);
SGAStarNode* SG_EXPORT sgPathGridGetNode(SGPathGrid* grid, size_t x, size_t y);
SGPathGridData* SG_EXPORT sgPathGridGetData(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT sgPathGridAddClear(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT sgPathGridAddWall(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT sgPathGridAddStart(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT sgPathGridAddGoal(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT sgPathGridSearchCreate(SGPathGrid* grid);
int SG_EXPORT sgPathGridSearchStep(SGPathGrid* grid);
SGLinkedList* SG_EXPORT sgPathGridSearchPath(SGPathGrid* grid, SGuint* pathlen);

#endif // __SIEGE_AI_GRID_H__
