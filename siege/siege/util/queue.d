/**
    \brief Implements a queue
    \todo Should this be merged with \ref siege.util.stack "stack"?
*/
module siege.util.queue;

private
{
    import std.string;

    import siege.core.exception;
    import siege.util.stack;
}

/**
    \brief A FIFO (first in, first out) - also called a queue
*/
struct Queue(T)
{
    T[] items;

    /// \brief Put an item in the queue
    void push(T item)
    {
        items ~= item;
    }

    /**
        \brief Remove the value from the top of the queue and return it
        \throw QueueUnderflowException if empty
    */
    T pop()
    {
        if(items.length == 0)
            throw new QueueUnderflowException();

        T temp = items[0];
        items = items[1..$];

        return temp;
    }

    /**
        \brief Peek at the value on top of the queue, but do not remove it
        \throw QueueUnderflowException if empty
    */
    T peek()
    {
        if(items.length == 0)
            throw new QueueUnderflowException();

        return items[0];
    }

    /// \brief Get the number of items in the queue
    size_t length()
    {
        return items.length;
    }

    /// \brief Remove all the elements from the queue
    void clear()
    {
        items.length = 0;
    }

    /*T[] opSlice(size_t one, size_t two)
    {
        T[] r = items.dup[one..two];
        return r;
    }*/

    /// \brief Get the n-th item from the queue
    T opIndex(size_t ind)
    {
        return items[ind];
    }

    /// \brief Get a string representation of the queue
    char[] toString()
    {
        return std.string.format(items);
    }

    /// \brief Convert the queue to a stack
    Stack!(T) toStack()
    {
        return Stack!(T)(items);
    }
}
