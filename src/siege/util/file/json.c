#define SG_BUILD_LIBRARY
#include <siege/util/file/json.h>
#include <siege/util/string.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

SGint SG_EXPORT _sgJSONTreeCmp(const void* a, const void* b)
{
    const SGJSONTreeItem* ai = a;
    const SGJSONTreeItem* bi = b;
    return strcmp(ai->key, bi->key);
}

void SG_EXPORT _sgJSONFreeValue(SGJSONValue* value)
{
    if(!value)
        return;

    SGJSONTreeItem* titem;

    switch(value->type)
    {
        case SG_JSON_TYPE_NULL:
        case SG_JSON_TYPE_BOOLEAN:
        case SG_JSON_TYPE_NUMBER:
            break; // nothing to do!
        case SG_JSON_TYPE_STRING:
        case SG_JSON_TYPE_COMMENT:
            free(value->v.string);
            break;
        case SG_JSON_TYPE_ARRAY:
            while(value->v.array->head)
                _sgJSONFreeValue(sgListPopFirst(value->v.array));
            sgListDestroy(value->v.array);
            break;
        case SG_JSON_TYPE_OBJECT:
            while(value->v.object->root)
            {
                titem = sgTreePopRoot(value->v.object);
                free(titem->key);
                _sgJSONFreeValue(titem->val);
                free(titem);
            }
            sgTreeDestroy(value->v.object);
            break;
    }
    free(value->strbuf);
    free(value);
}

void SG_EXPORT _sgJSONDumpTreeItem(SGTreeNode* node, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent)
{
    if(!node)
        return;

    if(node->left)
    {
        _sgJSONDumpTreeItem(node->left, str, len, mem, pretty, indent, indent);
        _sgStringAppend(str, len, mem, ",");
        if(pretty)
            _sgStringAppend(str, len, mem, "\n");
    }

    size_t i;
    if(pretty)
        for(i = 0; i < indent; i++)
            _sgStringAppend(str, len, mem, "\t");

    SGJSONTreeItem* titem = node->item;
    _sgStringAppend(str, len, mem, "\"");
    _sgJSONEscapeString(titem->key, str, len, mem);
    _sgStringAppend(str, len, mem, "\":");
    if(pretty)
        _sgStringAppend(str, len, mem, " ");
    _sgJSONDumpValue(titem->val, str, len, mem, pretty, indent, 0);

    if(node->right)
    {
        _sgStringAppend(str, len, mem, ",");
        if(pretty)
            _sgStringAppend(str, len, mem, "\n");
        _sgJSONDumpTreeItem(node->right, str, len, mem, pretty, indent, indent);
    }
}

void SG_EXPORT _sgJSONDumpValue(SGJSONValue* value, char** str, size_t* len, size_t* mem, SGbool pretty, size_t indent, size_t cindent)
{
    if(!value)
        return;

    SGListNode* node;

    size_t i;
    if(pretty)
        for(i = 0; i < cindent; i++)
            _sgStringAppend(str, len, mem, "\t");

    char* buf;

    switch(value->type)
    {
        case SG_JSON_TYPE_NULL:
            _sgStringAppend(str, len, mem, "null");
            break;
        case SG_JSON_TYPE_BOOLEAN:
            _sgStringAppend(str, len, mem, value->v.boolean ? "true" : "false");
            break;
        case SG_JSON_TYPE_NUMBER:
            buf = sgAPrintf("%g", value->v.number);
            _sgStringAppend(str, len, mem, buf);
            sgAPrintFree(buf);
            break; // nothing to do!
        case SG_JSON_TYPE_STRING:
            _sgStringAppend(str, len, mem, "\"");
            _sgJSONEscapeString(value->v.string, str, len, mem);
            _sgStringAppend(str, len, mem, "\"");
            break;
        case SG_JSON_TYPE_COMMENT:
            _sgStringAppend(str, len, mem, "***");
            _sgStringAppend(str, len, mem, value->v.comment);
            _sgStringAppend(str, len, mem, "***");
            break;
        case SG_JSON_TYPE_ARRAY:
            _sgStringAppend(str, len, mem, "[");
            if(pretty)
                _sgStringAppend(str, len, mem, "\n");
            for(node = value->v.array->head; node; node = node->next)
            {
                _sgJSONDumpValue(node->item, str, len, mem, pretty, indent + 1, indent + 1);
                if(node->next)
                    _sgStringAppend(str, len, mem, ",");
                if(pretty)
                    _sgStringAppend(str, len, mem, "\n");
            }
            if(pretty)
                for(i = 0; i < indent; i++)
                    _sgStringAppend(str, len, mem, "\t");
            _sgStringAppend(str, len, mem, "]");
            break;
        case SG_JSON_TYPE_OBJECT:
            _sgStringAppend(str, len, mem, "{");
            if(pretty)
                _sgStringAppend(str, len, mem, "\n");
            _sgJSONDumpTreeItem(value->v.object->root, str, len, mem, pretty, indent + 1, indent + 1);
            if(pretty)
                _sgStringAppend(str, len, mem, "\n");
            _sgStringAppend(str, len, mem, "}");
            if(pretty)
                _sgStringAppend(str, len, mem, "\n");
            break;
    }
}

