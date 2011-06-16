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

#define SG_BUILD_LIBRARY
#include <siege/ai/astar.h>

#include <stdlib.h>

SGAStar* SG_EXPORT sgAStarCreate(SGAStarNode* start, SGAStarNode* goal, SGAStarScore g, SGAStarScore h, SGAStarIsGoal isgoal)
{
	SGAStar* search = malloc(sizeof(SGAStar));
	search->set.open = sgListCreate();
	sgListAppend(search->set.open, start);
	search->set.closed = sgListCreate();
	search->path = sgListCreate();
	search->current = NULL;
	search->goal = goal;
	search->gfound = SG_FALSE;

	search->cb.g = g;
	search->cb.h = h;
	search->cb.isgoal = isgoal;

	start->score.g = 0;
	start->score.h = h(start, goal);
	start->score.f = start->score.g + start->score.h;

	return search;
}
void SG_EXPORT sgAStarDestroy(SGAStar* search)
{
	sgListDestroy(search->set.open);
	sgListDestroy(search->set.closed);
	sgListDestroy(search->path);
	free(search);
}

// returns TRUE if done, FALSE if not done
SGbool SG_EXPORT sgAStarStep(SGAStar* search)
{
	// if the goal was already found, do nothing
	if(search->gfound == SG_TRUE)
		return SG_TRUE;

	if(!sgListLength(search->set.open))
	{
		search->gfound = SG_FALSE; // FAILURE
		return SG_TRUE;
	}

	SGListNode* finode = NULL;
	SGListNode* node;
	SGAStarNode* anode;
	float minf = SG_INF;
	for(node = search->set.open->first; node != NULL; node = node->next)
	{
		anode = node->item;
		if(anode->score.f <= minf) // we allow for == in order to allow for score.f to be SG_INF
		{
			finode = node;
			minf = anode->score.f;
		}
	}
	if(finode == NULL)
	{
		search->gfound = SG_FALSE; // FAILURE - some weird error just happened
		return SG_TRUE;
	}
	SGAStarNode* min = finode->item;
	search->current = min;

	if(search->cb.isgoal != NULL)
	{
		if(search->cb.isgoal(min, search->goal))
		{
			search->gfound = SG_TRUE; // SUCCESS
			return SG_TRUE;
		}
	}
	else if(min == search->goal) // fallback
	{
		search->gfound = SG_TRUE; // SUCCESS
		return SG_TRUE;
	}

	sgListRemoveNode(search->set.open, finode);
	sgListAppend(search->set.closed, min);

	SGbool inside;
	float teng;
	SGbool tenbetter;
	SGListNode* open;
	SGListNode* closed;
	for(node = min->links->first; node != NULL; node = node->next)
	{
		anode = node->item;

		inside = SG_FALSE;
		for(closed = search->set.closed->first; closed != NULL; closed = closed->next)
			if(anode == closed->item)
			{
				inside = SG_TRUE;
				break;
			}
		if(inside)
			continue;

		if(search->cb.g != NULL)
			teng = search->cb.g(min, anode);
		else // FALLBACK - cost is g+1 (the number of steps)
			teng = min->score.g + 1;

		inside = 0;
		for(open = search->set.open->first; open != NULL; open = open->next)
			if(anode == open->item)
			{
				inside = SG_TRUE;
				break;
			}
		if(!inside)
		{
			sgListAppend(search->set.open, anode);
			tenbetter = SG_TRUE;
		}
		else if(teng < anode->score.g)
			tenbetter = SG_TRUE;
		else
			tenbetter = SG_FALSE;
		if(tenbetter)
		{
			anode->from = min;
			anode->score.g = teng;
			if(search->cb.h != NULL)
				anode->score.h = search->cb.h(anode, search->goal);
			else // FALLBACK - assume 0 cost, turning this into a breath-first search (feeling optimistic today, aren't we?)
				anode->score.h = 0;
			anode->score.f = anode->score.g + anode->score.h;
		}
	}

	return SG_FALSE; // CONTINUE - didn't find the finish, we have to continue
}
SGbool SG_EXPORT sgAStarGoalFound(SGAStar* search)
{
	return search->gfound;
}
SGList* SG_EXPORT sgAStarPath(SGAStar* search, size_t* pathlen) // reconstruct the path from the current node to the start; current node need not be the goal
{
	// sgListClear(search->path);
	sgListDestroy(search->path);
	search->path = sgListCreate();

	if(pathlen != NULL)
		*pathlen = 0;

	SGAStarNode* current = search->current;
	while(current != NULL)
	{
		sgListAppend(search->path, current);
		current = current->from;

		if(pathlen != NULL)
			(*pathlen)++;
	}

	return search->path;
}

SGAStarNode* SG_EXPORT sgAStarNodeCreate(void* data)
{
	SGAStarNode* node = malloc(sizeof(SGAStarNode));
	node->from = NULL;
	node->links = sgListCreate();
	node->data = data;
	node->score.g = SG_INF;
	node->score.h = SG_INF;
	node->score.f = SG_INF;
	return node;
}
void SG_EXPORT sgAStarNodeDestroy(SGAStarNode* node)
{
	sgListDestroy(node->links);
	free(node);
}
void SG_EXPORT sgAStarNodeLink(SGAStarNode* from, SGAStarNode* to)
{
	sgAStarNodeUnlink(from, to); // to prevent duplication
	sgListAppend(from->links, to);
}
void SG_EXPORT sgAStarNodeDLink(SGAStarNode* one, SGAStarNode* two)
{
	sgAStarNodeLink(one, two);
	sgAStarNodeLink(two, one);
}
void SG_EXPORT sgAStarNodeUnlink(SGAStarNode* from, SGAStarNode* to)
{
	sgListRemoveItem(from->links, to);
}
void SG_EXPORT sgAStarNodeDUnlink(SGAStarNode* one, SGAStarNode* two)
{
	sgAStarNodeUnlink(one, two);
	sgAStarNodeUnlink(two, one);
}
