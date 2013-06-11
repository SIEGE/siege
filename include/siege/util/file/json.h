/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#if 0 /* Currently broken */

#ifndef __SIEGE_UTIL_FILE_JSON_H__
#define __SIEGE_UTIL_FILE_JSON_H__

#include "../../common.h"
#include "../list.h"
#include "../set.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_JSON_TYPE_NULL    0
#define SG_JSON_TYPE_BOOLEAN 1
#define SG_JSON_TYPE_NUMBER  2
#define SG_JSON_TYPE_STRING  3
#define SG_JSON_TYPE_COMMENT 4
#define SG_JSON_TYPE_ARRAY   5
#define SG_JSON_TYPE_OBJECT  6

#define SG_JSON_SYMBOL_SCHARS SG_ALPHA "_-."
#define SG_JSON_SYMBOL_MCHARS SG_JSON_SYMBOL_SCHARS SG_DECDIGITS

typedef struct SGJSONValue
{
    SGenum type;
    char* strbuf; // used for errors and stringification
    union
    {
        SGSet* object;
        SGList* array;
        char* string;
        double number;
        SGbool boolean;
        char* comment; // obviously an alias for string...
    } v;
} SGJSONValue;

typedef struct SGJSONSetItem
{
    char* key;
    SGJSONValue* val;
} SGJSONSetItem;

void SG_CALL _sgJSONFreeValue(SGJSONValue* value);
void SG_CALL _sgJSONDumpSetItem(SGSetNode* node, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent);
void SG_CALL _sgJSONDumpValue(SGJSONValue* value, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent);

char* SG_CALL _sgJSONSkipComments(char* input, char** error);
char* SG_CALL _sgJSONEscapeString(const char* input, char** str, size_t* len, size_t* mem);
SGbool SG_CALL _sgJSONGetSymbol(char** input);

char* SG_CALL _sgJSONParseNull(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseBoolean(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseNumber(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseString(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseSymbol(SGJSONValue* into, char* input, char** error); // extensions
char* SG_CALL _sgJSONParseComment(SGJSONValue* into, char* input, char** error); // extension
char* SG_CALL _sgJSONParseArray(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseObject(SGJSONValue* into, char* input, char** error);
char* SG_CALL _sgJSONParseValue(SGJSONValue* into, char* input, char** error);

SGJSONValue* SG_CALL sgJSONValueCreateString(const char* str);
SGJSONValue* SG_CALL sgJSONValueCreateFile(const char* fname);
void SG_CALL sgJSONValueDestroy(SGJSONValue* value);

char* SG_CALL sgJSONToString(SGJSONValue* value, SGbool pretty);
void SG_CALL sgJSONArrayRemoveValue(SGJSONValue* array, SGJSONValue* value);
void SG_CALL sgJSONObjectSetValue(SGJSONValue* object, const char* key, SGJSONValue* value);
void SG_CALL sgJSONObjectRemoveValue(SGJSONValue* object, const char* key);
SGJSONValue* SG_CALL sgJSONObjectGetValue(SGJSONValue* object, const char* key);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_FILE_JSON_H__

#endif