char* SG_EXPORT _sgJSONSkipComments(char* input, char** error)
{
    char* end;
    SGJSONValue val;

    while(1)
    {
        input = sgSpaceEnd(input);

        end = _sgJSONParseComment(&val, input, error);
        if(input != end)
        {
            if(!end) return NULL;
            free(val.v.comment);
            input = end;
        }
        else
            break;
    }
    return input;
}
char* SG_EXPORT _sgJSONEscapeString(const char* input, char** str, size_t* len, size_t* mem)
{
    size_t i;
    for(i = 0; input[i]; i++)
    {
        if(*len + 6 >= *mem)
        {
            if(*mem == 0)
                *mem = 32;
            else
                *mem <<= 1;
            *str = realloc(*str, *mem);
        }

        if(strchr("\"\\\b\f\n\r\t", input[i]))
        {
            (*str)[(*len)++] = '\\';
            switch(input[i])
            {
                case '"':  (*str)[(*len)++] = '"';  break;
                case '\\': (*str)[(*len)++] = '\\'; break;
                case '\b': (*str)[(*len)++] = 'b';  break;
                case '\f': (*str)[(*len)++] = 'f';  break;
                case '\n': (*str)[(*len)++] = 'n';  break;
                case '\r': (*str)[(*len)++] = 'r';  break;
                case '\t': (*str)[(*len)++] = 't';  break;
            }
        }
        else if(input[i] < 32 || input[i] > 127)
        {
            //memcpy(&(*str)[*len], sgPrintf("\\u%.4X", input[i]), 6);
            sprintf(&(*str)[*len], "\\u%.4X", input[i]);
            *len += 6;
        }
        else
            (*str)[(*len)++] = input[i];
    }
    (*str)[*len] = 0;
    return *str;
}
SGbool SG_EXPORT _sgJSONGetSymbol(char** input)
{
    char* start = *input;

    if(strchr(SG_JSON_SYMBOL_SCHARS, **input))
        (*input)++;
    else
        return SG_FALSE;
    while(strchr(SG_JSON_SYMBOL_MCHARS, **input))
        (*input)++;

    return start != *input;
}

