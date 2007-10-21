module GC.GC;

public import derelict.sdl.sdl;

// gui part
//#include "GUI/GUI.h"

/// Core Engine Functions
public import GC.constants;
public import GC.sprites;
public import GC.objects;
public import GC.instances;
//public import GC.textures;
public import GC.drawing;
//public import GC.levels;

/// Not-so-important functions
public import GC.log;
//public import GC.network;
//public import GC.files;
//public import GC.physics;
/// No, this isn't the GC's GUI... This is the GUI that users can add to their games or programs.
//public import GC.gui;

/// Misc... Mabye we'll add this mabye not. If we do, they'll probably be "optinal modules" - think plugins.
//public import GC.shaders;
//public import GC.water;


    // BASICS
    SDL_Surface* gpScreen;

    int GC_Init(int width,int height, int bpp, int flags)
    {
        LogOpen();
        LogWrite("Game started! Date/time: dd/mm/yyyy hh:mm");
        LogWrite("--------------------------------------------------");

        NULL_SPRITE = new cSprite();
        NULL_OBJECT = new cObject();
        NULL_INSTANCE = new cInstance();

        NULL_SPRITE.id = -1;
        NULL_OBJECT.id = -1;
        NULL_INSTANCE.id = -1;

        DerelictSDL.load();
        // initialize SDL video
        if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            printf( "Unable to init SDL: %s\n", SDL_GetError() );
            return 1;
        }

        // create a new window
        gpScreen = SDL_SetVideoMode(width,height,bpp,flags);
        if ( !gpScreen )
        {
            printf("Unable to set 640x480 video: %s\n", SDL_GetError());
            return 2;
        }
        return 0;
    }
    void GC_Quit()
    {
        for(long i=0; i<gSpriteID; i++)
        {
            if(gSpriteArray[i].id >= 0)
            {
                SpriteRemove(i);
            }
        }
        SDL_Quit();
        LogWrite("--------------------------------------------------");
        LogWrite("Game quit! Running time: hh:mm, <ticks> ticks.");
        LogClose();
    }
