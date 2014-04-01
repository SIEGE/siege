#define SG_BUILD_LIBRARY
#include <siege/util/getopt.h>

#include <stdio.h>
#include <string.h>

static SGlong _sgGetOptFindLongInd(SGGetOpt* getopt, const char* name, size_t len)
{
    const SGOption* option;
    if(!getopt->longopts) return -1;

    for(option = getopt->longopts; option->name; option++)
        if(strlen(option->name) == len && !memcmp(option->name, name, len))
            return option - getopt->longopts;
    return -1;
}

static SGint _sgGetOptLongInd(SGGetOpt* getopt, SGlong* longind, char** arg, char* pair)
{
    char* eq = strchr(pair, '=');
    size_t len = (eq ? eq - pair : strlen(pair));

    const SGOption* opt;

    getopt->longind = _sgGetOptFindLongInd(getopt, pair, len);
    if(getopt->longind == -1)
    {
        getopt->err = '?';
        getopt->val = '-';
    }
    else
    {
        if(eq) eq++;
        opt = &getopt->longopts[getopt->longind];
        getopt->val = opt->val;

        switch(opt->atype)
        {
        case SG_ARG_NONE:
            if(eq)
            {
                getopt->err = '=';
                getopt->arg = eq;
            }
            break;
        case SG_ARG_OPTIONAL:
            if(eq)
                getopt->arg = eq;
            break;
        case SG_ARG_REQUIRED:
            if(eq)
                getopt->arg = eq;
            else
                getopt->err = '?';
            break;
        default:
            SG_ASSERT(0, "Invalid SGOption.atype");
            break;
        }
    }

    getopt->ind++;

    *longind = getopt->longind;
    *arg = getopt->arg;
    return getopt->err ? getopt->err : getopt->val;
}

static SGint _sgGetOptInArg(SGGetOpt* getopt, SGlong* longind, char** arg)
{
    SG_ASSERT(getopt && getopt->inarg && *getopt->inarg, "NULL getopt or getopt->inarg passed");

    if(longind) *longind = -1;
    if(arg) *arg = NULL;

    char* inarg = getopt->inarg;

    /* TODO: do this strchr properly */
    char* sub = strchr(getopt->shortopts, *inarg);
    if(!sub)
    {
        getopt->err = '?'; /* missing argument to -%c */
        getopt->val = *inarg;
    }
    else
    {
        inarg++;

        getopt->val = sub[0];
        if(sub[1] == ':')
        {
            if(!*inarg)
            {
                if(++getopt->ind >= getopt->argc)
                    getopt->err = '?'; /* missing argument to -%c */
                else
                    getopt->arg = getopt->argv[getopt->ind++];
            }
            else
            {
                getopt->ind++;
                getopt->arg = inarg;
            }
            getopt->inarg = NULL;
        }
        else
            getopt->inarg = inarg;
    }

    if(getopt->inarg && !*getopt->inarg)
    {
        getopt->ind++;
        getopt->inarg = NULL;
    }

    *arg = getopt->arg;
    return getopt->err ? getopt->err : getopt->val;
}

SGOption SG_CALL sgOption(const char* name, SGenum atype, SGint val)
{
    SGOption opt;
    opt.name = name;
    opt.atype = atype;
    opt.val = val;
    return opt;
}

SGGetOpt* SG_CALL sgGetOptInit(SGGetOpt* getopt, size_t argc, char* const* argv, const char* shortopts, const SGOption* longopts)
{
    if(!getopt) return NULL;
    getopt->ind = 1;
    getopt->inarg = NULL;
    getopt->argc = argc;
    getopt->argv = argv;
    getopt->shortopts = shortopts;
    getopt->longopts = longopts;

    getopt->err = 0;
    getopt->val = EOF;
    getopt->longind = -1;
    getopt->arg = NULL;
    return getopt;
}

SGint SG_CALL sgGetOptNext(SGGetOpt* getopt, SGlong* longind, char** arg)
{
    getopt->err = 0;
    getopt->val = EOF;
    getopt->longind = -1;
    getopt->arg = NULL;

    if(getopt->inarg)
        return _sgGetOptInArg(getopt, longind, arg);

    if(getopt->ind >= getopt->argc) return EOF;

    char* argv = getopt->argv[getopt->ind];
    if(argv[0] != '-') return EOF;
    argv++;

    if(argv[0] == '-') /* -- or --foo */
    {
        argv++;
        if(argv[0]) /* --foo */
             return _sgGetOptLongInd(getopt, longind, arg, argv);
        else /* -- */
            goto end;
    }
    else /* -x or - */
    {
        if(argv[0]) /* -x at 'x' */
        {
            getopt->inarg = argv;
            return _sgGetOptInArg(getopt, longind, arg);
        }
        else /* "-"; not an option */
            goto end;
    }
end:
    getopt->ind++;
    return EOF;
}
