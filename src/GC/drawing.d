/// if we decide to change our engine, this is the place where most of the changes are going to happen!

module GC.drawing;

//private import derelict.sdl.sdl;
private import GC.GC;

///#include <SDL/SDL_draw.h>

    // all this char crap might be changed to Uint8 someday...
    void DrawSprite(long sprite,int x=0,int y=0,short angle=0,char alpha=0xFF)
    {
        SDL_Rect rect;
        rect.x = x-gSpriteArray[sprite].xorigin;
        rect.w = gSpriteArray[sprite].surface.w;
        rect.y = y-gSpriteArray[sprite].yorigin;
        rect.h = gSpriteArray[sprite].surface.h;
        SDL_BlitSurface(gSpriteArray[sprite].surface, null, gpScreen, &rect);
    }

    void DrawPixel(SDL_Surface* surface,int x,int y,Uint32 pixel)
    {
        ///Draw_Pixel(gpScreen,x,y,SDL_MapRGBA(gpScreen.format, (color & 16711680)/65536 , (color & 65280)/256, color & 255,alpha & 0xFF));
        int bpp = surface.format.BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = cast(Uint8 *)surface.pixels + y * surface.pitch + x * bpp;

        switch(bpp)
        {
            case 1:
                *p = pixel;
            break;

            case 2:
                *cast(Uint16 *)p = pixel;
            break;

            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    p[0] = (pixel >> 16) & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = pixel & 0xff;
                }
                else
                {
                    p[0] = pixel & 0xff;
                    p[1] = (pixel >> 8) & 0xff;
                    p[2] = (pixel >> 16) & 0xff;
                }
            break;

            case 4:
                *cast(Uint32 *)p = pixel;;
            break;

            default:
            break; /* shouldn't happen, but avoids warnings */
        }
    }

    void DrawLine(int x1,int y1,int x2,int y2,int color[1],int alpha=0xFFFF)
    {
        ///Draw_Line(gpScreen,x1,y1,x2,y2,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
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
            ///Draw_Rect(gpScreen,a,b,c-a,d-b,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            ///Draw_FillRect(gpScreen,a,b,c-a,d-b,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
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
            ///Draw_Round(gpScreen,a,b,c-a,d-b,corner,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            ///Draw_FillRound(gpScreen,a,b,c-a,d-b,corner,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
    }

    void DrawEllipse(int x,int y,int xradius,int yradius,int color[1],int alpha=0xFFFF,bool fill=1)
    {
        if (fill == 0)
        {
            ///Draw_Ellipse(gpScreen,x,y,xradius,yradius,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
        else
        {
            ///Draw_FillEllipse(gpScreen,x,y,xradius,yradius,SDL_MapRGBA(gpScreen.format, (color[0] & 16711680)/65536 , (color[0] & 65280)/256, color[0] & 255,alpha & 0xFF));
        }
    }

    void DrawClear(int color,int alpha=0xFF)
    {
        SDL_FillRect(gpScreen, null, SDL_MapRGBA(gpScreen.format, (color & 16711680)/65536 , (color & 65280)/256, color & 255,alpha & 0xFF));
    }

    Uint32 GetPixel(SDL_Surface *surface, int x, int y)
    {
        int bpp = surface.format.BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = cast(Uint8 *)surface.pixels + y * surface.pitch + x * bpp;

        switch(bpp)
        {
            case 1:
                return *p;

            case 2:
                return *cast(Uint16 *)p;

            case 3:
                if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    return p[0] << 16 | p[1] << 8 | p[2];
                }
                else
                {
                    return p[0] | p[1] << 8 | p[2] << 16;
                }

            case 4:
                return *cast(Uint32 *)p;

            default:
                return 0;       /* shouldn't happen, but avoids warnings */
        }
    }
