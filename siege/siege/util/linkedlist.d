module siege.util.linkedlist;

class LinkedListBoundsError: Exception
{
    this(char[] msg)
    {
        super(msg);
    }
}

class LinkedList(T)
{
    private
    {
        size_t len = 0;
    }

    LinkedNode!(T) *firstNode = null;
    LinkedNode!(T) *lastNode = null;

    LinkedNode!(T) *append(T item)
    {
        len++;

        LinkedNode!(T) *node = new LinkedNode!(T);
        node.previous = lastNode;
        node.item = item;
        node.next = null;

        if(firstNode is null)
            firstNode = node;
        if(lastNode !is null)
        {
            node.previous = lastNode;
            lastNode.next = node;
        }
        lastNode = node;

        return node;
    }

    LinkedNode!(T) *prepend(T item)
    {
        len++;

        LinkedNode!(T) *node = new LinkedNode!(T);
        node.previous = null;
        node.item = item;
        node.next = firstNode;

        if(lastNode is null)
            lastNode = node;
        if(firstNode !is null)
        {
            node.next = firstNode;
            firstNode.previous = node;
        }
        firstNode = node;

        return node;
    }

    void remove(LinkedNode!(T) *node)
    {
        len--;

        if(node.next !is null)
            node.next.previous = node.previous;
        if(node.previous !is null)
            node.previous.next = node.next;

        delete node;
    }

    T opIndex(uint index)
    {
        LinkedNode!(T) *p = firstNode;

        if (index >= len)
            throw new LinkedListBoundsError("Linked List index out of bounds");

        for(uint i = 0; i < index; i++)
        {
            p = p.next;
        }
        return p.item;
    }

    size_t length()
    {
        return len;
    }
}

struct LinkedNode(T)
{
    LinkedNode!(T) *previous;
    T item;
    LinkedNode!(T) *next;

    alias previous left;
    alias next right;
}

