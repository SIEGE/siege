/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/util/arrops.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void* SG_EXPORT sgMap(void* base, size_t num, size_t size, SGMapFunction func)
{
    size_t i;
    for(i = 0; i < num; i++)
        //memmove(base + i * size, func(base + i * size), i * size);
        func(base + i * size);
    return base;
}

/*
    func: -
           +---+---+---+
    Index: | 0   1   2 | Operation
           +---+---+---+---+---+---+
    Step1: | 1   2   3 | func([1], [2]) -> [1]
    Step2: | 1  -1   ? | func([0], [1]) -> [0]
    Final: | 2   ?   ? |
           +---+---+---+
*/
void* SG_EXPORT sgRFold(void* base, size_t num, size_t size, SGFoldFunction func)
{
    ptrdiff_t i;
    for(i = num - 1; i >= 1; i--)
        func(base + i * (size - 1), base + i * (size - 1), base + i * size);
    return base;
}

/*
    func: -
           +---+---+---+
    Index: | 0   1   2 | Operation
           +---+---+---+---+---+---+
    Step1: | 1   2   3 | func([0], [1]) -> [0]
    Step2: |-1   ?   3 | func([0], [2]) -> [0]
    Final: |-4   ?   ? |
           +---+---+---+
*/
void* SG_EXPORT sgLFold(void* base, size_t num, size_t size, SGFoldFunction func)
{
    ptrdiff_t i;
    for(i = 0; i < num - 1; i++)
        func(base, base, base + i * (size + 1));
    return base;
}
