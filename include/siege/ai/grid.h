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

#include <stdlib.h>

#define SG_AGRID_CLEAR 0
#define SG_AGRID_WALL  1
#define SG_AGRID_START 2
#define SG_AGRID_GOAL  3

typedef struct SGAGridData
{
	SGuint x;
	SGuint y;
	SGenum type;
	float cost;
} SGAGridData;

typedef struct SGAGrid
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
} SGAGrid;

float SG_EXPORT _sgAGridG(SGAStarNode* from, SGAStarNode* to);
float SG_EXPORT _sgAGridH(SGAStarNode* from, SGAStarNode* to);
SGbool SG_EXPORT _sgAGridGoal(SGAStarNode* from, SGAStarNode* to);

SGAGrid* SG_EXPORT sgAGridCreate(SGuint width, SGuint height, SGbool diag, SGbool wdiag);
void SG_EXPORT sgAGridDestroy(SGAGrid* grid);
SGAStarNode* SG_EXPORT sgAGridGetNode(SGAGrid* grid, SGuint x, SGuint y);
SGAGridData* SG_EXPORT sgAGridGetData(SGAGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgAGridAddClear(SGAGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgAGridAddWall(SGAGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgAGridAddStart(SGAGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgAGridAddGoal(SGAGrid* grid, SGuint x, SGuint y);
void SG_EXPORT sgAGridSearchCreate(SGAGrid* grid);
SGint SG_EXPORT sgAGridSearchStep(SGAGrid* grid);
SGLinkedList* SG_EXPORT sgAGridSearchPath(SGAGrid* grid, SGuint* pathlen);

#endif // __SIEGE_AI_GRID_H__
