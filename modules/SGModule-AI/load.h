#ifndef __LOAD_H__
#define __LOAD_H__
/////AI structs
typedef struct _Fuzzy
{
    SGdouble    num;
	SGchar*     name;
	SGbool      defuzzed;
	SGbool      evaluated;
}Fuzzy;

typedef struct _FuzzySet
{
    Fuzzy*      mFuzzy;
}FuzzySet;

typedef struct _FuzzyEngine
{
    FuzzySet    set;
    SGbool      hasList;
}FuzzyEngine;

#endif // __LOAD_H__