char* SG_EXPORT _sgJSONParseNull(SGJSONValue* into, char* input, char** error)
{
    char* start = input;
    into->type = SG_JSON_TYPE_NULL;

    // we can't use sgStartsWith here because we don't want to accept "nullfoo" or whatnot
    if(!_sgJSONGetSymbol(&input))
        return input;

    return strncmp(start, "null", input - start) ? start : input;
}
char* SG_EXPORT _sgJSONParseBoolean(SGJSONValue* into, char* input, char** error)
{
    char* start = input;
    into->type = SG_JSON_TYPE_BOOLEAN;

    // we can't use sgStartsWith here because we don't want to accept "nullfoo" or whatnot
    if(!_sgJSONGetSymbol(&input))
        return input;

    if(input - start == 4 && !strncmp(start, "true", input - start))
    {
        into->v.boolean = SG_TRUE;
        return input;
    }
    if(input - start == 5 && !strncmp(start, "false", input - start))
    {
        into->v.boolean = SG_FALSE;
        return input;
    }
    return start;
}
char* SG_EXPORT _sgJSONParseNumber(SGJSONValue* into, char* input, char** error)
{
    char* start = input;
    into->type = SG_JSON_TYPE_NUMBER;
    into->v.number = strtod(start, &input);

    return input;
}
char* SG_EXPORT _sgJSONParseString(SGJSONValue* into, char* input, char** error)
{
    char startc;
    into->type = SG_JSON_TYPE_STRING;

    SGbool escape = SG_FALSE;
    startc = *input;
    if(startc != '"' && startc != '\'' && startc != '`') // ' and ` are extensions
        return input;
    input++;

    size_t len = 0;
    size_t mem = 32;
    into->v.string = malloc(mem);

    size_t maxspan;
    size_t span;

    char convbuf[5];
    convbuf[4] = 0;
    unsigned long ul;

    while(*input)
    {
        /*
         * We need 2+1 additional memory:
         * Plus 2 potential chars (for \u) and null-termination.
         */
        if(len + 2 >= mem)
        {
            mem <<= 1;
            into->v.string = realloc(into->v.string, mem);
        }

        if(escape)
        {
            switch(*input)
            {
                case '"':
                case '\'':
                case '`':
                case '\\':
                case '/': into->v.string[len++] = *input; input++; break;
                case 'b': into->v.string[len++] = '\b'; input++; break;
                case 'f': into->v.string[len++] = '\f'; input++; break;
                case 'n': into->v.string[len++] = '\n'; input++; break;
                case 'r': into->v.string[len++] = '\r'; input++; break;
                case 't': into->v.string[len++] = '\t'; input++; break;
                case 'a': into->v.string[len++] = '\a'; input++; break; // extension
                case 'e': into->v.string[len++] = '\033'; input++; break; // extension
                case 'x': // extension
                case 'u':
                    maxspan = (*input == 'x') ? 2 : 4;
                    input++;
                    span = SG_MIN(strspn(input, SG_HEXDIGITS), maxspan);
                    /*
                     * It is fine to report an error, despite the extension -
                     * \xXX is illegal in JSON in either case without it.
                     */
                    if(span < maxspan)
                    {
                        *error = "Invalid \\xXX or \\uXXXX escape sequence!";
                        return NULL;
                    }
                    memcpy(convbuf, input, span);
                    convbuf[span] = 0;
                    input += span; // 2-4 hex digits
                    ul = strtoul(convbuf, NULL, 16);
                    if(maxspan == 4)
                        into->v.string[len++] = ul >> 8; // hi part
                    into->v.string[len++] = ul;
                    break;

                default:
                    // extension: \ooo octal escape
                    input++;
                    span = SG_MIN(strspn(input, SG_OCTDIGITS), 3); // we need up to 3!
                    if(span < 1) // no oct chars, which means we don't knwow what this is...
                    {
                        if(into->strbuf)
                            free(into->strbuf);
                        into->strbuf = sgAPrintf("Unknown escape sequence \\%c!", *input);
                        *error = into->strbuf;
                        return NULL;
                    }
                    // we have at least 1 oct char!

                    memcpy(convbuf, input, span);
                    convbuf[span] = 0;
                    input += span;
                    ul = strtoul(convbuf, NULL, 8);
                    into->v.string[len++] = ul;
            }
            escape = SG_FALSE;
        }
        else if(*input == '\\')
        {
            input++;
            escape = SG_TRUE;
        }
        else if(*input == startc)
        {
            input++;
            into->v.string[len] = 0;
            return input;
        }
        else
        {
            into->v.string[len++] = *input;
            input++;
        }
    }

    *error = "Unterminated string literal!";
    return NULL;
}
char* SG_EXPORT _sgJSONParseSymbol(SGJSONValue* into, char* input, char** error) // extensions
{
    char* start = input;
    into->type = SG_JSON_TYPE_STRING;

    if(!_sgJSONGetSymbol(&input))
        return start;

    into->v.string = malloc(input - start + 1);
    memcpy(into->v.string, start, input - start);
    into->v.string[input - start] = 0;

    return input;
}
char* SG_EXPORT _sgJSONParseComment(SGJSONValue* into, char* input, char** error) // extension
{
    char* start = input;
    into->type = SG_JSON_TYPE_COMMENT;

    if(sgStartsWith(input, "#") || sgStartsWith(input, "//"))
    {
        input = sgLineEnd(input);
        into->v.comment = malloc(input - start + 1);
        memcpy(into->v.comment, start, input - start);
        into->v.comment[input - start] = 0;
    }
    else if(sgStartsWith(input, "/*"))
    {
        input += 2;
        input = strstr(input, "*/");
        if(!input)
        {
            *error = "Unterminated comment!";
            return NULL;
        }
        input += 2; // to also get the */

        into->v.comment = malloc(input - start + 1);
        memcpy(into->v.comment, start, input - start);
        into->v.comment[input - start] = 0;
    }
    return input;
}

