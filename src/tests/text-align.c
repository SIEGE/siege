#include <siege/siege.h>

static const char* Text[] = { "XYZxyz", "XYZxyz\nABCabc" };

static const SGenum AlignW[] = { SG_ALIGN_LEFT, SG_ALIGN_CENTER, SG_ALIGN_RIGHT };
static const SGenum AlignH[] = { SG_ALIGN_TOP, SG_ALIGN_CENTER, SG_ALIGN_BASELINE, SG_ALIGN_BOTTOM };

static const char* NamesW[] = { "LEFT", "CENTER", "RIGHT" };
static const char* NamesH[] = { "TOP", "CENTER", "BASELINE", "BOTTOM" };

#define ARRSIZE(x) (sizeof(x) / sizeof(*x))

#define WPART 160
#define HPART 160

#define WIDTH (WPART*ARRSIZE(Text)*ARRSIZE(AlignW))
#define HEIGHT (HPART*ARRSIZE(AlignH))

int main(void)
{
    sgInit(0);
    sgWindowOpen(WIDTH, HEIGHT, 32, 0);

    SGFont* font = sgFontCreate("data/fonts/DejaVuSans.ttf", 12.0, 0, 0);

    size_t i, j, k;

    SGint ret;
    for(;;)
    {
        sgDrawClear();
        if(!sgLoop(&ret))
            break;

        sgDrawColor3f(0.25, 0.0, 0.0);
        for(i = WPART / 2; i < WIDTH; i += WPART)
            sgDrawLine(i, 0, i, HEIGHT);
        for(j = HPART / 2; j < HEIGHT; j += HPART)
            sgDrawLine(0, j, WIDTH, j);
        sgDrawColor3f(0.5, 0.5, 0.0);
        for(k = 0; k < ARRSIZE(Text); k++)
            for(i = 0; i < ARRSIZE(AlignW); i++)
                sgFontPrintAligned(font, WPART / 2 + (k * ARRSIZE(AlignW) + i) * WPART, 0, SG_ALIGN_TOP, NamesW[i]);
        for(j = 0; j < ARRSIZE(AlignH); j++)
            sgFontPrintAligned(font, 0, HPART / 2 + j * HPART, SG_ALIGN_LEFT, NamesH[j]);
        sgDrawColor1f(1.0);

        for(k = 0; k < ARRSIZE(Text); k++)
        {
            for(i = 0; i < ARRSIZE(AlignW); i++)
            {
                for(j = 0; j < ARRSIZE(AlignH); j++)
                {
                    sgFontPrintAligned(font, WPART / 2 + (k * ARRSIZE(AlignW) + i) * WPART, HPART / 2 + j * HPART, AlignW[i] | AlignH[j], Text[k]);
                }
            }
        }

        sgWindowSwapBuffers();
    }

    sgFontDestroy(font);
    sgDeinit();
    return ret;
}
