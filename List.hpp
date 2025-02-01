#ifndef _LIST_HEADER
#define _LIST_HEADER

template <typename Any>
class List
{
private:
    struct unit
    {
        unit *before, *next;
        Any object;

        unit(void) : object() { before = next = nullptr; }
    };
    // A more complex and comsuming basic structure.
    // Provide a much better support to insert and pop.
    // Support more powerful iterator.

public:
    class Iterator // Powerful enough to be treat as pointers.
    {
    private:
        friend List;
        unit *here;

    protected:
    public:
        inline Iterator(void) { here = nullptr; }

        inline Iterator(const Iterator &other) { here = other.here; }

        inline Iterator &operator++(void)
        {
            here = here->next;
            return *this;
        }

        inline Iterator &operator++(int) { return ++(*this); }

        inline Iterator &operator--(void)
        {
            here = here->before;
            return *this;
        }

        inline Any &operator*(void) { return here->object; }

        inline Iterator &operator--(int) { return --(*this); }

        Iterator operator+(int offset);
        Iterator &operator+=(int offset);

        Iterator operator-(int offset);
        Iterator &operator-=(int offset);

        inline Any &operator[](int offset)
        {
            Iterator iter(*this);
            return *(iter + offset);
        }

        inline operator Any *(void) { return &(here->object); }
        // Behavior like a pointer.
    };

private:
    size_t element_count; // The counter for element amount.

    Iterator start; // An iterator that points to the first element.
    Iterator end;   // An iterator that points to the last element.

protected:
    /*
        The following functions are inner member functions that realize
        public member function `append` below.
        Expand template parameter package recursively.
    */
    template <typename... Args>
    void _append(Any &first_element, Args... parameters)
    {
        append(first_element);
        _append(forward<Args>(parameters)...); // Recursive call.
    }

    template <typename... Args>
    void _append(Any &&first_element, Args... parameters)
    {
        append(forward<Any>(first_element));
        _append(forward<Args>(parameters)...); // Recursive call.
    }

    template <typename... Args>
    void _append(Any *first_element, Args... parameters)
    {
        append(*first_element);
        _append(forward<Args>(parameters)...); // Recursive call.
    } // Support passing a pointer.

    inline void _append(void) {}
    // For a more robust program, set the end of the recursion.

    void release(void); // Deconstructor.

public:
    inline List(void) : start(), end() { element_count = 0; }
    // Default constructor without parameters for List.

    /* A more powerful constructor. */
    template <typename... Args>
    List(Args... parameters) : start(), end()
    {
        element_count = 0;
        _append(forward<Args>(parameters)...); // Recursive call.
    }

    List(std::initializer_list<Any> list);
    // Support initializer list syntax.

    List(const List &other);
    // Copy constructor for List.

    List(List &&other) : start(), end()
    {
        element_count = other.element_count;
        start.here = other.start.here;
        end.here = other.end.here;

        other.element_count = 0; // Prevent calling deconstructor unexpectedly.
        start.here = end.here = nullptr;
    }
    // Move constructor for List.

    /* More override operators for copy and move. */
    List &operator=(const List &other);

    List &operator=(List &&other)
    {
        release(); // Call deconstructor to prevent memory leaking.

        element_count = other.element_count;
        start.here = other.start.here;
        end.here = other.end.here;

        other.element_count = 0; // Prevent calling deconstructor unexpectedly.
        start.here = end.here = nullptr;

        return *this;
    }

    /* Get iterators. */
    inline Iterator begin(void) { return start; }
    inline Iterator tail(void) { return end; }

    /* Functions to append an element are below. */
    List &append(Any &obj);
    List &append(Any &&obj);

    List &operator<<(Any &obj) { return append(obj); }
    List &operator<<(Any &&obj) { return append(forward<Any>(obj)); }

    template <typename... Args>
    inline List &append(Args... parameters)
    {
        _append(forward<Args>(parameters)...);
        return *this;
    }

    /* Functions to get elements are below. */
    Any operator>>(Any &obj) { return pop(1); } // Delete from the list.
    Any pop(int offset);                        // Delete from the list.
    Any get(int offset);                        // Do nothing.
    Any &operator[](int offset);                // Return reference.

