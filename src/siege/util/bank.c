/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/util/bank.h>

#include <stdlib.h>
#include <string.h>

static void expandCandidate(char* buf, const char* in, size_t inlen, const char* name)
{
    size_t namelen = strlen(name);

    size_t escs = 0;
    int esc = 0;
    size_t i;
    for(i = 0; i < inlen; i++)
    {
        if(esc)
        {
            if(in[i] == '%')
                *(buf++) = '%';
            else if(in[i] == 's')
            {
                memcpy(buf, name, namelen);
                buf += namelen;
            }
            else if(strchr(" \t\r\n\v", in[i]))
                esc = !esc; // this will make sure we keep esc after this step (we ignore spaces)
            else
            {
                memcpy(buf, &in[escs], i - escs);
                buf += i - escs;
            }
            esc = !esc;
        }
        else if(in[i] == '%')
        {
            escs = i;
            esc = 1;
        }
        else
            *(buf++) = in[i];
    }
    *buf = 0;
}
static void* loadItem(SGBank* bank, const char* name, void* data)
{
    const char* format = bank->format;

    size_t buflen = strlen(name) + strlen(format) + 1;
    char* buf = malloc(buflen);
    if(!buf)
        return NULL;

    void* item = NULL;

    size_t seglen;
    do
    {
        for(seglen = 0; format[seglen] && format[seglen] != '|'; seglen++)
        {}

        expandCandidate(buf, format, seglen, name);

        item = bank->cbLoad(buf, data);
        if(item)
            break;

        format = format + seglen;
        if(*format) // if we're at '|', jump over that
            format++;
    }
    while(*format);

    free(buf);
    return item;
}

SGBank* sgBankCreate(const char* format, SGBankLoad* cbLoad, SGBankUnload* cbUnload)
{
    SGBank* bank = malloc(sizeof(SGBank));
    if(!bank) return NULL;

    bank->smap = sgSMapCreate();
    if(!bank->smap)
    {
        free(bank);
        return NULL;
    }

    /* NULL format is equivalent to a no-op */
    if(!format) format = "%s";

    size_t len = strlen(format);
    bank->format = malloc(len + 1);
    if(!bank->format)
    {
        sgSMapDestroy(bank->smap);
        free(bank);
        return NULL;
    }
    memcpy(bank->format, format, len + 1);

    bank->cbLoad = cbLoad;
    bank->cbUnload = cbUnload;

    return bank;
}
void sgBankDestroy(SGBank* bank)
{
    if(!bank) return;

    sgSMapDestroy(bank->smap);
    free(bank->format);
    free(bank);
}

void* sgBankLoad(SGBank* bank, const char* name, void* data)
{
    void* item = sgSMapFind(bank->smap, name);
    if(item)
        return item;

    item = loadItem(bank, name, data);
    if(item)
        return item;

    return NULL;
}
void sgBankUnload(SGBank* bank, const char* name)
{
    if(!name) return;

    void* item = sgSMapFind(bank->smap, name);
    if(!item) return;

    if(bank->cbUnload)
        bank->cbUnload(item);
    sgSMapRemove(bank->smap, name);
}
