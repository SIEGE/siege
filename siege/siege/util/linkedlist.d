/**
    \brief A linked list implementation
*/
module siege.util.linkedlist;

private
{
    import siege.core.exception;
}

/**
    \brief A linked list template class
*/
class LinkedList(T)
{
    private
    {
        size_t len = 0;
    }

    /// \brief The first node in the list
    LinkedNode!(T) *firstNode = null;
    /// \brief The last node in the list
    LinkedNode!(T) *lastNode = null;

    /**
        \brief Append an item to the list
        \param item The item to append
        \return The node that was created in the process
    */
    LinkedNode!(T)* append(T item)
    {
        len++;

        LinkedNode!(T) *node = new LinkedNode!(T);
        node.prev = lastNode;
        node.item = item;
        node.next = null;

        if(firstNode is null)
            firstNode = node;
        if(lastNode !is null)
        {
            node.prev = lastNode;
            lastNode.next = node;
        }
        lastNode = node;

        return node;
    }

    /**
        \brief Prepend an item to the list
        \param item The item to prepend
        \return The node that was created in the process
    */
    LinkedNode!(T)* prepend(T item)
    {
        len++;

        LinkedNode!(T)* node = new LinkedNode!(T);
        node.prev = null;
        node.item = item;
        node.next = firstNode;

        if(lastNode is null)
            lastNode = node;
        if(firstNode !is null)
        {
            node.next = firstNode;
            firstNode.prev = node;
        }
        firstNode = node;

        return node;
    }

    /**
        \brief Remove a node from the list
        \param node The node to remove
    */
    void remove(LinkedNode!(T)* node)
    {
        len--;

        if(node.next !is null)
            node.next.prev = node.prev;
        if(node.prev !is null)
            node.prev.next = node.next;

        delete node;
    }

    /**
        \brief Get the N-th item from the start of the list (pretend to be an array)
        \param index The item index to fetch
    */
    T opIndex(uint index)
    {
        LinkedNode!(T)* p = firstNode;

        if (index >= len)
            throw new LinkedListBoundsError("Linked List index out of bounds");

        for(uint i = 0; i < index; i++)
        {
            p = p.next;
        }
        return p.item;
    }

    /**
        \brief Get the number of items in the list (pretend to be an array)
    */
    size_t length()
    {
        return len;
    }

    /**
        \brief Overloaded for use with foreach and foreach_reverse
    */
    // @{
        int opApply(int delegate(ref T) dg)
        {
            int result = 0;

            LinkedNode!(T)* currentNode = firstNode;
            while(currentNode !is null)
            {
                result = dg(currentNode.item);
                if(result)
                    break;

                currentNode = currentNode.next;
            }
            return result;
        }

        int opApplyReverse(int delegate(ref T) dg)
        {
            int result = 0;

            LinkedNode!(T)* currentNode = lastNode;
            while(currentNode !is null)
            {
                result = dg(currentNode.item);
                if(result)
                    break;

                currentNode = currentNode.prev;
            }
            return result;
        }
    // @}
}

/**
    \brief Linked list node
*/
struct LinkedNode(T)
{
    /// \brief The item
    T item;
    /* @{ */
    /// \brief The previous node (null if this is the first node)
    LinkedNode!(T) *prev;
    /// \brief The next node (null if this is the last node)
    LinkedNode!(T) *next;
    /* @} */
    /**
        \name
        Aliases for the previous and the next node
    */
    /* @{ */
    /// \deprecated Use prev instead
    deprecated alias prev previous;
    alias prev left;
    alias next right;
    /* @} */
}

