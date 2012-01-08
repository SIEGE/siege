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

float SG_EXPORT _sgNavGridG(SGAStarNode* from, SGAStarNode* to);
float SG_EXPORT _sgNavGridH(SGAStarNode* from, SGAStarNode* to);
SGbool SG_EXPORT _sgNavGridGoal(SGAStarNode* from, SGAStarNode* to);

SGNavGrid* SG_EXPORT sgNavGridCreate(SGuint width, SGuint height, SGbool diag, SGbool wdiag);
void SG_EXPORT sgNavGridDestroy(SGNavGrid* grid);
SGAStarNode* SG_EXPORT sgNavGridGetNode(SGNavGrid* grid, SGuint x, SGuint y);
SGNavGridData* SG_EXPORT sgNavGridGetData(SGNavGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgNavGridAddClear(SGNavGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgNavGridAddWall(SGNavGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgNavGridAddStart(SGNavGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgNavGridAddGoal(SGNavGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgNavGridSearchCreate(SGNavGrid* grid);
SGbool SG_EXPORT sgNavGridSearchStep(SGNavGrid* grid);
SGbool SG_EXPORT sgNavGridGoalFound(SGNavGrid* grid);
SGList* SG_EXPORT sgNavGridSearchPath(SGNavGrid* grid, size_t* pathlen);

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AI_GRID_H__
