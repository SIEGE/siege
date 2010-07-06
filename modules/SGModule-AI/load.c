#include "main.h"
#include "load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGint SG_EXPORT SGmAIFuzzyFInit1(Fuzzy *F)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyFInit2(Fuzzy *F, SGfloat ff)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyFInit3(Fuzzy *F, SGfloat ff, SGchar *name)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyFInit4(Fuzzy *F, SGdouble ff, SGchar* name)
{
    F->num = (SGfloat)ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyFInit5(Fuzzy *F, SGchar* name)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyFSetName(Fuzzy *F, SGchar* name)
{
    F->name = name;
    return SG_OK;
}

SGchar* SG_EXPORT SGmAIFuzzyFGetName(Fuzzy *F)
{
    return F->name;
}

SGint SG_EXPORT SGmAIFuzzyFSetNumber(Fuzzy *F, SGdouble n)
{
    F->num = (SGfloat)n;
    return SG_OK;
}

SGdouble SG_EXPORT SGmAIFuzzyFGetNumber(Fuzzy *F)
{
    return (SGdouble)F->num;
}

SGbool SG_EXPORT SGmAIFuzzyFContained(Fuzzy *F, SGdouble n)
{
    if (F->num < (SGfloat)n)
			return SG_TRUE;
		else
			return SG_FALSE;
}

SGchar* SG_EXPORT SGmAIFuzzyFShow(Fuzzy *F)
{
    assert(strcmp(SGmAIFuzzyFGetName(F),"")==0);
    return F->name;
}

SGint SG_EXPORT SGmAIFuzzyFSetDefuzzed(Fuzzy *F)
{
    F->defuzzed = SG_TRUE;
    return SG_OK;
}

SGbool SG_EXPORT SGmAIFuzzyFGetDefuzzed(Fuzzy *F)
{
    return F->defuzzed;
}

SGint SG_EXPORT SGmAIFuzzyFSetEvaluated(Fuzzy *F)
{
    F->evaluated = SG_TRUE;
    return SG_OK;
}

SGbool SG_EXPORT SGmAIFuzzyFGetEvaluated(Fuzzy *F)
{
    return F->evaluated;
}
