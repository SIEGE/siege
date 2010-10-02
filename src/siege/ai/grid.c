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

float SG_EXPORT _SGPathGridG(SGAStarNode* from, SGAStarNode* to)
{
    SGPathGridData* fdata = from->data;
    SGPathGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return from->score.g + sqrt(dx*dx + dy*dy) * tdata->cost;
}
float SG_EXPORT _SGPathGridH(SGAStarNode* from, SGAStarNode* to)
{
    SGPathGridData* fdata = from->data;
    SGPathGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return sqrt(dx*dx + dy*dy);
}
SGbool SG_EXPORT _SGPathGridGoal(SGAStarNode* from, SGAStarNode* to)
{
    return from == to;
}

SGPathGrid* SG_EXPORT SGPathGridCreate(size_t width, size_t height, char diag, char wdiag)
{
    size_t x, y;
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
            grid->grid[x][y] = SGAStarNodeCreate(data);
        }
    }
    for(x = 1; x < width + 1; x++)
    {
        for(y = 1; y < height + 1; y++)
        {
            SGAStarNodeLink(grid->grid[x][y], grid->grid[x  ][y+1]);
            SGAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y  ]);
            SGAStarNodeLink(grid->grid[x][y], grid->grid[x  ][y-1]);
            SGAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y  ]);
            if(diag)
            {
                SGAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y+1]);
                SGAStarNodeLink(grid->grid[x][y], grid->grid[x-1][y-1]);
                SGAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y-1]);
                SGAStarNodeLink(grid->grid[x][y], grid->grid[x+1][y+1]);
            }
        }
    }

    // unlinking borders...
    for(x = 1; x < width + 1; x++)
    {
        SGAStarNodeDUnlink(grid->grid[x-1][1     ], grid->grid[x][0       ]);
        SGAStarNodeDUnlink(grid->grid[x  ][1     ], grid->grid[x][0       ]);
        SGAStarNodeDUnlink(grid->grid[x+1][1     ], grid->grid[x][0       ]);
        SGAStarNodeDUnlink(grid->grid[x-1][height], grid->grid[x][height+1]);
        SGAStarNodeDUnlink(grid->grid[x  ][height], grid->grid[x][height+1]);
        SGAStarNodeDUnlink(grid->grid[x+1][height], grid->grid[x][height+1]);
    }
    for(y = 1; y < height + 1; y++)
    {
        SGAStarNodeDUnlink(grid->grid[1    ][y+1], grid->grid[0      ][y]);
        SGAStarNodeDUnlink(grid->grid[1    ][y  ], grid->grid[0      ][y]);
        SGAStarNodeDUnlink(grid->grid[1    ][y-1], grid->grid[0      ][y]);
        SGAStarNodeDUnlink(grid->grid[width][y+1], grid->grid[width+1][y]);
        SGAStarNodeDUnlink(grid->grid[width][y  ], grid->grid[width+1][y]);
        SGAStarNodeDUnlink(grid->grid[width][y-1], grid->grid[width+1][y]);
    }
    SGAStarNodeDUnlink(grid->grid[1    ][1     ], grid->grid[0      ][0       ]);
    SGAStarNodeDUnlink(grid->grid[1    ][height], grid->grid[0      ][height+1]);
    SGAStarNodeDUnlink(grid->grid[width][height], grid->grid[width+1][height+1]);
    SGAStarNodeDUnlink(grid->grid[width][1     ], grid->grid[width+1][0       ]);

    return grid;
}
void SG_EXPORT SGPathGridDestroy(SGPathGrid* grid)
{
    if(grid->search != NULL)
        SGAStarDestroy(grid->search);
    sgLinkedListDestroy(grid->path);
    size_t x, y;
    for(x = 0; x < grid->width + 1; x++)
    {
        for(y = 0; y < grid->height + 1; y++)
        {
            free(grid->grid[x][y]->data);
            SGAStarNodeDestroy(grid->grid[x][y]);
        }
        free(grid->grid[x]);
    }
}
SGAStarNode* SG_EXPORT SGPathGridGetNode(SGPathGrid* grid, size_t x, size_t y)
{
    if(x >= grid->width || y >= grid->height)
        return NULL;
    return grid->grid[x+1][y+1];
}
SGPathGridData* SG_EXPORT SGPathGridGetData(SGPathGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = SGPathGridGetNode(grid, x, y);
    if(node == NULL)
        return NULL;
    return node->data;
}
void SG_EXPORT SGPathGridAddClear(SGPathGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = SGPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_CLEAR;
        x++;
        y++;
        SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x][y]);
        if(grid->diag)
        {
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                SGAStarNodeLink(grid->grid[x-1][y+1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                SGAStarNodeLink(grid->grid[x-1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                SGAStarNodeLink(grid->grid[x+1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
                           &&  (((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)))
                SGAStarNodeLink(grid->grid[x+1][y+1], grid->grid[x][y]);
        }
        if(grid->wdiag)
        {
            if(((SGPathGridData*)grid->grid[x  ][y+1]->data)->type != SG_PATH_GRID_WALL)
            {
                SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y+1]);
                SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y+1]);
            }
            if(((SGPathGridData*)grid->grid[x-1][y  ]->data)->type != SG_PATH_GRID_WALL)
            {
                SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x-1][y  ]);
                SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x-1][y  ]);
            }
            if(((SGPathGridData*)grid->grid[x  ][y-1]->data)->type != SG_PATH_GRID_WALL)
            {
                SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y-1]);
                SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y-1]);
            }
            if(((SGPathGridData*)grid->grid[x+1][y  ]->data)->type != SG_PATH_GRID_WALL)
            {
                SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x+1][y  ]);
                SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x+1][y  ]);
            }
        }
    }
}
void SG_EXPORT SGPathGridAddWall(SGPathGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = SGPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_WALL;
        x++;
        y++;
        SGAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x][y]);
        SGAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x][y]);
        SGAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x][y]);
        SGAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x][y]);
        if(grid->diag)
        {
            SGAStarNodeUnlink(grid->grid[x-1][y+1], grid->grid[x][y]);
            SGAStarNodeUnlink(grid->grid[x-1][y-1], grid->grid[x][y]);
            SGAStarNodeUnlink(grid->grid[x+1][y-1], grid->grid[x][y]);
            SGAStarNodeUnlink(grid->grid[x+1][y+1], grid->grid[x][y]);
        }
        if(!grid->wdiag)
        {
            SGAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x-1][y  ]);
            SGAStarNodeUnlink(grid->grid[x  ][y+1], grid->grid[x+1][y  ]);
            SGAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x  ][y+1]);
            SGAStarNodeUnlink(grid->grid[x-1][y  ], grid->grid[x  ][y-1]);
            SGAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x-1][y  ]);
            SGAStarNodeUnlink(grid->grid[x  ][y-1], grid->grid[x+1][y  ]);
            SGAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x  ][y+1]);
            SGAStarNodeUnlink(grid->grid[x+1][y  ], grid->grid[x  ][y-1]);
        }
    }
}
void SG_EXPORT SGPathGridAddStart(SGPathGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = SGPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_START;
        grid->start = node;
    }
}
void SG_EXPORT SGPathGridAddGoal(SGPathGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = SGPathGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((SGPathGridData*)node->data)->type = SG_PATH_GRID_GOAL;
        grid->goal = node;
    }
}
void SG_EXPORT SGPathGridSearchCreate(SGPathGrid* grid)
{
    grid->search = SGAStarCreate(grid->start, grid->goal, _SGPathGridG, _SGPathGridH, _SGPathGridGoal);
}
int SG_EXPORT SGPathGridSearchStep(SGPathGrid* grid)
{
    int s = SGAStarStep(grid->search);
    if(s != 0)
        grid->done = SG_TRUE;
    return s;
}
SGLinkedList* SG_EXPORT SGPathGridSearchPath(SGPathGrid* grid, SGuint* pathlen)
{
    sgLinkedListDestroy(grid->path);
    grid->path = sgLinkedListCreate();

    SGLinkedList* list = SGAStarPath(grid->search, pathlen);
    SGLinkedNode* node;
    SGAStarNode* anode;

    for(node = list->first; node != NULL; node = node->next)
    {
        anode = node->item;
        sgLinkedListAppend(grid->path, anode->data);
    }

    return grid->path;
}
