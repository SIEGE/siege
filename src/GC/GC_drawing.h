// if we decide to change our engine, this is the place where most of the changes are going to happen!

#ifndef _GC_drawing_h
#define _GC_drawing_h

#include <SDL/SDL_draw.h>

namespace GC
{
    // all this char crap might be changed to Uint8 someday...
    void DrawSprite(long sprite,int x=0,int y=0,short angle=0,char alpha=0xFF)
    {
        SDL_Rect rect;
        rect.x = x-gSpriteArray[sprite].xorigin;
        rect.w = gSpriteArray[sprite].surface->w;
        rect.y = y-gSpriteArray[sprite].yorigin;
        rect.h = gSpriteArray[sprite].surface->h;
        SDL_BlitSurface(gSpriteArray[sprite].surface, 0, gpScreen, &rect);
    }

    void DrawPixel(int x,int y,int color,int alpha=0xFF)
    {
        Draw_Pixel(gpScreen,x,y,SDL_MapRGBA(gpScreen->format, (color & 16711680)/65536 , (color & 65280)/256, color & 255,alpha & 0xFF));
    }

    void DrawLine(int x1,int y1,int x2,int y2,int color[1],int alpha=0xFFFF)
    {
        Draw_Line(gpScreen,x1,y1,x2,y2,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
    }

    void DrawTriangle(int x1,int y1,int x2,int y2,int x3,int y3,int color[2],int alpha=0xFFFFFF,bool fill=1)
    {
        // draw a triangle...
    }

    void DrawRectangle(int x1,int y1,int x2,int y2,int color[3],int alpha=0xFFFFFFFF,bool fill=1)
    {
        int a = (x1<x2) ? x1:x2;
        int b = (y1<y2) ? y1:y2;
        int c = (x2<x1) ? x1:x2;
        int d = (y2<y1) ? y1:y2;

        if (fill == 0)
        {
            Draw_Rect(gpScreen,a,b,c-a,d-b,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            Draw_FillRect(gpScreen,a,b,c-a,d-b,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
    }
    void DrawRectangleRounded(int x1,int y1,int x2,int y2,int corner,int color[3],int alpha=0xFFFFFFFF,bool fill=1)
    {
        int a = (x1<x2) ? x1:x2;
        int b = (y1<y2) ? y1:y2;
        int c = (x2<x1) ? x1:x2;
        int d = (y2<y1) ? y1:y2;

        if (fill == 0)
        {
            Draw_Round(gpScreen,a,b,c-a,d-b,corner,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            Draw_FillRound(gpScreen,a,b,c-a,d-b,corner,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
    }

    void DrawEllipse(int x,int y,int xradius,int yradius,int color[1],int alpha=0xFFFF,bool fill=1)
    {
        if (fill == 0)
        {
            Draw_Ellipse(gpScreen,x,y,xradius,yradius,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            Draw_FillEllipse(gpScreen,x,y,xradius,yradius,SDL_MapRGBA(gpScreen->format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
    }

    void DrawClear(int color,int alpha=0xFF)
    {
        SDL_FillRect(gpScreen, 0, SDL_MapRGBA(gpScreen->format, (color & 16711680)/65536 , (color & 65280)/256, color & 255,alpha & 0xFF));
    }
}

#endif