char* SG_EXPORT _sgJSONParseArray(SGJSONValue* into, char* input, char** error)
{
    char* end;
    SGJSONValue* val;
    into->type = SG_JSON_TYPE_ARRAY;

    if(*input != '[')
        return input;
    input++;

    into->v.array = sgListCreate();

    input = _sgJSONSkipComments(input, error);
    if(!input) return NULL;
    while(*input != ']' && *input)
    {
        if(into->v.array->head) // if there was a previous item, but no comma...
        {
            if(*input != ',')
            {
                if(into->strbuf)
                    free(into->strbuf);
                into->strbuf = sgAPrintf("Expected a comma, found '%c'", *input);
                *error = into->strbuf;
                return NULL;
            }
            else
                input++;
        }

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;

        if(*input == ']')
        {
            input++;
            return input;
        }

        val = malloc(sizeof(SGJSONValue));
        val->type = SG_JSON_TYPE_NULL;
        val->strbuf = NULL;

        end = _sgJSONParseValue(val, input, error);
        if(!end) return NULL;
        if(input == end)
        {
            *error = "Internal error";
            free(val);
            return NULL;
        }
        input = end;

        sgListAppend(into->v.array, val);

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;
    }

    if(!*input)
    {
        *error = "Mismatched opening array brace '['";
        return NULL;
    }
    input++;
    return input;
}
char* SG_EXPORT _sgJSONParseObject(SGJSONValue* into, char* input, char** error)
{
    char* end;
    SGJSONTreeItem* titem;
    SGJSONValue key;
    into->type = SG_JSON_TYPE_OBJECT;

    if(*input != '{')
        return input;
    input++;

    into->v.object = sgTreeCreate(_sgJSONTreeCmp);

    input = _sgJSONSkipComments(input, error);
    if(!input) return NULL;
    while(*input != '}' && *input)
    {
        if(into->v.array->head) // if there was a previous item, but no comma...
        {
            if(*input != ',')
            {
                if(into->strbuf)
                    free(into->strbuf);
                into->strbuf = sgAPrintf("Expected a comma, found '%c'", *input);
                *error = into->strbuf;
                return NULL;
            }
            input++;
        }

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;
        if(*input == '}')
        {
            input++;
            return input;
        }

        titem = malloc(sizeof(SGJSONTreeItem));
        end = input;
        if(_sgJSONGetSymbol(&end)) // extension
        {
            titem->key = malloc(end - input + 1);
            memcpy(titem->key, input, end - input);
            titem->key[end - input] = 0;
            input = end;
        }
        else
        {
            end = _sgJSONParseString(&key, input, error);
            if(end == NULL) return NULL;
            if(end == input)
            {
                if(into->strbuf)
                    free(into->strbuf);
                into->strbuf = sgAPrintf("Expected key, found '%c'", *input);
                *error = into->strbuf;
                free(titem);
                return NULL;
            }
            input = end;
            titem->key = key.v.string;
        }

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;

        if(*input != ':')
        {
            if(into->strbuf)
                free(into->strbuf);
            into->strbuf = sgAPrintf("Expected ':', found '%c'", *input);
            *error = into->strbuf;
            return NULL;
        }
        input++;

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;

        titem->val = malloc(sizeof(SGJSONValue));
        titem->val->type = SG_JSON_TYPE_NULL;
        titem->val->strbuf = NULL;

        end = _sgJSONParseValue(titem->val, input, error);
        if(!end) return NULL;
        if(input == end)
        {
            *error = "Internal error";
            free(titem->key);
            free(titem->val);
            free(titem);
            return NULL;
        }
        input = end;

        sgTreeInsert(into->v.object, titem);

        input = _sgJSONSkipComments(input, error);
        if(!input) return NULL;
    }

    if(!*input)
    {
        *error = "Mismatched opening object brace '{'";
        return NULL;
    }
    return input;
}

