#include "common.h"
#include "navmesh.h"

float _WMeshG(ANode* from, ANode* to)
{
    WVertex* fdata = from->data;
    WVertex* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return from->score.g + sqrt(dx*dx + dy*dy);
}
float _WMeshH(ANode* from, ANode* to)
{
    WVertex* fdata = from->data;
    WVertex* tdata = to->data;

    float dx = tdata->x - (float)fdata->x;
    float dy = tdata->y - (float)fdata->y;
    return sqrt(dx*dx + dy*dy);
}
int _WMeshGoal(ANode* from, ANode* to)
{
    return from == to;
}

int WLineIntersects(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* xp, float* yp)
{
    if((!(BOUNDS(x1, x2, x3) || BOUNDS(x1, x2, x4)) || !(BOUNDS(y1, y2, y3) || BOUNDS(y1, y2, y4)))
    && (!(BOUNDS(x3, x4, x1) || BOUNDS(x3, x4, x2)) || !(BOUNDS(y3, y4, y1) || BOUNDS(y3, y4, y2))))
        return 0;

    float f1 = x1*y2 - y1*x2;
    float f2 = x3*y4 - y3*x4;
    float x1m = x1 - x2;
    float y1m = y1 - y2;
    float x3m = x3 - x4;
    float y3m = y3 - y4;

    float den = x1m * y3m - y1m * x3m;
    float x = (f1 * x3m - f2 * x1m) / den;
    float y = (f1 * y3m - f2 * y1m) / den;

    if(xp != NULL)
        *xp = x;
    if(yp != NULL)
        *yp = y;

    return BOUNDS(x1, x2, x) && BOUNDS(x3, x4, x) && BOUNDS(y1, y2, y) && BOUNDS(y3, y4, y);
}

int WPolyInside(WPoly* poly, float x, float y)
{
    size_t i, j, c = 0;
    for (i = 0, j = poly->numverts-1; i < poly->numverts; j = i++)
    {
        if (((poly->verts[i]->y > y) != (poly->verts[j]->y > y))
        &&   (x < (poly->verts[j]->x - poly->verts[i]->x) * (y - poly->verts[i]->y) / (poly->verts[j]->y - poly->verts[i]->y) + poly->verts[i]->x))
        c = !c;
    }
    return c;
}

