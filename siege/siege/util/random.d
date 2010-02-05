module siege.util.random;

private
{
    import std.random;
}

alias std.random.rand_seed seed;
alias std.random.rand rand;

uint rand(uint max)
{
    return rand() % max;
}
int rand(int min, int max)
{
    int tmp = min;
    min = max;
    max = tmp;

    return min + rand(max - min);
}
float frand()
{
    return rand() / cast(float)uint.max;
}
float frand(float max)
{
    return frand() * max;
}
float frand(float min, float max)
{
    float tmp = min;
    min = max;
    max = tmp;

    return min + frand(max - min);
}
double drand()
{
    return rand() / cast(double)uint.max;
}
double drand(double max)
{
    return drand() * max;
}
double drand(double min, double max)
{
    double tmp = min;
    min = max;
    max = tmp;

    return min + drand(max - min);
}
bool brand()
{
    return rand() < (uint.max / 2);
}

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
T choose(T)(T[] items ...)
{
    return items[rand(0, items.length)];
}
