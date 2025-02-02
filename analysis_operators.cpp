#include "tla.hpp"

char analysis_operators(char *operators, Token *aim, Results *results, int count)
{
    char cur;

    for (int i = 0; i < count; i++)
    {
        switch (*operators)
        {
        case ' ':
            break;
        case '=':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '-':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
            case '-':
            case '>':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '+':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
            case '+':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '!':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '&':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
            case '&':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '|':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '=':
            case '|':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '>':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '>':
            case '=':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '<':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '<':
            case '=':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '*':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '/':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = INSTRUCTION;
                *results << std::move(*aim);
                break;
            case '=':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case ':':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case ':':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                *(aim->str) = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '/':
            cur = *operators;
            operators++, i++;
            switch (*operators)
            {
            case '*':
            case '/':
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = *operators;
                aim->str[2] = '\0';
                aim->type = INSTRUCTION;
                *results << std::move(*aim);
                break;
            case '\0':
                aim->str = static_cast<char *>(malloc(2));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                break;
            default:
                aim->str = static_cast<char *>(malloc(3));
                aim->str[0] = cur;
                aim->str[1] = '\0';
                aim->type = OPERATOR;
                *results << std::move(*aim);
                operators--, i--;
                break;
            }
            break;
        case '\"':
            aim->str = static_cast<char *>(malloc(2));
            aim->str[0] = *operators;
            aim->str[1] = '\0';
            aim->type = STRING;
            *results << std::move(*aim);
            break;
        case '\'':
            aim->str = static_cast<char *>(malloc(2));
            aim->str[0] = *operators;
            aim->str[1] = '\0';
            aim->type = CHAR;
            *results << std::move(*aim);
            break;
        case '~':
        case '^':
        case ']':
        case '}':
        case '(':
        case ')':
        case ',':
        case ';':
        case '?':
        case '[':
        case '{':
        case '#':
        case '.':
            aim->str = static_cast<char *>(malloc(2));
            aim->str[0] = *operators;
            aim->str[1] = '\0';
            aim->type = OPERATOR;
            *results << std::move(*aim);
            break;
        default:
            aim->str = static_cast<char *>(malloc(2));
            aim->str[0] = *operators;
            aim->str[1] = '\0';
            aim->type = CHAR;
            *results << std::move(*aim);
            break;
        }
        operators++;
    }
    return 1;
}