char* SG_EXPORT _sgJSONParseValue(SGJSONValue* into, char* input, char** error)
{
    char* end;

    input = _sgJSONSkipComments(input, error);
    if(!input) return NULL;

    end = _sgJSONParseNull(into, input, error);
    if(input != end) return end; // end can also be NULL, which indicates an error

    end = _sgJSONParseBoolean(into, input, error);
    if(input != end) return end;

    end = _sgJSONParseNumber(into, input, error);
    if(input != end) return end;

    end = _sgJSONParseString(into, input, error);
    if(input != end) return end;

    end = _sgJSONParseSymbol(into, input, error);
    if(input != end) return end;

    end = _sgJSONParseArray(into, input, error);
    if(input != end) return end;

    end = _sgJSONParseObject(into, input, error);
    if(input != end) return end;

    if(into->strbuf)
        free(into->strbuf);
    into->strbuf = sgAPrintf("Error parsing near '%c'", *input);
    *error = into->strbuf;
    return NULL;
}

SGJSONValue* SG_EXPORT sgJSONValueCreateString(const char* str)
{
    SGJSONValue* root = malloc(sizeof(SGJSONValue));
    root->strbuf = NULL;
    char* error;

    if(sgStartsWith(str, "\xEF\xBB\xBF")) // skip the byte order mark
        str = str + 3;

    char* ret = _sgJSONParseValue(root, (char*)str, &error);
    if(ret == NULL)
    {
        fprintf(stderr, "Error parsing JSON: %s\n", error);
        free(root);
        return NULL;
    }
    return root;
}
SGJSONValue* SG_EXPORT sgJSONValueCreateFile(const char* fname)
{
    FILE* file = fopen(fname, "rb");
    if(!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    rewind(file);

    char* str = malloc(len + 1);
    fread(str, 1, len, file);
    str[len] = 0;

    SGJSONValue* val = sgJSONValueCreateString(str);
    free(str);
    return val;
}
void SG_EXPORT sgJSONValueDestroy(SGJSONValue* value)
{
    if(!value)
        return;
    _sgJSONFreeValue(value);
}

char* SG_EXPORT sgJSONToString(SGJSONValue* value, SGbool pretty)
{
    size_t len = 0;
    size_t mem = 32;
    char* str = malloc(mem);
    _sgJSONDumpValue(value, &str, &len, &mem, pretty, 0, 0);
    if(value->strbuf)
        free(value->strbuf);
    value->strbuf = str;
    return str;
}
void SG_EXPORT sgJSONArrayRemoveValue(SGJSONValue* array, SGJSONValue* value)
{
    if(array->type != SG_JSON_TYPE_ARRAY)
        return;

    SGListNode* node;
    for(node = array->v.array->head; node; node = node->next)
    {
        if(node->item == value)
        {
            _sgJSONFreeValue(value);
            sgListRemoveNode(array->v.array, node);
            return;
        }
    }
}
void SG_EXPORT sgJSONObjectSetValue(SGJSONValue* object, const char* key, SGJSONValue* value)
{
    if(object->type != SG_JSON_TYPE_OBJECT)
        return;

    SGJSONTreeItem seek;
    seek.key = (char*)key;

    SGJSONTreeItem* titem;

    SGTreeNode* node = sgTreeFindItem(object->v.object, &seek);
    if(node)
    {
        titem = node->item;
        _sgJSONFreeValue(titem->val);
        titem->val = value;
    }
}
void SG_EXPORT sgJSONObjectRemoveValue(SGJSONValue* object, const char* key)
{
    if(object->type != SG_JSON_TYPE_OBJECT)
        return;

    SGJSONTreeItem titem;
    titem.key = (char*)key;

    SGTreeNode* node = sgTreeFindItem(object->v.object, &titem);
    if(node)
    {
        titem = *(SGJSONTreeItem*)node->item;
        free(titem.key);
        _sgJSONFreeValue(titem.val);
        free(node->item);
        sgTreeRemoveNode(object->v.object, node);
    }
}
SGJSONValue* SG_EXPORT sgJSONObjectGetValue(SGJSONValue* object, const char* key)
{
    if(object->type != SG_JSON_TYPE_OBJECT)
        return NULL;

    SGJSONTreeItem seek;
    seek.key = (char*)key;

    SGTreeNode* node = sgTreeFindItem(object->v.object, &seek);
    if(node)
        return node->item;
    return NULL;
}
