#define SG_BUILD_LIBRARY
#include <siege/util/string.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

SGbool SG_EXPORT _sgStringInit(void)
{
    _sg_strBufLen = 0;
    _sg_strBuf = NULL;
    return SG_TRUE;
}
SGbool SG_EXPORT _sgStringDeinit(void)
{
    free(_sg_strBuf);
    return SG_TRUE;
}

char* SG_EXPORT sgPrintf(char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* str = sgPrintfv(format, args);
    va_end(args);
    return str;
}
char* SG_EXPORT sgPrintfv(char* format, va_list args)
{
    int ret = 0;
    _sg_strBufLen = 0;

    do
    {
        _sg_strBufLen += 256;
        _sg_strBuf = realloc(_sg_strBuf, _sg_strBufLen);
        ret = vsnprintf(_sg_strBuf, _sg_strBufLen, format, args);
    }
    while(ret >= _sg_strBufLen);

    if(ret < 0)
        return NULL;

    return _sg_strBuf;
}

char* SG_EXPORT sgLineEnd(char* text)
{
    if(text == NULL)
        return NULL;

    char* cr = strchr(text, '\r');
    char* lf = strchr(text, '\n');
    if(cr == NULL)
    {
        if(lf == NULL)
            return text + strlen(text);
        else
            return lf;
    }
    else if(lf == NULL) // cr != NULL
        return cr;
    else
        return (lf > cr) ? lf : cr;
}
SGuint SG_EXPORT sgLineLength(char* text)
{
    return sgLineEnd(text) - text;
}
char* SG_EXPORT sgNextLine(char* text)
{
    char* ptr = text;

    if(ptr != NULL)
    {
        char* crlf = strstr(ptr, "\r\n");
        char* cr = strchr(ptr, '\r');
        char* lf = strchr(ptr, '\n');
        if((crlf != NULL) && (crlf == cr) && (crlf == lf - 1)) // found a CRLF, and it was the first newline
            ptr = crlf + 2;
        else if((cr != NULL) && ((cr < lf) || (lf == NULL))) // found a CR, and it was the first newline
            ptr = cr + 1;
        else if(lf != NULL) // found a LF, and it was the first newline
            ptr = lf + 1;
        else // found nothing
            ptr = NULL;
        return ptr;
    }
    return NULL;
}
SGuint SG_EXPORT sgNumLines(char* text)
{
    SGuint numlines = 0;

    char* ptr = text;
    while(ptr != NULL)
    {
        ptr = sgNextLine(ptr);
        numlines++;
    }
    return numlines;
}
/// \todo TODO
void SG_EXPORT sgCharToUTF32(char* text, SGuint textlen, SGdchar* str)
{
    size_t i;
    for(i = 0; i < textlen; i++)
        str[i] = text[i];
}