WMesh* WMeshCreate()
{
    WMesh* mesh = malloc(sizeof(WMesh));
    mesh->search = NULL;
    mesh->start = NULL;
    mesh->goal = NULL;
    mesh->polys = NULL;
    mesh->numpolys = 0;
    mesh->links = NULL;
    mesh->numlinks = 0;
    mesh->path = NULL;
    mesh->numpath = 0;

    /*
    for(fe = 0; fe < from->numverts; fe++)
    {
        fvert = from->verts[fe];
        for(te = 0; te < to->numverts; te++)
        {
            tvert = to->verts[te];
            //if(WLineIntersects(fedge->vert1->x, fedge->vert1->y))
            ARR_ADD(fedge->vert1->links, fedge->vert1->numlinks, to->verts[i]);
            ARR_ADD(fedge->vert2->links, fedge->vert2->numlinks, to->verts[i]);
        }
    }
    */

    return mesh;
}
void WMeshDestroy(WMesh* mesh) /// TODO - remove start/end
{
    if(mesh->search != NULL)
        ASearchDestroy(mesh->search);
    free(mesh->polys);
    free(mesh->links);
    free(mesh->path);
    free(mesh);
}
void WMeshSearchCreate(WMesh* mesh) /// TODO - optimize
{
    size_t a, b, c, d, e, f;
    int link;
    int slink;
    int glink;
    for(a = 0; a < mesh->numpolys; a++)
    {
        for(b = 0; b < mesh->numpolys; b++)
        {
            for(c = 0; c < mesh->numpolys; c++)
            {
                link = 1;
                for(f = 0; f < mesh->polys[c]->numedges; f++)
                {
                    if(!mesh->polys[c]->edges[f]->border && WLineIntersects(mesh->start->x, mesh->start->y
                                                                          , mesh->goal->x, mesh->goal->y
                                                                          , mesh->polys[c]->edges[f]->vert1->x, mesh->polys[c]->edges[f]->vert1->y
                                                                          , mesh->polys[c]->edges[f]->vert2->x, mesh->polys[c]->edges[f]->vert2->y
                                                                          , NULL
                                                                          , NULL))
                        link = 0;
                }
                if(link) // end here... we found the goal; TODO - width
                {
                    ANodeLink(mesh->start->node, mesh->goal->node);
                    //goto found;
                }

                for(d = 0; d < mesh->polys[a]->numverts; d++)
                {
                    glink = 1;
                    slink = 1;
                    for(f = 0; f < mesh->polys[c]->numedges; f++)
                    {
                        if(!mesh->polys[c]->edges[f]->border && WLineIntersects(mesh->start->x, mesh->start->y
                                                                              , mesh->polys[a]->verts[d]->x, mesh->polys[a]->verts[d]->y
                                                                              , mesh->polys[c]->edges[f]->vert1->x, mesh->polys[c]->edges[f]->vert1->y
                                                                              , mesh->polys[c]->edges[f]->vert2->x, mesh->polys[c]->edges[f]->vert2->y
                                                                              , NULL
                                                                              , NULL))
                            slink = 0;
                        if(!mesh->polys[c]->edges[f]->border && WLineIntersects(mesh->goal->x, mesh->goal->y
                                                                              , mesh->polys[a]->verts[d]->x, mesh->polys[a]->verts[d]->y
                                                                              , mesh->polys[c]->edges[f]->vert1->x, mesh->polys[c]->edges[f]->vert1->y
                                                                              , mesh->polys[c]->edges[f]->vert2->x, mesh->polys[c]->edges[f]->vert2->y
                                                                              , NULL
                                                                              , NULL))
                            glink = 0;
                    }
                    if(slink)
                        ANodeLink(mesh->start->node, mesh->polys[a]->verts[d]->node);
                    if(glink)
                        ANodeLink(mesh->goal->node, mesh->polys[a]->verts[d]->node);

                    for(e = 0; e < mesh->polys[b]->numverts; e++)
                    {
                        link = 1;
                        for(f = 0; f < mesh->polys[c]->numedges; f++)
                        {
                            if(!mesh->polys[c]->edges[f]->border && WLineIntersects(mesh->polys[a]->verts[d]->x       , mesh->polys[a]->verts[d]->y
                                                                                  , mesh->polys[b]->verts[e]->x       , mesh->polys[b]->verts[e]->y
                                                                                  , mesh->polys[c]->edges[f]->vert1->x, mesh->polys[c]->edges[f]->vert1->y
                                                                                  , mesh->polys[c]->edges[f]->vert2->x, mesh->polys[c]->edges[f]->vert2->y
                                                                                  , NULL
                                                                                  , NULL))
                                link = 0;
                        }
                        if(link)
                            ANodeLink(mesh->polys[a]->verts[d]->node, mesh->polys[b]->verts[e]->node);
                    }
                }
            }
        }
    }
found:

    mesh->search = ASearchCreate(mesh->start->node, mesh->goal->node, _WMeshG, _WMeshH, _WMeshGoal);
}
int WMeshSearchStep(WMesh* mesh)
{
    return ASearchStep(mesh->search);
}
WVertex** WMeshSearchPath(WMesh* mesh, size_t* pathlen)
{
    ANode** nodes = ASearchPath(mesh->search, &mesh->numpath);
    mesh->path = realloc(mesh->path, mesh->numpath * sizeof(WVertex*));
    size_t i;
    for(i = 0; i < mesh->numpath; i++)
        mesh->path[i] = nodes[i]->data;

    *pathlen = mesh->numpath;
    return mesh->path;
}
void WMeshAddStart(WMesh* mesh, float x, float y)
{
    size_t i;
    for(i = 0; i < mesh->numpolys; i++)
    {
        if(WPolyInside(mesh->polys[i], x, y))
        {
            free(mesh->start);
            mesh->start = malloc(sizeof(WVertex));
            mesh->start->node = ANodeCreate(mesh->start);
            mesh->start->x = x;
            mesh->start->y = y;

            mesh->start->links = NULL;
            mesh->start->numlinks = 0;
            return;
        }
    }
}
void WMeshAddGoal(WMesh* mesh, float x, float y)
{
    size_t i;
    for(i = 0; i < mesh->numpolys; i++)
    {
        if(WPolyInside(mesh->polys[i], x, y))
        {
            free(mesh->goal);
            mesh->goal = malloc(sizeof(WVertex));
            mesh->goal->node = ANodeCreate(mesh->goal);
            mesh->goal->x = x;
            mesh->goal->y = y;

            mesh->goal->links = NULL;
            mesh->goal->numlinks = 0;
            return;
        }
    }
}

