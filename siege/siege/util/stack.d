module siege.util.stack;

private
{
    import std.string;

    import siege.core.exception;
    import siege.util.queue;
}

/**
    A LIFO (last in, first out).
*/
struct Stack(T)
{
    T[] items;

    /**
        Put an item on the stack.
    */
    void push(T item)
    {
        items ~= item;
    }

    /**
        Remove the value on top of the stack and return it.

        Throws:
            StackUnderflowException if empty.
    */
    T pop()
    {
        if(items.length == 0)
            throw new StackUnderflowException();

        T temp = items[$-1];
        items = items[0..$-1];

        return temp;
    }

    /**
        Peek at the value on top of the stack, but do not remove it.

        Throws:
            StackUnderflowException if empty.
    */
    T peek()
    {
        if(items.length == 0)
            throw new StackUnderflowException();

        return items[$-1];
    }

    /**
        Get the length of the stack
    */
    size_t length()
    {
        return items.length;
    }

    /**
        Removes all elements from the stack
    */
    void clear()
    {
        items.length = 0;
    }

    /*T[] opSlice(size_t one, size_t two)
    {
        T[] r = items.dup[one..two];
        return r;
    }*/

    T opIndex(size_t ind)
    {
        return items[ind];
    }

    char[] toString()
    {
        return std.string.format(items);
    }

    Queue!(T) toQueue()
    {
        return Queue!(T)(items);
    }
}