    /* Functions to insert elements are below. */
    List &insert(int where, Any &element);
    List &insert(int where, Any &&element);
    // Fill vacancy automatically.

    inline size_t length(void) { return element_count; }

    inline ~List(void) noexcept { release(); } // Call deconstructor.
};

template <typename Any>
typename List<Any>::Iterator
List<Any>::Iterator::operator+(int offset)
{
    if (offset < 0)
        return *this - (-offset);

    Iterator iter(*this);
    for (int i = 0; i < offset; i++)
        iter++;
    return iter;
}

template <typename Any>
typename List<Any>::Iterator &
List<Any>::Iterator::operator+=(int offset)
{
    if (offset < 0)
        return *this -= (-offset);

    for (int i = 0; i < offset; i++)
        (*this)++;
    return *this;
}

template <typename Any>
typename List<Any>::Iterator
List<Any>::Iterator::operator-(int offset)
{
    if (offset < 0)
        return *this + (-offset);

    Iterator iter(*this);
    for (int i = 0; i < offset; i++)
        iter--;
    return iter;
}

template <typename Any>
typename List<Any>::Iterator &
List<Any>::Iterator::operator-=(int offset)
{
    if (offset < 0)
        return *this += (-offset);

    for (int i = 0; i < offset; i++)
        (*this)--;
    return *this;
}

template <typename Any>
List<Any>::List(std::initializer_list<Any> list) : start(), end()
{
    element_count = 0;

    auto iterator = list.begin();
    for (int i = 0; i < list.size(); i++)
        append(*iterator), ++iterator;
}

template <typename Any>
List<Any> &List<Any>::append(Any &obj)
{
    if (element_count == 0)
    {
        start.here = new unit;
        start.here->before = start.here;
        start.here->next = start.here;
        end.here = start.here;
        start.here->object = obj;
        element_count++;
        return *this;
    }

    unit *temp = new unit;
    temp->next = start.here;
    temp->before = end.here;
    end.here->next = temp;
    start.here->before = temp;
    end.here = temp;

    end.here->object = obj;
    element_count++;
    return *this;
}

template <typename Any>
List<Any> &List<Any>::append(Any &&obj)
{
    if (element_count == 0)
    {
        start.here = new unit;
        start.here->before = start.here;
        start.here->next = start.here;
        end.here = start.here;
        start.here->object = forward<Any>(obj);
        element_count++;
        return *this;
    }

    unit *temp = new unit;
    temp->next = start.here;
    temp->before = end.here;
    end.here->next = temp;
    start.here->before = temp;
    end.here = temp;

    end.here->object = forward<Any>(obj);
    element_count++;
    return *this;
}

template <typename Any>
Any List<Any>::get(int offset)
{
    if (element_count == 0)
        return Any();

    /* Correct offset. */
    while (offset < 0)
        offset += element_count;
    while (offset >= element_count)
        offset -= element_count;

    Iterator iter;
    if (offset >= (element_count >> 1)) // Decrease the length of searching path.
    {
        iter = end;
        iter -= element_count - offset;
    }
    else
    {
        iter = start;
        iter += offset;
    }
    return iter.here->object;
}

template <typename Any>
Any List<Any>::pop(int offset)
{
    if (element_count == 0)
        return Any();

    /* Correct offset. */
    while (offset < 0)
        offset += element_count;
    while (offset >= element_count)
        offset -= element_count;

    if (offset == 0) // Popping the first element changes the start.
    {
        Any temp = start.here->object;
        start.here->before->next = start.here->next;
        start.here->next->before = start.here->before;

        unit *tmp = start.here;
        start++;
        delete tmp;
        return temp;
    }

    Iterator iter;
    if (offset >= (element_count >> 1)) // Decrease the length of searching path.
    {
        iter = end;
        iter -= element_count - offset;
    }
    else
    {
        iter = start;
        iter += offset;
    }

    Any temp = iter.here->object;
    iter.here->next->before = iter.here->before;
    iter.here->before->next = iter.here->next;
    delete iter.here;

    return temp;
}

