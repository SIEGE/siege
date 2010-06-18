#ifndef __GRID_H__
#define __GRID_H__

#include <stdlib.h>
#include "astar.h"

#define E_CLEAR 0
#define E_WALL  1
#define E_START 2
#define E_GOAL  3

typedef struct EGrid
{
    ASearch* search;
    ANode*** grid;
    size_t width;
    size_t height;

    struct EGridData** path;
    size_t numpath;
    ANode* start;
    ANode* goal;

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

float _EGridG(ANode* from, ANode* to);
float _EGridH(ANode* from, ANode* to);
int _EGridGoal(ANode* from, ANode* to);

EGrid* EGridCreate(size_t width, size_t height, char diag, char wdiag);
void EGridDestroy(EGrid* grid);
ANode* EGridGetNode(EGrid* grid, size_t x, size_t y);
EGridData* EGridGetData(EGrid* grid, size_t x, size_t y);
void EGridAddClear(EGrid* grid, size_t x, size_t y);
void EGridAddWall(EGrid* grid, size_t x, size_t y);
void EGridAddStart(EGrid* grid, size_t x, size_t y);
void EGridAddGoal(EGrid* grid, size_t x, size_t y);
void EGridSearchCreate(EGrid* grid);
int EGridSearchStep(EGrid* grid);
EGridData** EGridSearchPath(EGrid* grid, size_t* pathlen);

#endif // __GRID_H__
