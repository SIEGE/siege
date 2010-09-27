#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define CLAMP(a, x, y) (MIN(MAX((x), (a)), (y)))
char** splitlinesn(char* input, Cuint* numlines)
{
    if(numlines != NULL)
        *numlines = 0;
    if(input == NULL)
        return NULL;

    char** lines = NULL;

    Cuint line = 0;
    char* newline = NULL;
    char* crlf;
    char* cr;
    char* lf;

    do
    {
        lines = realloc(lines, ++line * sizeof(char*));
        lines[line - 1] = NULL;

        crlf = strstr(input, "\r\n");
        cr = strchr(input, '\r');
        lf = strchr(input, '\n');
        newline = crlf;
        if((cr != NULL && cr < newline) || newline == NULL)
            newline = cr;
        if((lf != NULL && lf < newline) || newline == NULL)
            newline = lf;

        if(newline != NULL)
        {
            lines[line - 1] = malloc((newline - input + 1) * sizeof(char));
            lines[line - 1] = strncpy(lines[line - 1], input, newline - input);
            lines[line - 1][newline - input] = 0;
            input = (char*)(newline == crlf) ? (newline + 2) : (newline + 1);
        }
        //else
        //    break;

    }
    while(newline != NULL);

    lines = realloc(lines, (line + 1) * sizeof(char*));
    lines[line - 1] = malloc((strlen(input) + 1) * sizeof(char));
    lines[line - 1] = strcpy(lines[line - 1], input);
    lines[line - 1][strlen(input)] = 0;
    lines[line] = NULL;
    if(numlines != NULL)
        *numlines = line;

    return lines;
}
char** splitlines(char* input)
{
    return splitlinesn(input, NULL);
}
void freelines(char** lines)
{
    if(lines == NULL)
        return;

    Cuint i;
    for(i = 0; lines[i] != NULL; i++)
        free(lines[i]);
    free(lines);
}

Cuint conStrlen(CCharacter* chars)
{
    if(chars == NULL)
        return 0;

    Cuint length;
    for(length = 0; chars[length].value != 0; length++)
    {
    }
    return length;
}

char* conPruneDeleten(char* string, Cuint* length, Cint* corr)
{
    Cuint len = *length;
    char* del = string;
    do
    {
        del = memchr(del, 127, (string + len - del) * sizeof(char));
        if(del != NULL)
        {
            memmove(del, (del != string + len - 1) ? (del + 2) : (del + 1), string + len - del);

            *length -= (del != string + len - 1) ? 2 : 1;

            if(corr != NULL)
                (*corr)++;
            del++;
        }
        //else
        //    break;
    }
    while(del != NULL);

    return realloc(string, (*length + 1) * sizeof(char));
    return string;
}
char* conPruneBackspacen(char* string, Cuint* length, Cint* corr)
{
    Cuint len = *length;
    char* bspace = string;
    do
    {
        bspace = memchr(bspace, '\b', (string + len - bspace) * sizeof(char));
        if(bspace != NULL)
        {
            /*bspace = bspace - (size_t)string;
            string = realloc(string, (*length + bspacesize) * sizeof(char));
            bspace = bspace + (size_t)string;*/

            memmove((bspace != string) ? (bspace - 1) : bspace, bspace + 1, string + len - bspace);

            *length -= (bspace != string) ? 2 : 1;

            /*if(corr != NULL)
                *corr += (bspace != string) ? 2 : 1;*/
            bspace++;
        }
        //else
        //    break;
    }
    while(bspace != NULL);

    return realloc(string, (*length + 1) * sizeof(char));
    //return string;
}
char* conExpandTabsn(char* string, Cuint* length, Cuint tabsize)
{
    char* tab = string;
    do
    {
        tab = memchr(tab, '\t', (string + *length - tab) * sizeof(char));
        if(tab != NULL)
        {
            tab = tab - (size_t)string;
            string = realloc(string, (*length + tabsize) * sizeof(char));
            tab = tab + (size_t)string;

            memmove(tab, tab + tabsize - 1, (string + *length - tab));
            Cuint i;
            for(i = 0; i < tabsize; i++)
                tab[i] = ' ';
            tab = tab + tabsize;
            *length += tabsize - 1;
        }
        //else
        //    reak;
    }
    while(tab != NULL);

    return string;
}

