#ifndef _GC_h
#define _GC_h

namespace GC
{
    // BASICS
    SDL_Surface* gpScreen;
}

// gui part
//#include "GUI/GUI.h"

// change to <> later - mabye
// core engine functions
#include "GC_constants.h"
#include "GC_sprites.h"
#include "GC_objects.h"
#include "GC_instances.h"
//#include "GC_textures.h"
#include "GC_drawing.h"
//#include "GC_levels.h"

// not-so-important functions
#include "GC_log.h"
//#include "GC_sockets.h"
//#include "GC_files.h"
//#include "GC_gui.h" //no, this isn't the GC's GUI... This is the GUI that users can add to their games or programs.

// misc... mabye we'll add this, mabye not. If we do, they'll probably be "optional modules" - think plugins.
//#include "GC_shaders.h"
//#include "GC_water.h"

namespace GC
{
    int GC_Init(int width,int height, int bpp, int flags)
    {
        LogOpen();
        LogWrite("Game started! Date/time: dd/mm/yyyy hh:mm");
        LogWrite("--------------------------------------------------");

        // initialize SDL video
        if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            printf( "Unable to init SDL: %s\n", SDL_GetError() );
            return 1;
        }

        // create a new window
        gpScreen = SDL_SetVideoMode(width, height, bpp,flags);
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
}

#endif
