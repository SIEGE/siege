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

float _EGridG(SGAStarNode* from, SGAStarNode* to);
float _EGridH(SGAStarNode* from, SGAStarNode* to);
int _EGridGoal(SGAStarNode* from, SGAStarNode* to);

EGrid* EGridCreate(size_t width, size_t height, char diag, char wdiag);
void EGridDestroy(EGrid* grid);
SGAStarNode* EGridGetNode(EGrid* grid, size_t x, size_t y);
EGridData* EGridGetData(EGrid* grid, size_t x, size_t y);
void EGridAddClear(EGrid* grid, size_t x, size_t y);
void EGridAddWall(EGrid* grid, size_t x, size_t y);
void EGridAddStart(EGrid* grid, size_t x, size_t y);
void EGridAddGoal(EGrid* grid, size_t x, size_t y);
void EGridSearchCreate(EGrid* grid);
int EGridSearchStep(EGrid* grid);
EGridData** EGridSearchPath(EGrid* grid, size_t* pathlen);

#endif // __SIEGE_AI_GRID_H__
