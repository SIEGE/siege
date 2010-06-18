#ifndef __NAVMESH_H__
#define __NAVMESH_H__

#include <stdlib.h>
#include "astar.h"

typedef struct WVertex
{
    ANode* node;

    float x;
    float y;

    struct WVertex** links;
    size_t numlinks;
} WVertex;

typedef struct WEdge
{
    int border;

    struct WVertex* vert1;
    struct WVertex* vert2;

    struct WEdge** links;
    size_t numlinks;
} WEdge;

typedef struct WPoly
{
    struct WMesh* mesh;

    struct WVertex** verts;
    size_t numverts;
    struct WEdge** edges;
    size_t numedges;

    struct WPoly** links;
    size_t numlinks;
} WPoly;

typedef struct WMesh
{
    ASearch* search;
    struct WVertex* start;
    struct WVertex* goal;
    struct WPoly** polys;
    size_t numpolys;

    struct WVertex** path;
    size_t numpath;
    struct WMesh** links;
    size_t numlinks;
} WMesh;

// 12,500,000 / s
// 28,571,429 / s
int WLineIntersects(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* x, float* y);
int WPolyInside(WPoly* poly, float x, float y);

WMesh* WMeshCreate();
void WMeshDestroy(WMesh* mesh);
void WMeshSearchCreate(WMesh* mesh);
int WMeshSearchStep(WMesh* mesh);
WVertex** WMeshSearchPath(WMesh* mesh, size_t* pathlen);
void WMeshAddStart(WMesh* mesh, float x, float y);
void WMeshAddGoal(WMesh* mesh, float x, float y);

WPoly* WPolyCreate(WMesh* mesh, float* x, float* y, size_t numverts);
void WPolyLink(WPoly* from, WPoly* to);
void WPolyDlink(WPoly* one, WPoly* two);
void WPolyUnlink(WPoly* from, WPoly* to);
void WPolyDUnlink(WPoly* one, WPoly* two);

#endif // __NAVMESH_H__