char* conToCharn(CCharacter* string, Cuint length)
{
    if(string == NULL)
        return NULL;

    char* cstring = malloc((length + 1) * sizeof(char));

    Cuint i;
    for(i = 0; (i < length) && (string[i].value != 0); i++)
        cstring[i] = FROMUTF(string[i].value);
    cstring[i] = 0;

    return cstring;
}
char* conToChar(CCharacter* string)
{
    return conToCharn(string, conStrlen(string));
}

CCharacter* conFromCharsn(CCharacter style, char* string, Cuint length)
{
    CCharacter* cstring = malloc((length + 1) * sizeof(CCharacter));

    Cuint i;
    for(i = 0; (i < length) && (string[i] != 0); i++)
    {
        memcpy(&cstring[i], &style, sizeof(CCharacter));
        cstring[i].value = TOUTF(string[i]);
    }
    cstring[i].value = 0;

    return cstring;
}
CCharacter* conFromChars(CCharacter style, char* string)
{
    return conFromCharsn(style, string, strlen(string));
}

CConsole* conCreate(Cuint width, Cuint height, Cuint dheight, Cuint iheight)
{
    CConsole* c = malloc(sizeof(CConsole));

    c->style.value = ' ';
    c->style.fgcolor = (CColor){0xC0, 0xC0, 0xC0, 0xFF};
    c->style.bgcolor = (CColor){0x00, 0x00, 0x00, 0xFF};
    c->style.flags = 0;

    c->xcursor = 0;

    c->width = width;
    c->height = height;
    c->sheight = height - 1;
    c->dheight = dheight;
    c->iheight = iheight;

    c->cbLine = NULL;

    c->input.hide = 0;
    c->input.insert = 1;
    c->input.cursor = 0;
    memcpy(&c->input.style, &c->style, sizeof(CCharacter));
    c->input.text = NULL;
    //c->input.prompt = NULL;
    //conSetPrompt(c, ">");
    c->input.prompt = malloc(2 * sizeof(CCharacter));
    memcpy(&c->input.prompt[0], &c->style, sizeof(CCharacter));
    memcpy(&c->input.prompt[1], &c->style, sizeof(CCharacter));
    c->input.prompt[0].value = '>';
    c->input.prompt[1].value = 0;

    c->field = malloc(height * sizeof(CCharacter*));
    Cuint i;
    for(i = 0; i < height; i++)
    {
        c->field[i] = malloc(sizeof(CCharacter));
        memcpy(c->field[i], &c->style, sizeof(CCharacter));
        c->field[i]->value = 0;
    }

    return c;
}

void conDestroy(CConsole* c)
{
    if(c == NULL)
        return;

    free(c->input.prompt);
    if(c->field != NULL)
    {
        Cuint i;
        for(i = 0; i < c->height; i++)
            free(c->field[i]);
        free(c->field);
    }

    free(c);
}

void conOutput(CConsole* c, void (*cbLine)(CCharacter* string, Cuint length, Cuint line))
{
    Cint left = MIN(c->height - c->sheight, c->dheight);
    Cuint i;
    Cuint length;
    CCharacter* string;
    Cuint mod;

    if(!c->input.hide)
    {
        Cuint plen = conStrlen(c->input.prompt);
        Cuint tlen = conStrlen(c->input.text);
        CCharacter* ccat = malloc((plen + tlen + 1) * sizeof(CCharacter));
        memcpy(ccat, c->input.prompt, plen * sizeof(CCharacter));
        memcpy(ccat + plen, c->input.text, tlen * sizeof(CCharacter));
        ccat[plen + tlen].value = 0;

        length = plen + tlen;
        /*Cuint ileft = c->iheight;
        while(length > c->width)
        {
            mod = length % c->width;
            length -= mod;
            cbLine(ccat + length, mod, c->dheight + ileft - 1);

            if(--ileft <= 0)
                return;
        }*/
        cbLine(ccat, length, c->dheight);

        //cbLine(ccat, plen + tlen, c->dheight);
        free(ccat);
    }

    for(i = c->height - 1; left > 0; i--)
    {
        string = c->field[i];
        length = conStrlen(c->field[i]);

        while(length > c->width)
        {
            mod = length % c->width;
            length -= mod;
            cbLine(string + length, mod, left - 1);

            if(--left <= 0)
                return;
        }
        // for the remaining part
        cbLine(string, length, left - 1);
        if(--left <= 0)
            return;
    }
}

