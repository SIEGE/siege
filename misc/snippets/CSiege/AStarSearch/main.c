#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>

#include "astar.h"
#include "grid.h"
#undef main

#define WIDTH 640
#define HEIGHT 480
#define CELL 16

typedef struct Cell
{
    // walls
    int intact;
    int w;
    int a;
    int s;
    int d;

    size_t x;
    size_t y;
    unsigned int type;
} Cell;

#define DESTROY(a,b)                \
    {                               \
        current->intact = 0;        \
        current->a = 0;           \
        next[found]->intact = 0;    \
        next[found]->b = 0;       \
    }
void maze(EGrid* grid)
{
    srand(time(NULL));

    size_t width = WIDTH / CELL / 2;
    size_t height = HEIGHT / CELL / 2;
    size_t x, y;

    Cell** cells;
    cells = malloc(width * sizeof(Cell*));
    for(x = 0; x < width; x++)
    {
        cells[x] = malloc(height * sizeof(Cell));
        for(y = 0; y < height; y++)
        {
            cells[x][y].intact = 1;
            cells[x][y].w = 1;
            cells[x][y].a = 1;
            cells[x][y].s = 1;
            cells[x][y].d = 1;

            cells[x][y].x = x;
            cells[x][y].y = y;
            cells[x][y].type = E_CLEAR;
        }
    }

    Cell** stack = NULL;
    size_t numstack = 0;
    size_t total = width * height;
    size_t visited = 1;
    x = rand() % width;
    y = rand() % height;
    Cell* current = &cells[x][y];

    Cell* next[4];
    int found;

    while(visited < total)
    {
        x = current->x;
        y = current->y;

        memset(next, 0, 4 * sizeof(Cell*));
        found = 0;
        if(y > 0 && cells[x][y-1].intact)
        {
            next[0] = &cells[x][y-1];
            found++;
        }
        if(x > 0 && cells[x-1][y].intact)
        {
            next[1] = &cells[x-1][y];
            found++;
        }
        if(y < height-1 && cells[x][y+1].intact)
        {
            next[2] = &cells[x][y+1];
            found++;
        }
        if(x < width-1 && cells[x+1][y].intact)
        {
            next[3] = &cells[x+1][y];
            found++;
        }
        if(found > 0)
        {
            do
                found = rand() % 4;
            while(next[found] == NULL);
            if(found == 0) // w
                DESTROY(w, s);
            if(found == 1) // a
                DESTROY(a, d);
            if(found == 2) // s
                DESTROY(s, w);
            if(found == 3) // d
                DESTROY(d, a);
            stack = realloc(stack, (numstack + 1) * sizeof(Cell*));
            stack[numstack++] = current;

            current = next[found];
            visited++;
        }
        else
        {
            current = stack[--numstack];
            stack = realloc(stack, numstack * sizeof(Cell*));
        }
    }

    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            current = &cells[x][y];
            EGridAddWall(grid, 2*x+1, 2*y+1);
            if(current->d)
                EGridAddWall(grid, 2*x+1, 2*y);
            if(current->s)
                EGridAddWall(grid, 2*x, 2*y+1);
        }
    }
    found = rand() % 4;
    if(found == 0) //wa
    {
        EGridAddStart(grid, 0, 0);
        EGridAddGoal(grid, 2*(width-1), 2*(height-1));
    }
    if(found == 1) //as
    {
        EGridAddStart(grid, 0, 2*(height-1));
        EGridAddGoal(grid, 2*(width-1), 0);
    }
    if(found == 2) //sd
    {
        EGridAddStart(grid, 2*(width-1), 2*(height-1));
        EGridAddGoal(grid, 0, 0);
    }
    if(found == 3) //dw
    {
        EGridAddStart(grid, 2*(width-1), 0);
        EGridAddGoal(grid, 0, 2*(height-1));
    }

    free(stack);
    for(x = 0; x < width; x++)
        free(cells[x]);
    free(cells);
}
#undef DESTROY

