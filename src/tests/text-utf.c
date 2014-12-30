// REQUIREMENTS:
// - A UTF-8-capable compiler
// - A UTF-8-capable editor (for this file)
// - An Unicode-capable font

#include <siege/siege.h>

static const char* Text[] = {
    "čšž",
    "Под южно дърво, цъфтящо в синьо, бягаше малко пухкаво зайче",  // Bulgarian
    "Příliš žluťoučký kůň úpěl ďábelské ódy",                       // Czech
    "Съешь ещё этих мягких французских булок да выпей же чаю",
    "Τάχιστη αλώπηξ βαφής ψημένη γη, δρασκελίζει υπέρ νωθρού κυνός",
};
static const wchar_t* TextW[] = {
    L"čšž",
    L"Под южно дърво, цъфтящо в синьо, бягаше малко пухкаво зайче",  // Bulgarian
    L"Příliš žluťoučký kůň úpěl ďábelské ódy",                       // Czech
    L"Съешь ещё этих мягких французских булок да выпей же чаю",
    L"Τάχιστη αλώπηξ βαφής ψημένη γη, δρασκελίζει υπέρ νωθρού κυνός",
};

#define ARRSIZE(x) (sizeof(x) / sizeof(*x))

#define WIDTH 640
#define HEIGHT 480

int main(void)
{
    sgInit(0);
    sgWindowOpen(WIDTH, HEIGHT, 32, 0);

    SGFont* font = sgFontCreate("data/fonts/DejaVuSans.ttf", 10.0, 0, 0);

    size_t i;

    SGint ret;
    for(;;)
    {
        sgDrawClear();
        if(!sgLoop(&ret))
            break;

        for(i = 0; i < ARRSIZE(Text); i++)
            sgFontPrintAlignedU8(font, WIDTH * 5 / 12, (i + 1) * 32 - 16, SG_ALIGN_BASELINE, Text[i]);
        for(i = 0; i < ARRSIZE(TextW); i++)
            sgFontPrintAlignedW(font, WIDTH * 7 / 12, (i + 1) * 32, SG_ALIGN_BASELINE, TextW[i]);

        sgWindowSwapBuffers();
    }

    sgFontRelease(font);
    sgDeinit();
    return ret;
}
