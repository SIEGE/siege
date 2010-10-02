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

#define E_CLEAR 0
#define E_WALL  1
#define E_START 2
#define E_GOAL  3

typedef struct EGrid
{
    SGAStar* search;
    SGAStarNode*** grid;
    size_t width;
    size_t height;

    struct EGridData** path;
    size_t numpath;
    SGAStarNode* start;
    SGAStarNode* goal;

    char done;
    char diag;
    char wdiag;
} EGrid;

typedef struct EGridData
{
    size_t x;
    size_t y;
    unsigned int type;
    float cost;
} EGridData;

float SG_EXPORT _EGridG(SGAStarNode* from, SGAStarNode* to);
float SG_EXPORT _EGridH(SGAStarNode* from, SGAStarNode* to);
int SG_EXPORT _EGridGoal(SGAStarNode* from, SGAStarNode* to);

EGrid* SG_EXPORT EGridCreate(size_t width, size_t height, char diag, char wdiag);
void SG_EXPORT EGridDestroy(EGrid* grid);
SGAStarNode* SG_EXPORT EGridGetNode(EGrid* grid, size_t x, size_t y);
EGridData* SG_EXPORT EGridGetData(EGrid* grid, size_t x, size_t y);
void SG_EXPORT EGridAddClear(EGrid* grid, size_t x, size_t y);
void SG_EXPORT EGridAddWall(EGrid* grid, size_t x, size_t y);
void SG_EXPORT EGridAddStart(EGrid* grid, size_t x, size_t y);
void SG_EXPORT EGridAddGoal(EGrid* grid, size_t x, size_t y);
void SG_EXPORT EGridSearchCreate(EGrid* grid);
int SG_EXPORT EGridSearchStep(EGrid* grid);
EGridData** SG_EXPORT EGridSearchPath(EGrid* grid, size_t* pathlen);

#endif // __SIEGE_AI_GRID_H__
