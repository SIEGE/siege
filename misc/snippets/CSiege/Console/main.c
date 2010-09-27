#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "console.h"

#define WIDTH 640
#define HEIGHT 480
#define CHEIGHT 12
SDL_Surface* window;
SDL_Surface* text;
SDL_Surface* consurf;
TTF_Font* mono;
CConsole* console;
int fontWidth(TTF_Font* font)
{
    SDL_Surface* surf = TTF_RenderText_Blended(font, "X", (SDL_Color) {255, 255, 255, 255});
    if(surf == NULL)
        return 0;
    int w = surf->w;
    SDL_FreeSurface(surf);
    return w;
}

void cbLine(CCharacter* string, Cuint length, Cuint line)
{
    char* cstr = conToCharn(string, length);
    SDL_Color color = {string->fgcolor.r, string->fgcolor.g, string->fgcolor.b, string->fgcolor.a};

    Cuint w = fontWidth(mono);

    Cuint i;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = line * CHEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    char buf[2];
    buf[1] = 0;
    for(i = 0; i < length; i++)
    {
        buf[0] = cstr[i];
        color = (SDL_Color){string[i].fgcolor.r, string[i].fgcolor.g, string[i].fgcolor.b, string[i].fgcolor.a};
        if(buf[0] == 3)
        {
            consurf = TTF_RenderText_Blended(mono, "C", color);
            SDL_BlitSurface(consurf, NULL, window, &rect);
            SDL_FreeSurface(consurf);
        }
        consurf = TTF_RenderText_Blended(mono, buf, color);

        SDL_BlitSurface(consurf, NULL, window, &rect);
        //rect.x += consurf->w;
        rect.x += w;
        SDL_FreeSurface(consurf);
    }

    /*consurf = TTF_RenderText_Blended(mono, cstr, color);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = line * 13;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    SDL_BlitSurface(consurf, NULL, window, &rect);
    SDL_FreeSurface(consurf);*/

    free(cstr);
}
#undef main
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    mono = TTF_OpenFont("Fonts/DejaVuLGCSansMono.ttf", CHEIGHT);

    window = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_EnableUNICODE(SDL_TRUE);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    text = TTF_RenderText_Blended(mono, "hello, world", (SDL_Color) {192, 192, 192, 255});

    console = conCreate(80, /*8*/40, /*HEIGHT / CHEIGHT - 1*/20, 2);
    conSetPrompt(console, "> ");
    conPrintT(console, "hello\nwor");
    conSetStyle(console, (CColor){255, 0, 0, 255}, (CColor){0, 0, 0, 255}, 0);
    int r = conPrintT(console, "ld\r");
    conPrintf(console, "%d\n", r);
    conSetStyle(console, (CColor){127, 127, 0, 255}, (CColor){0, 0, 0, 255}, 0);
    /*{
        char* map[256];
        memset(map, 0, 256 * sizeof(char*));
        map[  0] = "NUL"  ; map[  1] = "SOH"  ; map[  2] = "STX"  ; map[  3] = "ETX"  ; map[  4] = "EOT"  ; map[  5] = "ENQ"  ; map[  6] = "ACK"  ; map[  7] = "BEL";
        map[  8] = "BS"   ; map[  9] = "TAB"  ; map[ 10] = "LF"   ; map[ 11] = "VT"   ; map[ 12] = "FF"   ; map[ 13] = "CR"   ; map[ 14] = "SO"   ; map[ 15] = "SI";
        map[ 16] = "DLE"  ; map[ 17] = "DC1"  ; map[ 18] = "DC2"  ; map[ 19] = "DC3"  ; map[ 20] = "DC4"  ; map[ 21] = "NAK"  ; map[ 22] = "SYN"  ; map[ 23] = "ETB";
        map[ 24] = "CAN"  ; map[ 25] = "EM"   ; map[ 26] = "SUB"  ; map[ 27] = "ESC"  ; map[ 28] = "FS"   ; map[ 29] = "GS"   ; map[ 30] = "RS"   ; map[ 31] = "US";
        map[ 32] = "Space"; map[127] = "DEL"  ; map[155] = "CSI"  ;

        int cols = 4;

        int c;
        int x, y;
        for(y = 0; y < 256 / cols; y++)
        {
            for(x = 0; x < cols; x++)
            {
                c = x * 256 / cols + y;
                conSetStyle(console, (CColor){0, 127, 0, 255}, (CColor){0, 0, 0, 255}, 0);
                conPrintf(console, "  %3d", c);
                conSetStyle(console, (CColor){127, 127, 0, 255}, (CColor){0, 0, 0, 255}, 0);
                conPrintf(console, " %3X", c);
                conSetStyle(console, (CColor){0, 127, 127, 255}, (CColor){0, 0, 0, 255}, 0);
                conPrintf(console, " %3o", c);
                conSetStyle(console, (CColor){255, 0, 0, 255}, (CColor){0, 0, 0, 255}, 0);
                if(map[c] == 0)
                    conPrintf(console, " %c    ", c);
                else
                    conPrintf(console, " %-5s", map[c]);
                //conPrintf(console, "  %3d %.2X %c", c, c, (c >= 32) ? c : '?');

                conSetStyle(console, (CColor){(x == 1) ? 255 : 192, (x == 1) ? 255 : 192, (x == 1) ? 0 : 192, 255}, (CColor){0, 0, 0, 255}, 0);
                conPrintf(console, "%c", (x == 1) ? '|' : '|');
            }
            conPrintf(console, "\n");
        }
        conSetStyle(console, (CColor){255, 0, 0, 255}, (CColor){0, 0, 0, 255}, 0);
    }*/

    SDL_Event event;
    int done = 0;
    Cushort utf;
    char cutf[1];
    int cutflen;
    char buf[256];
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_PAGEUP)
                        conScroll(console, -1);
                    else if(event.key.keysym.sym == SDLK_PAGEDOWN)
                        conScroll(console, 1);
                    else if(event.key.keysym.sym == SDLK_LEFT)
                        conInputCursorMove(console, -1);
                    else if(event.key.keysym.sym == SDLK_RIGHT)
                        conInputCursorMove(console, 1);
                    else if(event.key.keysym.sym == SDLK_DELETE)
                        conInputTn(console, "\x7F", 1);
                    else if(event.key.keysym.sym == SDLK_INSERT)
                        conToggleInsert(console);
                    else
                    {
                        sprintf(buf, "%d", console->sheight);
                        SDL_FreeSurface(text);
                        text = TTF_RenderText_Blended(mono, buf, (SDL_Color) {192, 192, 192, 255});

                        utf = event.key.keysym.unicode;
                        cutf[0] = utf;
                        cutflen = 1;
                        //cutflen = wctomb(cutf, utf);
                        //cutf[1] = '0' + cutflen;
                        conInputTn(console, cutf, cutflen);
                    }
                    break;
                case SDL_KEYUP:
                    //conInputT();
                    //DisplayState(&event.key);
                    //DisplayModifiers(&event.key);
                    //DisplayKey(&event.key);
                    break;
                case SDL_QUIT:
                    done = 1;
                    break;
            }
        }

        SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));

        SDL_Rect rect;
        rect.x = WIDTH / 4;
        rect.y = HEIGHT / 4;
        rect.w = WIDTH / 2;
        rect.h = HEIGHT / 2;
        SDL_FillRect(window, &rect, SDL_MapRGB(window->format, 0, 128, 192));

        SDL_BlitSurface(text, NULL, window, &rect);
        conOutput(console, cbLine);
        //SDL_BlitSurface(console, NULL, window, NULL);

        if(!console->input.hide)
        {
            Cuint w = fontWidth(mono);
            consurf = TTF_RenderText_Blended(mono, console->input.insert ? "|" : "_", (SDL_Color){192, 192, 192, 255});
            rect.x = (conStrlen(console->input.prompt) + console->input.cursor) * w - (console->input.insert ? (w / 2) : 0);
            rect.y = console->dheight * 12;
            SDL_BlitSurface(consurf, NULL, window, &rect);
            SDL_FreeSurface(consurf);
        }

        SDL_Flip(window);
    }

    conDestroy(console);

    SDL_FreeSurface(text);
    //SDL_FreeSurface(consurf);
    SDL_Quit();

    return 0;
}
