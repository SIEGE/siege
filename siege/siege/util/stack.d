/**
    \brief Implements a stack
    \todo Should this be merged with \ref siege.util.queue "queue"?
*/
module siege.util.stack;

private
{
    import std.string;

    import siege.core.exception;
    import siege.util.queue;
}

/**
    \brief A LIFO (last in, first out) - also called a stack
*/
struct Stack(T)
{
    T[] items;

    /// \brief Put an item on the stack
    void push(T item)
    {
        items ~= item;
    }


    /**
        \brief Remove the value from the top of the stack and return it
        \throw StackUnderflowException if empty
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
        \brief Peek at the value on top of the stack, but do not remove it
        \throw StackUnderflowException if empty
    */
    T peek()
    {
        if(items.length == 0)
            throw new StackUnderflowException();

        return items[$-1];
    }

    /// \brief Get the number of items on the stack
    size_t length()
    {
        return items.length;
    }

    /// \brief Remove all the elements from the stack
    void clear()
    {
        items.length = 0;
    }

    /*T[] opSlice(size_t one, size_t two)
    {
        T[] r = items.dup[one..two];
        return r;
    }*/

    /// \brief Get the n-th item from the stack
    T opIndex(size_t ind)
    {
        return items[ind];
    }

    /// \brief Get a string representation of the stack
    char[] toString()
    {
        return std.string.format(items);
    }

    /// \brief Convert the stack to a queue
    Queue!(T) toQueue()
    {
        return Queue!(T)(items);
    }
}
