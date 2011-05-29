#include <siege/siege.h>

#include <stdlib.h>
#include <math.h>

int main(void)
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    //sgLoadModule("DevIL");
    sgInit(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE A-Star Demo");

    SGNavGrid* grid = sgNavGridCreate(640 / 32, 480 / 32, SG_TRUE, SG_FALSE);
    SGNavGridData* data;
    SGList* path = NULL;
    SGListNode* node;
    SGuint pathlen = 0;

    SGuint i, j;

    sgNavGridAddStart(grid, 1, 1);
    sgNavGridAddGoal(grid, 640 / 32 - 2, 480 / 32 - 2);

    srand(1);

    SGuint x, y;
    for(i = 0; i < 20 * 15 / 4; i++)
    {
        x = rand() % 20;
        y = rand() % 15;

        if((x == 1 && y == 1) || (x == 640 / 32 - 2 && y == 480 / 32 - 2))
        {
            i--;
            continue;
        }

        sgNavGridAddWall(grid, x, y);
    }

    sgNavGridSearchCreate(grid);
    while(!sgNavGridSearchStep(grid))
    {
    }
    if(sgNavGridGoalFound(grid))
        path = sgNavGridSearchPath(grid, &pathlen);

    while(sgLoop(NULL))
    {
        for(i = 0; i < grid->width; i++)
        {
            for(j = 0; j < grid->height; j++)
            {
                data = sgNavGridGetNode(grid, i, j)->data;
                switch(data->type)
                {
                    case SG_NAVGRID_CLEAR: sgDrawColor4f(0.25, 0.25, 0.25, 1.0); break;
                    case SG_NAVGRID_WALL:  sgDrawColor4f(0.0, 0.0, 0.0, 1.0); break;
                    case SG_NAVGRID_START: sgDrawColor4f(1.0, 0.0, 0.0, 1.0); break;
                    case SG_NAVGRID_GOAL:  sgDrawColor4f(0.0, 1.0, 0.0, 1.0); break;
                }
                sgDrawRectangle(i * 32, j * 32, i * 32 + 32, j * 32 + 32, 1);
            }
        }

        if(path)
        {
            sgDrawColor4f(1.0, 1.0, 1.0, 0.5);
            for(node = path->first; node != NULL; node = node->next)
            {
                data = node->item;
                sgDrawRectangle(data->x * 32, data->y * 32, data->x * 32 + 32, data->y * 32 + 32, 1);
            }
        }

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgNavGridDestroy(grid);

    sgDeinit();

    return 0;
}
