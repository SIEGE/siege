#ifndef __SIEGE_UTIL_GETOPT_H__
#define __SIEGE_UTIL_GETOPT_H__

#include "../common.h"

#define SG_ARG_NONE     0
#define SG_ARG_OPTIONAL 1
#define SG_ARG_REQUIRED 2

typedef struct SGOption
{
    const char* name;
    SGenum atype;
    SGint val;
} SGOption;

SGOption SG_CALL sgOption(const char* name, SGenum atype, SGint val);

typedef struct SGGetOpt
{
    size_t ind;
    char* inarg;
    size_t argc;
    char* const* argv;
    const char* shortopts;
    const SGOption* longopts;

    char err;
    SGint val;
    SGlong longind;
    char* arg;
} SGGetOpt;

SGGetOpt* SG_CALL sgGetOptInit(SGGetOpt* getopt, size_t argc, char* const* argv, const char* shortopts, const SGOption* longopts);

SGint SG_CALL sgGetOptNext(SGGetOpt* getopt, SGlong* longind, char** arg);

#endif /* __SIEGE_UTIL_GETOPT_H__ */
