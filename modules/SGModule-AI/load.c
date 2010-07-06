#include "main.h"
#include "load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGint SG_EXPORT SGmAIFuzzyInit1(Fuzzy *F)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyInit2(Fuzzy *F, SGfloat ff)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyInit3(Fuzzy *F, SGfloat ff, SGchar *name)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyInit4(Fuzzy *F, SGdouble ff, SGchar* name)
{
    F->num = (SGfloat)ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzyInit5(Fuzzy *F, SGchar* name)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT SGmAIFuzzySetName(Fuzzy *F, SGchar* name)
{
    F->name = name;
    return SG_OK;
}

SGchar* SG_EXPORT SGmAIFuzzyGetName(Fuzzy *F)
{
    return F->name;
}

SGint SG_EXPORT SGmAIFuzzySetNumber(Fuzzy *F, SGdouble n)
{
    F->num = (SGfloat)n;
    return SG_OK;
}

SGdouble SG_EXPORT SGmAIFuzzyGetNumber(Fuzzy *F)
{
    return (SGdouble)F->num;
}

SGbool SG_EXPORT SGmAIFuzzyContained(Fuzzy *F, SGdouble n)
{
    if (F->num < (SGfloat)n)
			return SG_TRUE;
		else
			return SG_FALSE;
}

SGchar* SG_EXPORT SGmAIFuzzyShow(Fuzzy *F)
{
    assert(strcmp(SGmAIFuzzyGetName(F),"")==0);
    return F->name;
}

SGint SG_EXPORT SGmAIFuzzySetDefuzzed(Fuzzy *F)
{
    F->defuzzed = SG_TRUE;
    return SG_OK;
}

SGbool SG_EXPORT SGmAIFuzzyGetDefuzzed(Fuzzy *F)
{
    return F->defuzzed;
}

SGint SG_EXPORT SGmAIFuzzySetEvaluated(Fuzzy *F)
{
    F->evaluated = SG_TRUE;
    return SG_OK;
}

SGbool SG_EXPORT SGmAIFuzzyGetEvaluated(Fuzzy *F)
{
    return F->evaluated;
}
