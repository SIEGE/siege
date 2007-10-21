module GC.sprites;

private import derelict.sdl.sdl;
private import GC.GC;

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

    long SpriteAdd(char[] fname, int xorigin = 0, int yorigin = 0, int xalpha = -1, int yalpha = -1)
    {
        SDL_Surface* surface = SDL_LoadBMP(cast(char*) fname);
        cSprite sprite = new cSprite;

        sprite.id = gSpriteID;
        sprite.xorigin = xorigin;
        sprite.yorigin = yorigin;
        sprite.xalpha = xalpha;
        sprite.yalpha = yalpha;

        if((xalpha != -1) && (yalpha != -1))
        {
            Uint32 pixel = GetPixel(surface,xalpha,yalpha);
            ubyte r;
            ubyte g;
            ubyte b;
            SDL_GetRGB(pixel,surface.format,&r,&g,&b);
            SDL_SetColorKey(surface,SDL_SRCCOLORKEY,SDL_MapRGB(gpScreen.format,r,g,b));
        }

        sprite.surface = surface;

        gSpriteArray[gSpriteID] = sprite;

        gSpriteID++;

        return gSpriteID-1;
    }

    long SpriteReplace(long sprite, char[] fname, int xorigin = 0, int yorigin = 0, int xalpha = 0, int yalpha = 0)
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