template <typename Any>
Any &List<Any>::operator[](int offset)
{
    if (element_count == 0)
        throw 0;

    /* Correct offset. */
    while (offset < 0)
        offset += element_count;
    while (offset >= element_count)
        offset -= element_count;

    Iterator iter;
    if (offset >= (element_count >> 1)) // Decrease the length of searching path.
    {
        iter = end;
        iter -= element_count - offset - 1;
    }
    else
    {
        iter = start;
        iter += offset;
    }
    return iter.here->object;
}

template <typename Any>
List<Any> &List<Any>::insert(int where, Any &element)
{
    if (element_count == 0) // The first element appended.
    {
        start.here = end.here = new unit;
        start.here->next = start.here->before = start.here;
        end.here->next = end.here->before = start.here;
        start.here->object = element;
        element_count++;
        return *this;
    }

    /* Correct offset. */
    while (where < 0)
        where += element_count;
    while (where >= element_count)
        where -= element_count;

    Iterator iter;
    if (where >= (element_count >> 1))
    {
        iter = end;
        iter -= element_count - where - 1;
    }
    else
    {
        iter = start;
        iter += where;
    }

    unit *temp = new unit;
    temp->before = iter.here;
    temp->next = iter.here->next;
    iter.here->next->before = temp;
    iter.here->next = temp;
    temp->object = element;
    element_count++;

    return *this;
}

template <typename Any>
List<Any> &List<Any>::insert(int where, Any &&element)
{
    if (element_count == 0) // The first element appended.
    {
        start.here = end.here = new unit;
        start.here->next = start.here->before = start.here;
        end.here->next = end.here->before = start.here;
        start.here->object = forward<Any>(element);
        element_count++;
        return *this;
    }

    /* Correct offset. */
    while (where < 0)
        where += element_count;
    while (where >= element_count)
        where -= element_count;

    Iterator iter;
    if (where >= (element_count >> 1))
    {
        iter = end;
        iter -= element_count - where - 1;
    }
    else
    {
        iter = start;
        iter += where;
    }

    unit *temp = new unit;
    temp->before = iter.here;
    temp->next = iter.here->next;
    iter.here->next->before = temp;
    iter.here->next = temp;
    temp->object = forward<Any>(element);
    element_count++;

    return *this;
}

template <typename Any>
List<Any>::List(const List &other) : start(), end()
{
    element_count = other.element_count;
    Iterator iter = other.start;

    unit *here, *temp;
    if (element_count)
    {
        /* Tackle the first element separately. */
        here = new unit;
        here->before = here->next = here;
        start.here = here;
        end.here = here;

        here->object = *iter; // Call copy function.

        for (int i = 0; i < element_count - 1; i++)
        {
            /* Allocate new memory and append it to the tail. */
            temp = new unit;
            temp->before = here;
            temp->next = start.here;

            /* Move pointer. */
            here->next = temp;
            here = temp;
            end.here = temp;

            temp->object = *iter; // Call copy function.
            iter++;               // Deal with next element.
        }
    }
}

template <typename Any>
void List<Any>::release(void)
{
    if (element_count == 0)
        return; // Prevent program from segment fault.

    unit *temp;
    Iterator iter = start;
    for (int i = 0; i < element_count - 1; i++)
    {
        temp = iter.here;
        iter++;
        delete temp;
    }

    delete iter.here;
}

template <typename Any>
List<Any> &List<Any>::operator=(const List &other)
{
    release(); // Call deconstructor to prevent memory leaking.

    element_count = other.element_count;
    Iterator iter = other.start;

    unit *here, *temp;
    if (element_count)
    {
        /* Tackle the first element separately. */
        here = new unit;
        here->before = here->next = here;
        start.here = here;
        end.here = here;

        here->object = *iter; // Call copy function.

        for (int i = 0; i < element_count - 1; i++)
        {
            /* Allocate new memory and append it to the tail. */
            temp = new unit;
            temp->before = here;
            temp->next = start.here;

            /* Move pointer. */
            here->next = temp;
            here = temp;
            end.here = temp;

            temp->object = *iter; // Call copy function.
            iter++;               // Deal with next element.
        }
    }
}

#endif
