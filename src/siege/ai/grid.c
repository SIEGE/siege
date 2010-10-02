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
/*
float _EGridG(SGAStarNode* from, SGAStarNode* to)
{
    EGridData* fdata = from->data;
    EGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return from->score.g + sqrt(dx*dx + dy*dy) * tdata->cost;
}
float _EGridH(SGAStarNode* from, SGAStarNode* to)
{
    EGridData* fdata = from->data;
    EGridData* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return sqrt(dx*dx + dy*dy);
}
int _EGridGoal(SGAStarNode* from, SGAStarNode* to)
{
    return from == to;
}

EGrid* EGridCreate(size_t width, size_t height, char diag, char wdiag)
{
    size_t x, y;
    EGridData* data;
    EGrid* grid = malloc(sizeof(EGrid));
    grid->search = NULL;
    grid->grid = malloc(width * sizeof(SGAStarNode**));
    grid->width = width;
    grid->height = height;
    grid->path = NULL;
    grid->numpath = 0;
    grid->start = NULL;
    grid->goal = NULL;

    grid->done = 0;
    grid->diag = diag;
    grid->wdiag = wdiag;

    for(x = 0; x < width + 2; x++)
    {
        grid->grid[x] = malloc(height * sizeof(SGAStarNode*));
        for(y = 0; y < height + 2; y++)
        {
            data = malloc(sizeof(EGridData));
            data->x = x - 1;
            data->y = y - 1;
            data->type = E_CLEAR;
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
void EGridDestroy(EGrid* grid)
{
    if(grid->search != NULL)
        SGAStarDestroy(grid->search);
    free(grid->path);
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
SGAStarNode* EGridGetNode(EGrid* grid, size_t x, size_t y)
{
    if(x >= grid->width || y >= grid->height)
        return NULL;
    return grid->grid[x+1][y+1];
}
EGridData* EGridGetData(EGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = EGridGetNode(grid, x, y);
    if(node == NULL)
        return NULL;
    return node->data;
}
void EGridAddClear(EGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = EGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((EGridData*)node->data)->type = E_CLEAR;
        x++;
        y++;
        SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x][y]);
        SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x][y]);
        if(grid->diag)
        {
            if(grid->wdiag || ((((EGridData*)grid->grid[x  ][y+1]->data)->type != E_WALL)
                           &&  (((EGridData*)grid->grid[x-1][y  ]->data)->type != E_WALL)))
                SGAStarNodeLink(grid->grid[x-1][y+1], grid->grid[x][y]);
            if(grid->wdiag || ((((EGridData*)grid->grid[x  ][y-1]->data)->type != E_WALL)
                           &&  (((EGridData*)grid->grid[x-1][y  ]->data)->type != E_WALL)))
                SGAStarNodeLink(grid->grid[x-1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((EGridData*)grid->grid[x  ][y-1]->data)->type != E_WALL)
                           &&  (((EGridData*)grid->grid[x+1][y  ]->data)->type != E_WALL)))
                SGAStarNodeLink(grid->grid[x+1][y-1], grid->grid[x][y]);
            if(grid->wdiag || ((((EGridData*)grid->grid[x  ][y+1]->data)->type != E_WALL)
                           &&  (((EGridData*)grid->grid[x+1][y  ]->data)->type != E_WALL)))
                SGAStarNodeLink(grid->grid[x+1][y+1], grid->grid[x][y]);
        }
        if(grid->wdiag)
        {
            printf("%d\n", grid->wdiag);
            if(((EGridData*)grid->grid[x  ][y+1]->data)->type != E_WALL)
            {
                SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y+1]);
                SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y+1]);
            }
            if(((EGridData*)grid->grid[x-1][y  ]->data)->type != E_WALL)
            {
                SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x-1][y  ]);
                SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x-1][y  ]);
            }
            if(((EGridData*)grid->grid[x  ][y-1]->data)->type != E_WALL)
            {
                SGAStarNodeLink(grid->grid[x-1][y  ], grid->grid[x  ][y-1]);
                SGAStarNodeLink(grid->grid[x+1][y  ], grid->grid[x  ][y-1]);
            }
            if(((EGridData*)grid->grid[x+1][y  ]->data)->type != E_WALL)
            {
                SGAStarNodeLink(grid->grid[x  ][y+1], grid->grid[x+1][y  ]);
                SGAStarNodeLink(grid->grid[x  ][y-1], grid->grid[x+1][y  ]);
            }
        }
    }
}
void EGridAddWall(EGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = EGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((EGridData*)node->data)->type = E_WALL;
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
void EGridAddStart(EGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = EGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((EGridData*)node->data)->type = E_START;
        grid->start = node;
    }
}
void EGridAddGoal(EGrid* grid, size_t x, size_t y)
{
    SGAStarNode* node = EGridGetNode(grid, x, y);
    if(node != NULL)
    {
        ((EGridData*)node->data)->type = E_GOAL;
        grid->goal = node;
    }
}
void EGridSearchCreate(EGrid* grid)
{
    grid->search = SGAStarCreate(grid->start, grid->goal, _EGridG, _EGridH, _EGridGoal);
}
int EGridSearchStep(EGrid* grid)
{
    int s = SGAStarStep(grid->search);
    if(s != 0)
        grid->done = 1;
    return s;
}
EGridData** EGridSearchPath(EGrid* grid, size_t* pathlen)
{
    SGAStarNode** nodes = SGAStarPath(grid->search, &grid->numpath);
    grid->path = realloc(grid->path, grid->numpath * sizeof(EGridData*));
    size_t i;
    for(i = 0; i < grid->numpath; i++)
        grid->path[i] = nodes[i]->data;

    *pathlen = grid->numpath;
    return grid->path;
}
*/
