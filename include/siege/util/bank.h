/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_BANK_H__
#define __SIEGE_UTIL_BANK_H__

#include "../common.h"
#include "smap.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef void* SGBankLoad(const char* name, void* data);
typedef void  SGBankUnload(void* ptr);

/*
 * SIEGE resource bank.
 *
 * It tries to find the item specified as "name" (in GetItem) in the
 * tree; if it is not found, it calls cbLoad and returns the result.
 */
typedef struct SGBank
{
    SGSMap* smap;
    char* format;
    SGBankLoad* cbLoad;
    SGBankUnload* cbUnload;
} SGBank;

/**
 * Format:
 *  %s => name
 *  %% => single '%'
 *  | => separator (tried in sequence until bank->load() returns non-NULL)
 */
SGBank* sgBankCreate(const char* format, SGBankLoad* cbLoad, SGBankUnload* cbUnload);
void sgBankDestroy(SGBank* bank);

void* sgBankLoad(SGBank* bank, const char* name, void* data);
void sgBankUnload(SGBank* bank, const char* name);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_BANK_H__
