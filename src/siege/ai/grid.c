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
#include <siege/ai/grid.h>

#include <math.h>

float SG_EXPORT _sgPathGridG(SGAStarNode* from, SGAStarNode* to)
{
    SGPathGridData* fdata = from->data;
    SGPathGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return from->score.g + sqrt(dx*dx + dy*dy) * tdata->cost;
}
float SG_EXPORT _sgPathGridH(SGAStarNode* from, SGAStarNode* to)
{
    SGPathGridData* fdata = from->data;
    SGPathGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return sqrt(dx*dx + dy*dy);
}
SGbool SG_EXPORT _sgPathGridGoal(SGAStarNode* from, SGAStarNode* to)
{
    return from == to;
}

SGPathGrid* SG_EXPORT sgPathGridCreate(SGuint width, SGuint height, SGbool diag, SGbool wdiag)
{
    SGuint x, y;
    SGPathGridData* data;
    SGPathGrid* grid = malloc(sizeof(SGPathGrid));
    grid->search = NULL;
    grid->grid = malloc(width * sizeof(SGAStarNode**));
    grid->width = width;
    grid->height = height;
    grid->path = sgLinkedListCreate();
    grid->start = NULL;
    grid->goal = NULL;

    grid->done = SG_FALSE;
    grid->diag = diag;
    grid->wdiag = wdiag;

    for(x = 0; x < width + 2; x++)
    {
        grid->grid[x] = malloc(height * sizeof(SGAStarNode*));
        for(y = 0; y < height + 2; y++)
        {
            data = malloc(sizeof(SGPathGridData));
            data->x = x - 1;
            data->y = y - 1;
            data->type = SG_PATH_GRID_CLEAR;
            data->cost = 1.0;
            grid->grid[x][y] = sgAStarNodeCreate(data);
        }
    }
    for(x = 1; x < width + 1; x++)
    {
        for(y = 1; y < height + 1; y++)
        {
            sgAStarNodeLink(grid->grid[x][y], grid->grid[x  ][y+1]);
            sgAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y  ]);
            sgAStarNodeLink(grid->grid[x][y], grid->grid[x  ][y-1]);
            sgAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y  ]);
            if(diag)
            {
                sgAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y+1]);
                sgAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y-1]);
                sgAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y-1]);
                sgAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y+1]);
            }
        }
    }

    // unlinking borders...
    for(x = 1; x < width + 1; x++)
    {
        sgAStarNodeDUnlink(grid->grid[x-1][1     ], grid->grid[x][0       ]);
        sgAStarNodeDUnlink(grid->grid[x  ][1     ], grid->grid[x][0       ]);
        sgAStarNodeDUnlink(grid->grid[x+1][1     ], grid->grid[x][0       ]);
        sgAStarNodeDUnlink(grid->grid[x-1][height], grid->grid[x][height+1]);
        sgAStarNodeDUnlink(grid->grid[x  ][height], grid->grid[x][height+1]);
        sgAStarNodeDUnlink(grid->grid[x+1][height], grid->grid[x][height+1]);
    }
    for(y = 1; y < height + 1; y++)
    {
        sgAStarNodeDUnlink(grid->grid[1    ][y+1], grid->grid[0      ][y]);
        sgAStarNodeDUnlink(grid->grid[1    ][y  ], grid->grid[0      ][y]);
        sgAStarNodeDUnlink(grid->grid[1    ][y-1], grid->grid[0      ][y]);
        sgAStarNodeDUnlink(grid->grid[width][y+1], grid->grid[width+1][y]);
        sgAStarNodeDUnlink(grid->grid[width][y  ], grid->grid[width+1][y]);
        sgAStarNodeDUnlink(grid->grid[width][y-1], grid->grid[width+1][y]);
    }
    sgAStarNodeDUnlink(grid->grid[1    ][1     ], grid->grid[0      ][0       ]);
    sgAStarNodeDUnlink(grid->grid[1    ][height], grid->grid[0      ][height+1]);
    sgAStarNodeDUnlink(grid->grid[width][height], grid->grid[width+1][height+1]);
    sgAStarNodeDUnlink(grid->grid[width][1     ], grid->grid[width+1][0       ]);

    return grid;
}
void SG_EXPORT sgPathGridDestroy(SGPathGrid* grid)
{
    if(grid->search != NULL)
        sgAStarDestroy(grid->search);
    sgLinkedListDestroy(grid->path);
    size_t x, y;
    for(x = 0; x < grid->width + 1; x++)
    {
        for(y = 0; y < grid->height + 1; y++)
        {
            free(grid->grid[x][y]->data);
            sgAStarNodeDestroy(grid->grid[x][y]);
        }
        free(grid->grid[x]);
    }
}
SGAStarNode* SG_EXPORT sgPathGridGetNode(SGPathGrid* grid, SGuint x, SGuint y)
{
    if(x >= grid->width || y >= grid->height)
        return NULL;
    return grid->grid[x+1][y+1];
}
SGPathGridData* SG_EXPORT sgPathGridGetData(SGPathGrid* grid, SGuint x, SGuint y)
{
    SGAStarNode* node = sgPathGridGetNode(grid, x, y);
    if(node == NULL)
        return NULL;
    return node->data;
}
void SG_EXPORT sgPathGridAddClear(SGPathGrid* grid, SGuint x, SGuint y)
{
    SGAStarNode* node = sgPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_CLEAR;
        x++;
        y++;
        sgAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x][y]);
        sgAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x][y]);
        sgAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x][y]);
        sgAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x][y]);
        if(grid->diag)
        {
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                sgAStarNodeLink(grid->grid[x-1][y+1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                sgAStarNodeLink(grid->grid[x-1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                sgAStarNodeLink(grid->grid[x+1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                sgAStarNodeLink(grid->grid[x+1][y+1], grid->grid[x][y]);
        }
        if(grid->wdiag)
        {
            if(((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
            {
                sgAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y+1]);
                sgAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y+1]);
            }
            if(((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)
            {
                sgAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x-1][y  ]);
                sgAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x-1][y  ]);
            }
            if(((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
            {
                sgAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y-1]);
                sgAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y-1]);
            }
            if(((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)
            {
                sgAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x+1][y  ]);
                sgAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x+1][y  ]);
            }
        }
    }
}
void SG_EXPORT sgPathGridAddWall(SGPathGrid* grid, SGuint x, SGuint y)
{
    SGAStarNode* node = sgPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_WALL;
        x++;
        y++;
        sgAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x][y]);
        sgAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x][y]);
        sgAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x][y]);
        sgAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x][y]);
        if(grid->diag)
        {
            sgAStarNodeUnlink(grid->grid[x-1][y+1], grid->grid[x][y]);
            sgAStarNodeUnlink(grid->grid[x-1][y-1], grid->grid[x][y]);
            sgAStarNodeUnlink(grid->grid[x+1][y-1], grid->grid[x][y]);
            sgAStarNodeUnlink(grid->grid[x+1][y+1], grid->grid[x][y]);
        }
        if(!grid->wdiag)
        {
            sgAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x-1][y  ]);
            sgAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x+1][y  ]);
            sgAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x  ][y+1]);
            sgAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x  ][y-1]);
            sgAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x-1][y  ]);
            sgAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x+1][y  ]);
            sgAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x  ][y+1]);
            sgAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x  ][y-1]);
        }
    }
}
void SG_EXPORT sgPathGridAddStart(SGPathGrid* grid, SGuint x, SGuint y)
{
    SGAStarNode* node = sgPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_START;
        grid->start = node;
    }
}
void SG_EXPORT sgPathGridAddGoal(SGPathGrid* grid, SGuint x, SGuint y)
{
    SGAStarNode* node = sgPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_GOAL;
        grid->goal = node;
    }
}
void SG_EXPORT sgPathGridSearchCreate(SGPathGrid* grid)
{
    grid->search = sgAStarCreate(grid->start, grid->goal, _sgPathGridG, _sgPathGridH, _sgPathGridGoal);
}
SGint SG_EXPORT sgPathGridSearchStep(SGPathGrid* grid)
{
    int s = sgAStarStep(grid->search);
    if(s != 0)
        grid->done = SG_TRUE;
    return s;
}
SGLinkedList* SG_EXPORT sgPathGridSearchPath(SGPathGrid* grid, SGuint* pathlen)
{
    sgLinkedListDestroy(grid->path);
    grid->path = sgLinkedListCreate();

    SGLinkedList* list = sgAStarPath(grid->search, pathlen);
    SGLinkedNode* node;
    SGAStarNode* anode;

    for(node = list->first; node != NULL; node = node->next)
    {
        anode = node->item;
        sgLinkedListAppend(grid->path, anode->data);
    }

    return grid->path;
}
