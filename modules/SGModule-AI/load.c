#include "main.h"
#include "load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGint SG_EXPORT sgmAIFuzzyFInit1(Fuzzy *F)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFInit2(Fuzzy *F, SGfloat ff)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFInit3(Fuzzy *F, SGfloat ff, SGchar *name)
{
    F->num = ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFInit4(Fuzzy *F, SGdouble ff, SGchar* name)
{
    F->num = (SGfloat)ff;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFInit5(Fuzzy *F, SGchar* name)
{
    F->num = 0;
    F->defuzzed = SG_FALSE;
	F->evaluated = SG_FALSE;
	F->name = name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFSetName(Fuzzy *F, SGchar* name)
{
    F->name = name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFGetName(Fuzzy *F, SGchar* name)
{
    name = F->name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFSetNumber(Fuzzy *F, SGdouble n)
{
    F->num = (SGfloat)n;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFGetNumber(Fuzzy *F, SGdouble* num)
{
    *num = (SGdouble)F->num;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFContained(Fuzzy *F, SGdouble n, SGbool* b)
{
    if (F->num < (SGfloat)n)
            *b = SG_TRUE;
		else
            *b = SG_FALSE;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFShow(Fuzzy *F, SGchar* name)
{
    SGchar* tmp;
    sgmAIFuzzyFGetName(F,tmp);
    assert(strcmp(tmp,"")==0);
    name = F->name;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFSetDefuzzed(Fuzzy *F)
{
    F->defuzzed = SG_TRUE;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFGetDefuzzed(Fuzzy *F, SGbool* b)
{
    *b = F->defuzzed;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFSetEvaluated(Fuzzy *F)
{
    F->evaluated = SG_TRUE;
    return SG_OK;
}

SGint SG_EXPORT sgmAIFuzzyFGetEvaluated(Fuzzy *F, SGbool* b)
{
    *b = F->evaluated;
    return SG_OK;
}