Cuint conPrintT(CConsole* c, char* text)
{
    Cuint nlines;
    char** lines = splitlinesn(text, &nlines);
    Cuint i, j;
    Cuint lwidth;
    Cuint printed = 0;

    for(i = 0; i < nlines; i++)
    {
        lwidth = strlen(lines[i]);

        //free(c->field[0]);
        //c->field = memmove(c->field, c->field + 1, (c->height - 1) * sizeof(CCharacter*));
        c->field[c->height - 1] = /*m*/realloc(c->field[c->height - 1], (c->xcursor + lwidth + 1) * sizeof(CCharacter));
        for(j = c->xcursor; j < c->xcursor + lwidth; j++)
        {
            memcpy(&c->field[c->height - 1][j], &c->style, sizeof(CCharacter));
            c->field[c->height - 1][j].value = TOUTF(lines[i][j - c->xcursor]);
        }
        c->field[c->height - 1][j].value = 0;
        c->xcursor += lwidth;
        if(i != nlines - 1)
        {
            free(c->field[0]);
            c->field = memmove(c->field, c->field + 1, (c->height - 1) * sizeof(CCharacter*));
            c->field[c->height - 1] = NULL;
            c->xcursor = 0;

            conScroll(c, -1);
            printed++;
        }

        printed += lwidth;
    }

    freelines(lines);

    return printed;
}

Cuint conPrintf(CConsole* c, char* format, ...)
{
    va_list args;
    va_start(args, format);

    int size = 256;
    char* buffer = malloc(size);
    int num;
    while(1)
    {
        num = vsnprintf(buffer, size, format, args);
        if(num > -1 && num < size)
            break;
        else
        {
            if(num > -1)
                size = num + 1;
            else
                size *= 2;
            buffer = realloc(buffer, size);
        }
    }

    va_end(args);

    return conPrintT(c, buffer);
}
// TODO: return input len
void conInputTn(CConsole* c, char* ntext, Cuint length)
{
    if(c->input.hide)
        return;
    if(length == 1 && *ntext == 27) // do nothing with the escape char
        return;

    char* text = malloc((length + 1) * sizeof(char));
    strncpy(text, ntext, length);
    text[length] = 0;

    Cuint nlines;
    char** lines = splitlinesn(text, &nlines);
    Cuint i;

    char* line;
    Cuint llen;
    //CCharacter* catline = NULL;
    //CCharacter* cline = NULL;
    Cuint clen;
    char* cinp;
    Cuint nlen;
    char* ninp;
    Cuint plen;
    Cint corr = 0;

    for(i = 0; i < nlines; i++)
    {
        clen = c->input.cursor; //conStrlen(c->input.text);
        nlen = conStrlen(c->input.text + c->input.cursor);
        cinp = conToCharn(c->input.text, clen + nlen);
        ninp = cinp + c->input.cursor;//conToCharn(c->input.text + clen, nlen);
        line = lines[i];
        llen = strlen(line);

        if(c->input.insert)
        {
            length = clen + llen + nlen;
            line = malloc((length + 1) * sizeof(char));
            memcpy(line, cinp, clen * sizeof(char));                 // before input
            memcpy(line + clen, lines[i], llen * sizeof(char));      // at input
            memcpy(line + clen + llen, ninp, (nlen) * sizeof(char)); // after input
            line[length] = 0;
        }
        else
        {
            Cuint n;
            char* from;
            char* to;
            int shift = 0;

            length = clen + MAX(llen, nlen);
            line = malloc((length + 1) * sizeof(char));
            memcpy(line, cinp, clen * sizeof(char));                 // before input

            from = lines[i];
            to = line + clen;
            for(n = clen; n < clen + llen; n++)
            {

                if(*from == '\b') // backspace
                {
                    //from++; // jump over
                    if(n != 0)
                    {
                        to--; // go to prev char
                        shift--;
                    }
                    //shift--;
                }
                else if(*from == 127) // delete
                {
                    //from++; // jump over
                    if(n != length - 1)
                    {
                        from++; // jump over the next char
                        shift--;
                    }
                    //shift--;
                }
                else
                {
                    *to = *from;
                    corr++;
                }
                if(*from == 0) // end
                    break;

                from++;
                to++;
            }
            length = clen + MAX(llen, nlen);

            if(nlen != 0)
                memcpy(line + clen + llen + shift, ninp + 1/* - shift*/, (nlen + 1/* + shift*/) * sizeof(char)); // after input
            line[length] = 0;
        }

        line = conPruneDeleten(line, &length, &corr);
        line = conPruneBackspacen(line, &length, &corr);
        line = conExpandTabsn(line, &length, TABSIZE);

        if(i != nlines - 1)
        {
            plen = conStrlen(c->field[c->height - 1]);
            {
                Cuint pr_len = conStrlen(c->input.prompt);

                char* buf = malloc((pr_len + 1) * sizeof(char));
                memset(buf, '_', pr_len * sizeof(char));
                buf[pr_len] = 0;
                conPrintT(c, buf); // todo: conPrintTc
                free(buf);
                memcpy(c->field[c->height - 1], c->input.prompt, (pr_len + 1) * sizeof(CCharacter));
            }
            //conPrintT(c, ">>> ");
            conPrintT(c, line); // todo: conPrintTc
            conPrintT(c, "\n"); // todo: conPrintTc
            if(c->cbLine != NULL)
                c->cbLine(c, c->field[c->height - 1] + plen, length);
            free(c->input.text);
            c->input.text = 0;
            //c->input.text = realloc(c->input.text, 0);

            conInputCursorSet(c, 0);
        }
        else
        {
            free(c->input.text);
            c->input.text = conFromCharsn(c->input.style, line, length);
            conInputCursorMove(c, length - (clen + nlen) + corr);
        }

        free(cinp);
        free(line);
    }

    freelines(lines);
}
void conInputT(CConsole* c, char* text)
{
    conInputTn(c, text, strlen(text));
}
Cuint conInputf(CConsole* c, char* format, ...)
{
    va_list args;
    va_start(args, format);

    int size = 256;
    char* buffer = malloc(size);
    int num;
    while(1)
    {
        num = vsnprintf(buffer, size, format, args);
        if(num > -1 && num < size)
            break;
        else
        {
            if(num > -1)
                size = num + 1;
            else
                size *= 2;
            buffer = realloc(buffer, size);
        }
    }

    va_end(args);

    /*return */conInputTn(c, buffer, num);
    return num;
}
void conInputCursorSet(CConsole* c, Cuint set)
{
    c->input.cursor = CLAMP(set, 0, conStrlen(c->input.text));
}
void conInputCursorMove(CConsole* c, Cint move)
{
    c->input.cursor = CLAMP((Cint)c->input.cursor + move, 0, conStrlen(c->input.text));
}

