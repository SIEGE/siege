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

float SG_EXPORT _SGPathGridG(SGAStarNode* from, SGAStarNode* to);
float SG_EXPORT _SGPathGridH(SGAStarNode* from, SGAStarNode* to);
SGbool SG_EXPORT _SGPathGridGoal(SGAStarNode* from, SGAStarNode* to);

SGPathGrid* SG_EXPORT SGPathGridCreate(size_t width, size_t height, char diag, char wdiag);
void SG_EXPORT SGPathGridDestroy(SGPathGrid* grid);
SGAStarNode* SG_EXPORT SGPathGridGetNode(SGPathGrid* grid, size_t x, size_t y);
SGPathGridData* SG_EXPORT SGPathGridGetData(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT SGPathGridAddClear(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT SGPathGridAddWall(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT SGPathGridAddStart(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT SGPathGridAddGoal(SGPathGrid* grid, size_t x, size_t y);
void SG_EXPORT SGPathGridSearchCreate(SGPathGrid* grid);
int SG_EXPORT SGPathGridSearchStep(SGPathGrid* grid);
SGLinkedList* SG_EXPORT SGPathGridSearchPath(SGPathGrid* grid, SGuint* pathlen);

#endif // __SIEGE_AI_GRID_H__