WPoly* WPolyCreate(WMesh* mesh, float* x, float* y, size_t numverts)
{
    WPoly* poly = malloc(sizeof(WPoly));
    poly->mesh = mesh;
    ARR_ADD(mesh->polys, mesh->numpolys, poly);
    poly->links = NULL;
    poly->numlinks = 0;
    poly->verts = malloc(numverts * sizeof(WVertex*));
    poly->numverts = numverts;
    poly->edges = malloc(numverts * sizeof(WEdge*));
    poly->numedges = numverts;

    size_t i;
    for(i = 0; i < numverts; i++)
    {
        poly->verts[i] = malloc(sizeof(WVertex));
        poly->verts[i]->node = ANodeCreate(poly->verts[i]);
        poly->verts[i]->links = NULL;
        poly->verts[i]->numlinks = 0;
        poly->verts[i]->x = x[i];
        poly->verts[i]->y = y[i];
    }
    for(i = 0; i < numverts; i++)
    {
        poly->edges[i] = malloc(sizeof(WEdge));
        poly->edges[i]->border = 0;
        poly->edges[i]->links = NULL;
        poly->edges[i]->numlinks = 0;
        poly->edges[i]->vert1 = poly->verts[(i - 1 + numverts) % numverts];
        poly->edges[i]->vert2 = poly->verts[i];
    }

    return poly;
}
void WPolyDestroy(WPoly* poly) /// TODO - free polys (?)
{
    size_t i;
    free(poly->links);
    for(i = 0; i < poly->numverts; i++)
    {
        ANodeDestroy(poly->verts[i]->node);
        free(poly->verts[i]->links);
        free(poly->verts[i]);
    }
    free(poly->verts);
    for(i = 0; i < poly->numedges; i++)
    {
        free(poly->edges[i]->links);
        free(poly->edges[i]);
    }
    free(poly->edges);
    free(poly);
}
void WPolyLink(WPoly* from, WPoly* to)
{
    WPolyUnlink(from, to); // to prevent duplication

    ptrdiff_t fe, te;
    WEdge* fedge;
    WEdge* tedge;
    for(fe = 0; fe < from->numedges; fe++)
    {
        fedge = from->edges[fe];
        for(te = 0; te < to->numedges; te++)
        {
            tedge = to->edges[te];

#define CMP(Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2) \
        ( (((Ax1) == (Bx1)) && ((Ay1) == (By1))     \
       && ((Ax2) == (Bx2)) && ((Ay2) == (By2)))     \
       || (((Ax2) == (Bx1)) && ((Ay2) == (By1))     \
       && ((Ax1) == (Bx2)) && ((Ay1) == (By2))))

            // if the edges match...
            if(CMP(fedge->vert1->x, fedge->vert1->y, fedge->vert2->x, fedge->vert2->y
                  ,tedge->vert1->x, tedge->vert1->y, tedge->vert2->x, tedge->vert2->y))
            {
                fedge->border = 1;
                tedge->border = 1;
            }
#undef CMP
        }
    }
}
void WPolyDlink(WPoly* one, WPoly* two)
{
    WPolyLink(one, two);
    WPolyLink(two, one);
}
void WPolyUnlink(WPoly* from, WPoly* to) /// TODO
{

}
void WPolyDUnlink(WPoly* one, WPoly* two)
{
    WPolyUnlink(one, two);
    WPolyUnlink(two, one);
}
