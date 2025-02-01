#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

using std::forward, std::move;

#include "List.hpp"

#define LABEL_LIMITATION static_cast<int>(128 + 1)

enum token_t
{
    NUMBER,
    CHAR,
    LABEL,
    OPERATOR,
    STRING,
    KEYWORD,
    INSTRUCTION,
    ERROR,
};

struct Token
{
    char *str;
    token_t type;

    Token(void)
    {
        str = nullptr;
        type = static_cast<token_t>(0);
    }

    Token &operator=(Token &&other)
    {
        str = other.str, other.str = nullptr;
        type = other.type, other.type = static_cast<token_t>(0);
        return *this;
    }
};

class String
{
private:
protected:
    char *str;     // Point to the string stored in the memory.
    size_t size;   // The exact length of the string. '\0' is involved.
    size_t memory; // The space allocated.

    void expand(bool copy);
    // Mange space in memory automatically.
    // The boolean parameter decides whether to copy the string remained in the previously allocated memory.

    inline String(char *str, size_t length, size_t memory)
    {
        this->str = str;
        this->memory = memory;
        size = length;
    }
    // Other friend class or function may call.

public:
    String(void);

    String(const char *str);
    // Be careful as this constructor may be called unexpectedly.
    // Pay attention that adding an `explict` would bring other unexpected chaos.

    String(const String &str);
    // Copy a string directly.

    String(String &&other)
    {
        str = other.str;
        size = other.size;
        memory = other.memory;
        other.str = nullptr; // Aoiding calling deconstructor unexpectedly.
    }

    String &operator=(const char *str);
    String &operator=(const String &str);
    String &operator=(String &&other);
    // Copy the string from another string, with automatic and efficient memory management.

    bool operator==(const char *str) const;
    inline bool operator==(const String &_str) const { return *this == _str.c_str(); }
    // Compare strings.

    String operator+(const char *other);
    String operator+(String &other);
    inline String operator+(String &&other) { return *this + other; }
    // Join two strings into a new one.

    String operator*(unsigned int frequency);
    // Copy the string for the given frequency, then attach them to the original string.

    String &operator+=(const char *str);
    String &operator+=(const String &str);
    inline String &operator+=(String &&other) { return *this += other; }
    // Append directly. Return lvalue!

    char operator[](int offset) const;
    void strip(void);
    // Remove blanks for both sides.

    ~String(void) noexcept;

    inline size_t length(void) const { return size - 1; }
    inline const char *c_str(void) const { return str; }
    inline operator const char *(void) const { return str; }
    inline operator bool(void) const { return static_cast<bool>(size - 1); }
};

void print(Token &token);
void fprint(FILE *file, Token &token);

typedef List<String> KeywordQueue;
typedef List<Token> Results;

char continue_as_label(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char continue_as_number(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char continue_as_operator(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char analysis_operators(char *operators, Token *aim, Results *results, int count);
