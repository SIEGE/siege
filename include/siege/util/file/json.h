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

#ifndef __SIEGE_UTIL_FILE_JSON_H__
#define __SIEGE_UTIL_FILE_JSON_H__

#include "../../common.h"
#include "../list.h"
#include "../tree.h"

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
        SGTree* object;
        SGList* array;
        char* string;
        double number;
        SGbool boolean;
        char* comment; // obviously an alias for string...
    } v;
} SGJSONValue;

typedef struct SGJSONTreeItem
{
    char* key;
    SGJSONValue* val;
} SGJSONTreeItem;

SGint SG_EXPORT _sgJSONTreeCmp(const void* a, const void* b);
void SG_EXPORT _sgJSONFreeValue(SGJSONValue* value);
void SG_EXPORT _sgJSONDumpTreeItem(SGTreeNode* node, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent);
void SG_EXPORT _sgJSONDumpValue(SGJSONValue* value, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent);

char* SG_EXPORT _sgJSONSkipComments(char* input, char** error);
char* SG_EXPORT _sgJSONEscapeString(const char* input, char** str, size_t* len, size_t* mem);
SGbool SG_EXPORT _sgJSONGetSymbol(char** input);

char* SG_EXPORT _sgJSONParseNull(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseBoolean(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseNumber(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseString(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseSymbol(SGJSONValue* into, char* input, char** error); // extensions
char* SG_EXPORT _sgJSONParseComment(SGJSONValue* into, char* input, char** error); // extension
char* SG_EXPORT _sgJSONParseArray(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseObject(SGJSONValue* into, char* input, char** error);
char* SG_EXPORT _sgJSONParseValue(SGJSONValue* into, char* input, char** error);

SGJSONValue* SG_EXPORT sgJSONValueCreateString(const char* str);
SGJSONValue* SG_EXPORT sgJSONValueCreateFile(const char* fname);
void SG_EXPORT sgJSONValueDestroy(SGJSONValue* value);

char* SG_EXPORT sgJSONToString(SGJSONValue* value, SGbool pretty);
void SG_EXPORT sgJSONArrayRemoveValue(SGJSONValue* array, SGJSONValue* value);
void SG_EXPORT sgJSONObjectSetValue(SGJSONValue* object, const char* key, SGJSONValue* value);
void SG_EXPORT sgJSONObjectRemoveValue(SGJSONValue* object, const char* key);
SGJSONValue* SG_EXPORT sgJSONObjectGetValue(SGJSONValue* object, const char* key);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_FILE_JSON_H__
