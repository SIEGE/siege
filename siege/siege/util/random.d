/**
    \brief Randomization
*/
module siege.util.random;

private
{
    import std.random;
}

/// \brief Alias from stdlib
alias std.random.rand_seed seed;
/// \brief Alias from stdlib
alias std.random.rand rand;

/* @{ */
/// \brief Random integer value in the range [0, max)
uint rand(uint max)
{
    return rand() % max;
}
/// \brief Random integer value in the range [min, max)
int rand(int min, int max)
{
    int tmp = min;
    min = max;
    max = tmp;

    return min + rand(max - min);
}
/* @} */
/* @{ */
/// \brief Random floating point value in the range [0, 1)
float frand()
{
    return rand() / cast(float)uint.max;
}
/// \brief Random floating point value in the range [0, max)
float frand(float max)
{
    return frand() * max;
}
/// \brief Random floating point value in the range [min, max)
float frand(float min, float max)
{
    float tmp = min;
    min = max;
    max = tmp;

    return min + frand(max - min);
}
/* @} */
/* @{ */
/* @{ */
/// \brief Random double-precision floating point value in the range [0, 1)
double drand()
{
    return rand() / cast(double)uint.max;
}
/// \brief Random double-precision floating point value in the range [0, max)
double drand(double max)
{
    return drand() * max;
}
/// \brief Random double-precision floating point value in the range [min, max)
double drand(double min, double max)
{
    double tmp = min;
    min = max;
    max = tmp;

    return min + drand(max - min);
}
/* @} */

/// \brief Random boolean - true or false
bool brand()
{
    return rand() < (uint.max / 2);
}

/**
    \brief Get a weighted random integer
    \param weights Represents the weight ratios to check against - for example, [25, 25, 50] means 25:25:50 chances of choosing 0, 1 and 2 respectively. Sum needs not to be 100
    \return The chosen number
*/
uint weight(float[] weights ...)
{
    real sum = 0;
    foreach(w; weights)
    {
        assert(w >= 0, "Weight must be nonnegative");
        sum += w;
    }
    assert(sum != 0, "Sum of weights must not be 0");

    real csum = 0;
    uint[] chances = new uint[](weights.length);
    foreach(i, w; weights)
    {
        chances[i] = cast(uint)((csum + w / sum) * uint.max);
        csum += w / sum;
    }

    uint r = rand() % uint.max;
    foreach(i, c; chances)
    {
        if(r < c)
            return i;
    }
    assert(0);
}
/// \brief Get a random item in an array
T choose(T)(T[] items ...)
{
    return items[rand(0, items.length)];
}
