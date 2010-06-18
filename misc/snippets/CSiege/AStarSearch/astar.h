#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <stdlib.h>

struct ANode;
typedef float (*ACB_g)(struct ANode*, struct ANode*);
typedef float (*ACB_h)(struct ANode*, struct ANode*);
typedef int   (*ACB_isgoal)(struct ANode*, struct ANode*);

typedef struct ASearch
{
    struct
    {
        struct ANode** closed;
        size_t numclosed;
        struct ANode** open;
        size_t numopen;
    } set;
    struct ANode** path;
    size_t numpath;
    struct ANode* current;
    struct ANode* goal;

    struct
    {
        ACB_g g;
        ACB_h h;
        ACB_isgoal isgoal;
    } cb;
} ASearch;

typedef struct ANode
{
    struct
    {
        float g;
        float h;
        float f;
    } score;
    struct ANode** links;
    size_t numlinks;
    struct ANode* from;
    void* data; //userdata
} ANode;

ASearch* ASearchCreate(ANode* start, ANode* goal, ACB_g g, ACB_h h, ACB_isgoal isgoal);
void ASearchDestroy(ASearch* search);
int ASearchStep(ASearch* search);
ANode** ASearchPath(ASearch* search, size_t* pathlen); // reconstruct the path from the current node to the start; current node need not be the goal

ANode* ANodeCreate(void* data);
void ANodeDestroy(ANode* node);
void ANodeLink(ANode* from, ANode* to);
void ANodeDLink(ANode* one, ANode* two);
void ANodeUnlink(ANode* from, ANode* to);
void ANodeDUnlink(ANode* one, ANode* two);

#endif // __ASTAR_H__
