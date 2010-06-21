/**
    \brief Implements a priority list
*/
module siege.util.plist;

private
{
    import std.string;
    import siege.util.misc;
}

/**
    \brief A priority list
*/
struct PList(T)
{
    private
    {
        bool _stop;
        ptrdiff_t _i;
    }

    uint type = HFO;
    float[] priorities;
    T[] items;

    void add(float p, T item)
    {
        bool op;
        foreach(i, _; items)
        {
            if(type & GT)
                op = priorities[i] > p;
            else if(type & GEQ)
                op = priorities[i] >= p;
            else if(type & LT)
                op = priorities[i] < p;
            else// if(type & LEQ)
                op = priorities[i] <= p;

            if(op)
            {
                priorities = priorities[0..i] ~ [p] ~ priorities[i..$];
                items = items[0..i] ~ [item] ~ items[i..$];
                return;
            }
        }

        priorities ~= p;
        items ~= item;
    }

    void removeItem(T item)
    {
        foreach(i, iitem; items)
            if(iitem == item)
            {
                removeIndex(i);
                return;
            }
    }
    void removeItems(T item)
    {
        size_t[] ilist;
        foreach(i, iitem; items)
            if(iitem == item)
                ilist ~= i;
        foreach_reverse(i; ilist)
            removeIndex(i);
    }
    void removePriority(float p)
    {
        removePSlice(p, p);
    }
    void removePSlice(float p1, float p2)
    {
        if(p1 > p2)
            swap(p1, p2);

        ptrdiff_t i1 = -1;
        ptrdiff_t i2 = -1;
        bool op1;
        bool op2;
        foreach(i, _; items)
        {
            if(type & GT || type & GEQ)
            {
                op1 = priorities[i] < p1;
                op2 = priorities[i] > p2;
            }
            else //if(type & LT && type & LEQ)
            {
                op1 = priorities[i] > p2;
                op2 = priorities[i] < p1;
            }
            if(op1)
                continue;
            if(op2)
                break;

            if(i1 == -1)
                i1 = i;
            i2 = i;
        }
        removeISlice(i1, i2 + 1);
    }
    void removeIndex(size_t i)
    {
        removeISlice(i, i + 1);
    }
    void removeISlice(size_t i1, size_t i2)
    {
        if(i1 > items.length)
            return;
        if(i2 > items.length)
            return;
        if(i1 > i2)
            swap(i1, i2);

        priorities = priorities[0..i1] ~ priorities[i2..$];
        items = items[0..i1] ~ items[i2..$];

        // make sure we're at the correct index if items were removed from inside of the event
        if((i1 <= _i) && (_i < i2))
            _i -= i1 + 1;
        else if(i2 <= _i)
            _i -= i2 - i1;
    }

    /// \brief Get the number of items in the list
    size_t length()
    {
        return items.length;
    }

    /// \brief Remove all the elements from the list
    void clear()
    {
        priorities.length = 0;
        items.length = 0;
    }

    /*T[] opSlice(size_t one, size_t two)
    {
        T[] r = items.dup[one..two];
        return r;
    }*/

    /// \brief Get the n-th item from the list
    T opIndex(size_t ind)
    {
        return items[ind];
    }

    /// \brief Get a string representation of the list
    char[] toString()
    {
        return format(items);
    }

    int opApply(int delegate(inout T) dg)
    {
        _stop = false;
        int result = 0;
        for(_i = 0; _i < items.length; _i++)
        {
            result = dg(items[_i]);
            if(result || _stop)
                break;
        }
        return result;
    }

    int opApplyReverse(int delegate(inout T) dg)
    {
        _stop = false;
        int result = 0;
        for(_i = items.length - 1; _i >= 0; _i--)
        {
            result = dg(items[_i]);
            if(result || _stop)
                break;
        }
        return result;
    }

    void stop()
    {
        _stop = true;
    }

static:
    const LEQ = (1<<0);
    const LT  = (1<<1);
    const GEQ = (1<<2);
    const GT  = (1<<3);

    const HFN = LEQ;
    const HFO = LT;
    const LFN = GEQ;
    const LFO = GT;
}
