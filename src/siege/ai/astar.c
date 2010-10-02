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

#define SG_BUILD_LIBRARY
#include <siege/ai/astar.h>

SGAStar* SG_EXPORT SGAStarCreate(SGAStarNode* start, SGAStarNode* goal, SGAStarScore g, SGAStarScore h, SGAStarIsGoal isgoal)
{
    SGAStar* search = malloc(sizeof(SGAStar));
    search->set.closed = NULL;
    search->set.numclosed = 0;
    search->set.open = malloc(sizeof(SGAStarNode*));
    search->set.open[0] = start;
    search->set.numopen = 1;
    search->path = NULL;
    search->numpath = 0;
    search->current = NULL;
    search->goal = goal;

    search->cb.g = g;
    search->cb.h = h;
    search->cb.isgoal = isgoal;

    start->score.g = 0;
    start->score.h = h(start, goal);
    start->score.f = start->score.g + start->score.h;

    return search;
}
void SG_EXPORT SGAStarDestroy(SGAStar* search)
{
    free(search->set.open);
    free(search->set.closed);
    free(search->path);
    free(search);
}
// returns TRUE if found, FALSE if not found, -1 on error
int SG_EXPORT SGAStarStep(SGAStar* search)
{
    if(search->set.numopen == 0)
        return -1; // FAILURE

    size_t minfi = search->set.numopen; // impossible value
    size_t i, j;
    float minf = SG_INF;
    for(i = 0; i < search->set.numopen; i++)
    {
        if(search->set.open[i]->score.f <= minf) // we allow for == in order to allow for score.f to be SG_INF
        {
            minfi = i;
            minf = search->set.open[i]->score.f;
        }
    }
    if(minfi == search->set.numopen)
        return -1; // FAILURE - some weird error just happened
    SGAStarNode* min = search->set.open[minfi];
    search->current = min;

    if(search->cb.isgoal != NULL)
    {
        if(search->cb.isgoal(min, search->goal))
            return 1; // SUCCESS
    }
    else if(min == search->goal) // fallback
        return 1;

    ARR_REMOVE(search->set.open, search->set.numopen, minfi);

    ARR_ADD(search->set.closed, search->set.numclosed, min);

    char inside;
    float teng;
    char tenbetter;
    for(i = 0; i < min->numlinks; i++)
    {
        inside = 0;
        for(j = 0; j < search->set.numclosed; j++)
            if(min->links[i] == search->set.closed[j])
            {
                inside = 1;
                break;
            }
        if(inside)
            continue;

        if(search->cb.g != NULL)
            teng = search->cb.g(min, min->links[i]);
        else // FALLBACK - cost is g+1 (the number of steps)
            teng = min->score.g + 1;

        inside = 0;
        for(j = 0; j < search->set.numopen; j++)
            if(min->links[i] == search->set.open[j])
            {
                inside = 1;
                break;
            }
        if(!inside)
        {
            ARR_ADD(search->set.open, search->set.numopen, min->links[i]);
            tenbetter = 1;
        }
        else if(teng < min->links[i]->score.g)
            tenbetter = 1;
        else
            tenbetter = 0;
        if(tenbetter)
        {
            min->links[i]->from = min;
            min->links[i]->score.g = teng;
            if(search->cb.h != NULL)
                min->links[i]->score.h = search->cb.h(min->links[i], search->goal);
            else // FALLBACK - assume 0 cost, turning this into a breath-first search (feeling optimistic today, aren't we?)
                min->links[i]->score.h = 0;
            min->links[i]->score.f = min->links[i]->score.g + min->links[i]->score.h;
        }
    }

    return 0; // CONTINUE - didn't find the finish, we have to continue
}
SGAStarNode** SG_EXPORT SGAStarPath(SGAStar* search, size_t* pathlen) // reconstruct the path from the current node to the start; current node need not be the goal
{
    search->numpath = 0;
    SGAStarNode* current = search->current;
    while(current != NULL)
    {
        ARR_ADD(search->path, search->numpath, current);
        current = current->from;
    }

    if(pathlen != NULL)
        *pathlen = search->numpath;

    return search->path;
}

SGAStarNode* SG_EXPORT SGAStarNodeCreate(void* data)
{
    SGAStarNode* node = malloc(sizeof(SGAStarNode));
    node->score.g = SG_INF;
    node->score.h = SG_INF;
    node->score.f = SG_INF;
    node->links = NULL;
    node->numlinks = 0;
    node->from = NULL;
    node->data = data;
    return node;
}
void SG_EXPORT SGAStarNodeDestroy(SGAStarNode* node)
{
    free(node->links);
    free(node);
}
void SG_EXPORT SGAStarNodeLink(SGAStarNode* from, SGAStarNode* to)
{
    SGAStarNodeUnlink(from, to); // to prevent duplication
    ARR_ADD(from->links, from->numlinks, to);
}
void SG_EXPORT SGAStarNodeDLink(SGAStarNode* one, SGAStarNode* two)
{
    SGAStarNodeLink(one, two);
    SGAStarNodeLink(two, one);
}
void SG_EXPORT SGAStarNodeUnlink(SGAStarNode* from, SGAStarNode* to)
{
    size_t i;
    for(i = 0; i < from->numlinks; i++)
        if(from->links[i] == to)
        {
            ARR_REMOVE(from->links, from->numlinks, i);
            return;
        }
}
void SG_EXPORT SGAStarNodeDUnlink(SGAStarNode* one, SGAStarNode* two)
{
    SGAStarNodeUnlink(one, two);
    SGAStarNodeUnlink(two, one);
}
