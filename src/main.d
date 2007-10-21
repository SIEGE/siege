//import derelict.sdl.sdl;
//import derelict.sdl.draw;
//import derelict.sdl.image;
import GC.GC;

int main ( char[][] args )
{
    /*int WIDTH = 640;
    int HEIGHT = 480;
    int BPP = 16;*/

    int _tmp = GC_Init(WIDTH,HEIGHT,BPP,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (_tmp > 0)
    {
        return _tmp;
    }

    // load the images
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
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                break;
            default:
                break;
            } // end switch
        } // end of message processing

        /// DRAWING STARTS HERE

        // clear screen
        DrawClear(cBlack);
        //DrawSprite(bmp,200,300);

        // draw bitmap
        for(long i=0; i<gInstanceID; i++)
        {
            if((gInstanceArray[i].id >= 0) && (gInstanceArray[i].alpha > 0))
            {
                DrawSprite(gInstanceArray[i].sprSprite.id,gInstanceArray[i].x,gInstanceArray[i].y);
            }
        //SDL_BlitSurface(bmp, 0, gpScreen, &dstrect);
        }

        /// DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(gpScreen);
    } // end main loop

    GC_Quit();
    return 0;
}
