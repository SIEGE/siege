#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include <SDL/sdl.h>

typedef struct Texture
{
    size_t width;
    size_t height;
    size_t bpp;
    uint32_t flags;

    struct Buffer** buffers;
    size_t numbuffers;
} Texture;

typedef struct Buffer
{
    struct Texture* texture;
    size_t width;
    size_t height;
    size_t bpp;
    uint32_t flags;

    float* data;
    char* cdata;
} Buffer;

float _ptInterpolateLinear(float a, float b, float x)
{
    return a * (1-x) + b * x;
}

Texture* ptTextureCreate(size_t width, size_t height, size_t bpp, uint32_t flags)
{
    Texture* texture = malloc(sizeof(Texture));
    texture->width = width;
    texture->height = height;
    texture->bpp = bpp;
    texture->flags = flags;

    texture->buffers = NULL;
    texture->numbuffers = 0;
    return texture;
}
void ptTextureDestroy(Texture* texture)
{
    free(texture->buffers);
    free(texture);
}

Buffer* ptBufferCreate(Texture* texture, size_t width, size_t height, size_t bpp, uint32_t flags)
{
    Buffer* buffer = malloc(sizeof(Buffer));

    texture->buffers = realloc(texture->buffers, (texture->numbuffers + 1) * sizeof(Buffer*));
    texture->numbuffers++;

    buffer->texture = texture;
    buffer->width = width;
    buffer->height = height;
    buffer->bpp = bpp;
    buffer->flags = flags;

    buffer->data = malloc(width * height * bpp * sizeof(float));
    buffer->cdata = NULL;
    return buffer;
}
void ptBufferDestroy(Buffer* buffer)
{
    size_t i;
    for(i = 0; i < buffer->texture->numbuffers; i++)
        if(buffer->texture->buffers[i] == buffer)
        {
            buffer->texture->numbuffers--;
            memmove(buffer->texture->buffers[i], buffer->texture->buffers[i+1], (buffer->texture->numbuffers - i) * sizeof(Buffer*));
            buffer->texture->buffers = realloc(buffer->texture->buffers, buffer->texture->numbuffers * sizeof(Buffer*));
            break;
        }

    free(buffer->data);
    free(buffer->cdata);
    free(buffer);
}

#define PT_INTERP_NEAREST 0
#define PT_INTERP_LINEAR  1
void ptScale(Buffer* buffer, size_t width, size_t height, uint32_t interpolation)
{
    float* newdata = malloc(width * height * buffer->bpp * sizeof(float));

    float xratio = width / (float)buffer->width;
    float yratio = height / (float)buffer->height;

    size_t x;
    size_t y;
    for(x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            float bx = x / xratio;
            float by = y / yratio;
            float add1 = _ptInterpolateLinear(buffer->data[(size_t)((y * buffer->width / yratio + x / xratio)*buffer->bpp)], ceil(bx), fmod(bx, 1));
            newdata[(y * width + x)*buffer->bpp+0] = buffer->data[(size_t)((y * buffer->width / yratio + x / xratio)*buffer->bpp)];
            newdata[(y * width + x)*buffer->bpp+1] = 1.0;
            newdata[(y * width + x)*buffer->bpp+2] = 1.0;
            newdata[(y * width + x)*buffer->bpp+3] = 1.0;
        }
    }

    free(buffer->data);
    buffer->data = newdata;
}

void ptNoiseValue(Buffer* buffer, int undersample, bool loopx, bool loopy)
{
    size_t nw = buffer->width >> undersample;
    size_t nh = buffer->height >> undersample;

    float* nf = malloc((nw + 1) * (nh + 1) * sizeof(float));

    size_t x;
    size_t y;
    for(x = 0; x < buffer->width; x++)
        for(y = 0; y < buffer->height; y++)
        {
            nf[(y << undersample) * nw + (x << undersample)] = rand() / (float)RAND_MAX;
            buffer->data[(y * buffer->width + x)*buffer->bpp+0] =
            buffer->data[(y * buffer->width + x)*buffer->bpp+1] =
            buffer->data[(y * buffer->width + x)*buffer->bpp+2] = nf[y * buffer->width + x];
            buffer->data[(y * buffer->width + x)*buffer->bpp+3] = 1.0;
        }

    free(nf);
}
void ptBufferFinalizeRGBA32(Buffer* buffer)
{
    buffer->cdata = realloc(buffer->cdata, buffer->width * buffer->height * buffer->bpp);

    size_t i;
    for(i = 0; i < buffer->width * buffer->height * buffer->bpp; i++)
        buffer->cdata[i] = (uint8_t)(buffer->data[i] * 0xFF);
}

#define WIDTH 512
#define HEIGHT 512

Texture* texture;
Buffer* buffer;

Uint32* pdata;
SDL_Surface* surface;
SDL_Surface* window;
#undef main
int main()
{
    srand(0);
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    {
        texture = ptTextureCreate(WIDTH, HEIGHT, 32 / 8, 0);
        buffer = ptBufferCreate(texture, WIDTH, HEIGHT, 32 / 8, 0);
        ptNoiseValue(buffer, 0, true, true);
        ptScale(buffer, 1024, 1024, PT_INTERP_LINEAR);
        ptBufferFinalizeRGBA32(buffer);

        Uint32 rmask, gmask, bmask, amask;

        #if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xFF000000;
            gmask = 0x00FF0000;
            bmask = 0x0000FF00;
            amask = 0x000000FF;
        #else
            rmask = 0x000000FF;
            gmask = 0x0000FF00;
            bmask = 0x00FF0000;
            amask = 0xFF000000;
        #endif

        pdata = malloc(buffer->width * buffer->height * buffer->bpp);
        memcpy(pdata, buffer->cdata, buffer->width * buffer->height * buffer->bpp);
        surface = SDL_CreateRGBSurfaceFrom(buffer->cdata, WIDTH, HEIGHT, 32, WIDTH * buffer->bpp, rmask, gmask, bmask, amask);
    }

    SDL_Event event;
    int running = 1;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }

        SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));

        SDL_BlitSurface(surface, NULL, window, NULL);

        SDL_Flip(window);
    }

    SDL_FreeSurface(surface);
    free(pdata);

    ptBufferDestroy(buffer);
    ptTextureDestroy(texture);

    SDL_Quit();

    return 0;
}
