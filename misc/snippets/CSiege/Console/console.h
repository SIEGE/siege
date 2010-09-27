#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>

#define TOUTF(x) (x)
#define FROMUTF(x) (x)
#define TABSIZE 4

typedef int8_t Cbool;

typedef char Cchar;
typedef uint16_t Cwchar;
typedef uint32_t Cdchar;

typedef int8_t Cbyte;
typedef uint8_t Cubyte;
typedef int16_t Cshort;
typedef uint16_t Cushort;
typedef int32_t Cint;
typedef uint32_t Cuint;
typedef int64_t Clong;
typedef uint64_t Culong;

typedef struct CColor
{
    Cubyte r;
    Cubyte g;
    Cubyte b;
    Cubyte a;
} CColor;

typedef struct CCharacter
{
    Cchar value;
    CColor fgcolor;
    CColor bgcolor;
    Cuint flags;
} CCharacter;

typedef struct CInput
{
    Cbool hide;
    Cbool insert;
    Cuint cursor;
    CCharacter style;
    CCharacter* prompt;
    CCharacter* text;
} CInput;

typedef struct CConsole
{
    CCharacter style;
    CInput input;

    Cuint xcursor;

    Cuint width;
    Cuint height;
    Cuint sheight;
    Cuint dheight;
    Cuint iheight;

    CCharacter** field;

    void (*cbLine)(struct CConsole* console, CCharacter* line, Cuint length);
} CConsole;

char** splitlinesn(char* input, Cuint* numlines);
char** splitlines(char* input);
void freelines(char** lines);

Cuint conStrlen(CCharacter* chars);

char* conPruneDeleten(char* string, Cuint* length, Cint* corr);
char* conPruneBackspacen(char* string, Cuint* length, Cint* corr);
char* conExpandTabsn(char* string, Cuint* length, Cuint tabsize);

char* conToCharn(CCharacter* string, Cuint length);
char* conToChar(CCharacter* string);
CCharacter* conFromCharsn(CCharacter style, char* string, Cuint length);
CCharacter* conFromChars(CCharacter style, char* string);

CConsole* conCreate(Cuint width, Cuint height, Cuint dheight, Cuint iheight);
void conDestroy(CConsole* c);
void conOutput(CConsole* c, void (*cbLine)(CCharacter* string, Cuint length, Cuint line));
Cuint conPrintT(CConsole* c, char* text);
Cuint conPrintf(CConsole* c, char* format, ...);
void conInputTn(CConsole* c, char* text, Cuint length);
void conInputT(CConsole* c, char* text);
Cuint conInputf(CConsole* c, char* format, ...);
void conInputCursorSet(CConsole* c, Cuint set);
void conInputCursorMove(CConsole* c, Cint move);
void conScroll(CConsole* c, Cint scroll);
void conToggleInsert(CConsole* c);
void conSetInsert(CConsole* c, Cbool insert);
void conGetInsert(CConsole* c, Cbool* insert);
void conSetStyle(CConsole* c, CColor fgcolor, CColor bgcolor, Cuint flags);
void conGetStyle(CConsole* c, CColor* fgcolor, CColor* bgcolor, Cuint* flags);
void conSetPrompt(CConsole* c, char* string);
void conGetPrompt(CConsole* c, char** string);

#endif // __CONSOLE_H__
