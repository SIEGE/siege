#include "common.h"
#include "astar.h"

ASearch* ASearchCreate(ANode* start, ANode* goal, ACB_g g, ACB_h h, ACB_isgoal isgoal)
{
    ASearch* search = malloc(sizeof(ASearch));
    search->set.closed = NULL;
    search->set.numclosed = 0;
    search->set.open = malloc(sizeof(ANode*));
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
void ASearchDestroy(ASearch* search)
{
    free(search->set.open);
    free(search->set.closed);
    free(search->path);
    free(search);
}
// returns TRUE if found, FALSE if not found, -1 on error
int ASearchStep(ASearch* search)
{
    if(search->set.numopen == 0)
        return -1; // FAILURE

    size_t minfi = search->set.numopen; // impossible value
    size_t i, j;
    float minf = INFINITY;
    for(i = 0; i < search->set.numopen; i++)
    {
        if(search->set.open[i]->score.f <= minf) // we allow for == in order to allow for score.f to be INFINITY
        {
            minfi = i;
            minf = search->set.open[i]->score.f;
        }
    }
    if(minfi == search->set.numopen)
        return -1; // FAILURE - some weird error just happened
    ANode* min = search->set.open[minfi];
    search->current = min;

    if(search->cb.isgoal != NULL)
    {
        if(search->cb.isgoal(min, search->goal))
            return 1; // SUCCESS
    }
    else if(min == search->goal) // fallback
        return 1;

    ARR_REMOVE(search->set.open, search->set.numopen, minfi);
    //memmove(&search->set.open[minfi], &search->set.open[minfi+1], (search->set.numopen - (minfi + 1)) * sizeof(ANode*));
    //search->set.open = realloc(search->set.open, (search->set.numopen - 1) * sizeof(ANode*));
    //search->set.numopen--;

    ARR_ADD(search->set.closed, search->set.numclosed, min);
    //search->set.closed = realloc(search->set.closed, (search->set.numclosed + 1) * sizeof(ANode*));
    //search->set.closed[search->set.numclosed] = min;
    //search->set.numclosed++;

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
ANode** ASearchPath(ASearch* search, size_t* pathlen) // reconstruct the path from the current node to the start; current node need not be the goal
{
    search->numpath = 0;
    ANode* current = search->current;
    while(current != NULL)
    {
        ARR_ADD(search->path, search->numpath, current);
        current = current->from;
    }

    if(pathlen != NULL)
        *pathlen = search->numpath;

    return search->path;
}

ANode* ANodeCreate(void* data)
{
    ANode* node = malloc(sizeof(ANode));
    node->score.g = INFINITY;
    node->score.h = INFINITY;
    node->score.f = INFINITY;
    node->links = NULL;
    node->numlinks = 0;
    node->from = NULL;
    node->data = data;
    return node;
}
void ANodeDestroy(ANode* node)
{
    free(node->links);
    free(node);
}
void ANodeLink(ANode* from, ANode* to)
{
    ANodeUnlink(from, to); // to prevent duplication
    ARR_ADD(from->links, from->numlinks, to);
    //from->links = realloc(from->links, (from->numlinks + 1) * sizeof(ANode*));
    //from->links[(from->numlinks)++] = to;
}
void ANodeDLink(ANode* one, ANode* two)
{
    ANodeLink(one, two);
    ANodeLink(two, one);
}
void ANodeUnlink(ANode* from, ANode* to)
{
    size_t i;
    for(i = 0; i < from->numlinks; i++)
        if(from->links[i] == to)
        {
            ARR_REMOVE(from->links, from->numlinks, i);
            return;
        }
}
void ANodeDUnlink(ANode* one, ANode* two)
{
    ANodeUnlink(one, two);
    ANodeUnlink(two, one);
}
