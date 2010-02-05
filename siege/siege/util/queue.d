module siege.util.queue;

private
{
    import std.string;

    import siege.core.exception;
    import siege.util.stack;
}

/**
    A FIFO (first in, first out).
*/
struct Queue(T)
{
    T[] items;

    /**
        Put an item on the queue.
    */
    void push(T item)
    {
        items ~= item;
    }

    /**
        Remove the value on top of the queue and return it.

        Throws:
            QueueUnderflowException if empty.
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
        Peek at the value on top of the queue, but do not remove it.

        Throws:
            QueueUnderflowException if empty.
    */
    T peek()
    {
        if(items.length == 0)
            throw new QueueUnderflowException();

        return items[0];
    }

    /**
        Get the length of the queue
    */
    size_t length()
    {
        return items.length;
    }

    /**
        Removes all elements from the queue
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

    Stack!(T) toStack()
    {
        return Stack!(T)(items);
    }
}