void drawGrid(EGrid* grid);

SDL_Event event;
SDL_Surface* window;
EGrid* grid;
EGridData** data;
int done = SDL_FALSE;
char sready = 0;
char lmouse = 0;
char rmouse = 0;
char mmouse = 0;
int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL);

    glEnable( GL_TEXTURE_2D );
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -256, 256);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    grid = EGridCreate(WIDTH / CELL, HEIGHT / CELL, 1, 0);
    EGridAddStart(grid, 1, 1);
    EGridAddGoal(grid, WIDTH / CELL - 2, HEIGHT / CELL - 2);
    //maze(grid);

    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        lmouse = 1;
                    if(event.button.button == SDL_BUTTON_RIGHT)
                        rmouse = 1;
                    if(event.button.button == SDL_BUTTON_MIDDLE)
                        mmouse = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        lmouse = 0;
                    if(event.button.button == SDL_BUTTON_RIGHT)
                        rmouse = 0;
                    //if(event.button.button == SDL_BUTTON_MIDDLE)
                    //    mmouse = 0;
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE)
                        EGridSearchCreate(grid);
                    break;

                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;
            }
        }

        if(lmouse)
            EGridAddWall(grid, event.button.x / CELL, event.button.y / CELL);
        if(rmouse)
            EGridAddClear(grid, event.button.x / CELL, event.button.y / CELL);
        if(mmouse)
        {
            EGridSearchStep(grid);
            sready = 1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        drawGrid(grid);

        SDL_GL_SwapBuffers();
    }

    EGridDestroy(grid);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

void drawGrid(EGrid* grid)
{
    size_t x, y;
    EGridData* data;
    EGridData** path;
    glBegin(GL_QUADS);
    for(x = 0; x < WIDTH / CELL; x++)
    {
        for(y = 0; y < HEIGHT / CELL; y++)
        {
            data = EGridGetData(grid, x, y);
            switch(data->type)
            {
                case E_CLEAR:
                    glColor4f(0.75, 0.75, 0.75, 1.0);
                    break;
                case E_WALL:
                    glColor4f(0.25, 0.25, 0.25, 1.0);
                    break;
                case E_START:
                    glColor4f(1.0, 0.5, 0.5, 1.0);
                    break;
                case E_GOAL:
                    glColor4f(0.5, 1.0, 0.5, 1.0);
                    break;
            }
            glVertex2f(x * CELL       , y * CELL       );
            glVertex2f(x * CELL       , y * CELL + CELL);
            glVertex2f(x * CELL + CELL, y * CELL + CELL);
            glVertex2f(x * CELL + CELL, y * CELL       );
        }
    }
    glEnd();

    glBegin(GL_LINES);
    glColor4f(0.5, 0.5, 0.5, 1.0);
    for(x = 0; x < WIDTH / CELL; x++)
    {
        for(y = 0; y < HEIGHT / CELL; y++)
        {
            glVertex2f(x * CELL       , y * CELL + CELL);
            glVertex2f(x * CELL + CELL, y * CELL + CELL);
            glVertex2f(x * CELL + CELL, y * CELL + CELL);
            glVertex2f(x * CELL + CELL, y * CELL       );
        }
    }
    glEnd();

    if(sready)
    {
        path = EGridSearchPath(grid, &y);

        glBegin(GL_QUADS);
        glColor4f(0.5, 0.0, 0.5, 0.1);
        for(x = 0; x < y; x++)
        {
            glVertex2f(path[x]->x * CELL       , path[x]->y * CELL       );
            glVertex2f(path[x]->x * CELL       , path[x]->y * CELL + CELL);
            glVertex2f(path[x]->x * CELL + CELL, path[x]->y * CELL + CELL);
            glVertex2f(path[x]->x * CELL + CELL, path[x]->y * CELL       );
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        for(x = 0; x < y; x++)
        {
            glVertex2f(path[x]->x * CELL + CELL/2, path[x]->y * CELL + CELL/2);
        }
        glEnd();
    }
}
