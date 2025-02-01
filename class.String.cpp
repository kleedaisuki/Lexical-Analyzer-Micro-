#include "tla.hpp"

void String::expand(bool copy)
/* Set member variable `set` and it could allot memory automatically. */
{
    if (memory <= size)
    {
        do
        {
            memory <<= 1;
        } while (memory <= size);
        if (copy)
        {
            char *temp = new char[memory];
            sprintf(temp, "%s", str);
            delete[] str;
            str = temp;
        }
        else
        {
            delete[] str;
            str = new char[memory];
        }
    }
    else
    {
        if (!str)
            str = new char[memory];
    }
}

String::String(void)
{
    str = new char[32];
    memory = 32;
    size = 1;
    *str = '\0';
}

String::String(const char *_str)
{
    str = NULL;
    size = strlen(_str) + 1;
    memory = 32;
    expand(false);
    sprintf(str, "%s", _str);
}

String::String(const String &_str)
{
    str = NULL;
    size = _str.size;
    memory = 32;
    expand(false);
    sprintf(str, "%s", _str.c_str());
}

String &String::operator=(const char *_str)
{
    size = strlen(_str) + 1;
    expand(false);
    sprintf(str, "%s", _str);

    return *this;
}

String &String::operator=(const String &_str)
{
    size = _str.size;
    expand(false);
    sprintf(str, "%s", _str.c_str());
    return *this;
}

String &String::operator=(String &&other)
{
    if (str)
        delete[] str;

    size = other.size;
    memory = other.memory;
    str = other.str;

    other.str = NULL;
    return *this;
}

bool String::operator==(const char *_str) const
{
    const char *here = str;
    const char *there = _str;

    while (*here and *there)
    {
        if (*here != *there)
            return false;
        here++, there++;
    }
    return *here == *there;
}

String &String::operator+=(const char *_str)
{
    size += strlen(_str);
    expand(true);

    if (!_str)
        return *this;
    char *locate = str;
    while (*locate)
        locate++;
    sprintf(locate, "%s", _str);

    return *this;
}

String &String::operator+=(const String &_str)
{
    size += _str.size - 1;
    expand(true);

    if (!_str)
        return *this;
    char *locate = str;
    while (*locate)
        locate++;
    sprintf(locate, "%s", _str);

    return *this;
}

char String::operator[](int offset) const
{
    size_t len = length();
    while (offset < 0)
        offset += len;
    while (offset >= len)
        offset -= len;

    return str[offset];
}

void String::strip(void)
{
    String copy(*this);

    const char *start = copy.str;
    char *write_char, *end = copy.str + copy.size - 1;
    while (*start == ' ')
        start++;
    while (*end == ' ')
        end--;
    end++;
    *end = '\0';

    size = strlen(start) + 1;
    expand(false);
    sprintf(str, "%s", start);
}

String String::operator+(const char *other)
{
    String result(*this);
    result += other;
    return result;
}

String String::operator+(String &other)
{
    String result(*this);
    result += other;
    return result;
}

String::~String(void) noexcept
{
    if (str) // Aoiding calling deconstructor unexpectedly.
        delete[] str;
}
