#ifndef _GC_sprites_h
#define _GC_sprites_h

namespace GC
{
    class cSprite
    {
        public:
            // no p prefix here because this is also going to be used externally, in scripts
            SDL_Surface* surface;

            long id;
            int xorigin;
            int yorigin;
            int xalpha;
            int yalpha;
    } ;

    cSprite NULL_SPRITE;
    long gSpriteID = 0;
    cSprite gSpriteArray[255];

    long SpriteAdd(char* fname, int xorigin = 0, int yorigin = 0, int xalpha = 0, int yalpha = 0)
    {
        SDL_Surface* surface = SDL_LoadBMP(fname);
        cSprite sprite;

        sprite.id = gSpriteID;
        sprite.xorigin = xorigin;
        sprite.yorigin = yorigin;
        sprite.xalpha = xalpha;
        sprite.yalpha = yalpha;

        sprite.surface = surface;

        gSpriteArray[gSpriteID] = sprite;

        gSpriteID++;

        return gSpriteID-1;
    }

    long SpriteReplace(long sprite, char* fname, int xorigin = 0, int yorigin = 0, int xalpha = 0, int yalpha = 0)
    {
        //nothing just yet!
        return sprite;
    }

    long SpriteRemove(long sprite)
    {
        long id = gSpriteArray[sprite].id;
        gSpriteArray[sprite].id = -1;
        SDL_FreeSurface(gSpriteArray[sprite].surface);
        return id;
    }
}

#endif
