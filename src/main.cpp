/*
Copyright (c) 2007, Tim Chas

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of the GameCraft Team nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_image.h>

// to be changed to <> later - mabye
#include "GC/GC.h"

/*
    Dependencies:
    LibSDL
    SDL_image.h
    SDL_draw.h
*/

using namespace GC;

int main ( int argc, char** argv )
{
    // make sure SDL cleans up before exit
    atexit(GC_Quit);

    /*int WIDTH = 640;
    int HEIGHT = 480;
    int BPP = 16;*/

    int _tmp = GC_Init(WIDTH,HEIGHT,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (_tmp > 0)
    {
        return _tmp;
    }

    // load an image
    long bmp = SpriteAdd("cb.bmp",75,60);
    long obj = ObjectAdd(bmp);
    InstanceAdd(obj,128,128);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        DrawClear(cBlack);
        //DrawSprite(bmp,200,300);

        // draw bitmap
        for(long i=0; i<gInstanceID; i++)
        {
            if(gInstanceArray[i].instID >= 0)
            {
                DrawSprite(gInstanceArray[i].sprSprite->id,gInstanceArray[i].x,gInstanceArray[i].y);
            }
        //SDL_BlitSurface(bmp, 0, gpScreen, &dstrect);
        }
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(gpScreen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