void conScroll(CConsole* c, Cint scroll)
{
    c->sheight = CLAMP((Cint)c->sheight + scroll, 0, c->height);
}

void conToggleInsert(CConsole* c)
{
    c->input.insert = !c->input.insert;
}
void conSetInsert(CConsole* c, Cbool insert)
{
    c->input.insert = insert;
}
void conGetInsert(CConsole* c, Cbool* insert)
{
    *insert = c->input.insert;
}

void conSetStyle(CConsole* c, CColor fgcolor, CColor bgcolor, Cuint flags)
{
    if(c == NULL)
        return;

    c->style.fgcolor = fgcolor;
    c->style.bgcolor = bgcolor;
    c->style.flags = flags;
}
void conGetStyle(CConsole* c, CColor* fgcolor, CColor* bgcolor, Cuint* flags)
{
    if(c == NULL)
        return;

    *fgcolor = c->style.fgcolor;
    *bgcolor = c->style.bgcolor;
    *flags = c->style.flags;
}

void conSetPrompt(CConsole* c, char* string)
{
    //Cuint len = strlen(string);

    free(c->input.prompt);
    c->input.prompt = conFromChars(c->input.style, string);
    /*c->input.prompt = malloc((len + 1) * sizeof(CCharacter));
    Cuint i;
    for(i = 0; i < len; i++)
    {
        memcpy(&c->input.prompt[i], &c->style, sizeof(CCharacter));
        c->input.prompt[i].value = TOUTF(string[i]);
    }*/
}
void conGetPrompt(CConsole* c, char** string)
{
    *string = conToChar(c->input.prompt);
}
