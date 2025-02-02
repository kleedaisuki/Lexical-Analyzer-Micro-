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

typedef List<Token> Results;

void print(Token &token);
void fprint(FILE *file, Token &token);

char continue_as_label(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char continue_as_number(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char continue_as_operator(FILE *file, char *stack, int *counter, Token *aim, Results *results);
char analysis_operators(char *operators, Token *aim, Results *results, int count);
