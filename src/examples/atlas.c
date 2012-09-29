#include <siege/siege.h>

#include <stdlib.h>
#include <stdio.h>

#define WIDTH 640
#define HEIGHT 480

#define ASIZE 256
#define BORDER 0
#define NUMTEST 256

#define POS(i,j,w,h) (((j) * (w) + (i)) * 4)

SGubyte data[ASIZE*ASIZE];

void setPixel4ub(SGubyte* data, size_t i, size_t j, size_t w, size_t h, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    if(i >= w || j >= h)
        return;

    data[POS(i,j,w,h)+0] = r;
    data[POS(i,j,w,h)+1] = g;
    data[POS(i,j,w,h)+2] = b;
    data[POS(i,j,w,h)+3] = a;
}
void setPixel4f(SGubyte* data, size_t i, size_t j, size_t w, size_t h, float r, float g, float b, float a)
{
    setPixel4ub(data, i, j, w, h, (SGubyte)(r * 255), (SGubyte)(g * 255), (SGubyte)(b * 255), (SGubyte)(a * 255));
}
void fillArea(SGAtlas* atlas, SGAtlasArea* area)
{
    size_t i, j;
    for(i = 0; i < area->w; i++)
        for(j = 0; j < area->h; j++)
            setPixel4f(data, i, j, area->w, area->h, i / (float)area->w, j / (float)area->h, 0.5, 1.0);
    sgAtlasAreaSetData(atlas, area, area->w, area->h, 32, data);
}

int main(void)
{
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("STB-Image");

    sgInit(0);

    sgWindowOpen(WIDTH, HEIGHT, 32, 0);
    sgWindowSetTitle("SIEGE Atlas Demo");

    SGAtlas* atlas = sgAtlasCreate(ASIZE, ASIZE, 32);

    SGAtlasArea* area;

    size_t i;
    size_t num = 0;
    for(i = 0; i < NUMTEST; i++)
    {
        area = sgAtlasAreaReserve(atlas, BORDER + 12 + rand() % 5, BORDER + 12 + rand() % 5, SG_FALSE);
        if(area)
        {
            fillArea(atlas, area);
            num++;
        }
    }
    printf("Successfully inserted: %u/%u items\n", (unsigned int)num, NUMTEST);

    while(sgLoop(NULL))
    {
        sgDrawColor1f(1.0);
        sgAtlasDrawDBG(atlas, (WIDTH - ASIZE) / 2, (HEIGHT - ASIZE) / 2, 0, SG_FALSE);

        sgDrawColor3f(0.0, 1.0, 0.0);
        sgAtlasDrawDBG(atlas, (WIDTH - ASIZE) / 2, (HEIGHT - ASIZE) / 2, 0, SG_TRUE);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgAtlasDestroy(atlas);

    sgDeinit();

    return 0;
}
