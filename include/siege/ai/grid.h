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

#ifndef __SIEGE_AI_GRID_H__
#define __SIEGE_AI_GRID_H__

#include "../common.h"
#include "astar.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define SG_NAVGRID_CLEAR 0
#define SG_NAVGRID_WALL  1
#define SG_NAVGRID_START 2
#define SG_NAVGRID_GOAL  3

typedef struct SGNavGridData
{
	SGuint x;
	SGuint y;
	SGenum type;
	float cost;
} SGNavGridData;

typedef struct SGNavGrid
{
	SGAStar* search;
	SGAStarNode*** grid;
	SGuint width;
	SGuint height;

	SGList* path;
	SGAStarNode* start;
	SGAStarNode* goal;

	SGbool diag;
	SGbool wdiag;
} SGNavGrid;

float SG_CALL _sgNavGridG(SGAStarNode* from, SGAStarNode* to);
float SG_CALL _sgNavGridH(SGAStarNode* from, SGAStarNode* to);
SGbool SG_CALL _sgNavGridGoal(SGAStarNode* from, SGAStarNode* to);

SGNavGrid* SG_CALL sgNavGridCreate(SGuint width, SGuint height, SGbool diag, SGbool wdiag);
void SG_CALL sgNavGridDestroy(SGNavGrid* grid);
SGAStarNode* SG_CALL sgNavGridGetNode(SGNavGrid* grid, SGuint x, SGuint y);
SGNavGridData* SG_CALL sgNavGridGetData(SGNavGrid* grid, SGuint x, SGuint y);
void SG_CALL sgNavGridAddClear(SGNavGrid* grid, SGuint x, SGuint y);
void SG_CALL sgNavGridAddWall(SGNavGrid* grid, SGuint x, SGuint y);
void SG_CALL sgNavGridAddStart(SGNavGrid* grid, SGuint x, SGuint y);
void SG_CALL sgNavGridAddGoal(SGNavGrid* grid, SGuint x, SGuint y);
void SG_CALL sgNavGridSearchCreate(SGNavGrid* grid);
SGbool SG_CALL sgNavGridSearchStep(SGNavGrid* grid);
SGbool SG_CALL sgNavGridGoalFound(SGNavGrid* grid);
SGList* SG_CALL sgNavGridSearchPath(SGNavGrid* grid, size_t* pathlen);

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AI_GRID_H__
