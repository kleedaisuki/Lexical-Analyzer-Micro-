#include "tla.hpp"

static const char *keyword_queue[] = {
    "void",
    "signed",
    "unsigned",
    "char",
    "short",
    "int",
    "long",
    "float",
    "double",
    "if",
    "else",
    "for",
    "while",
    "do",
    "break",
    "continue",
    "switch",
    "case",
    "return",
    "template",
    "typename",
    "struct",
    "class",
    "union",
    "const",
    "voliate",
    "asm",
    "constexpr",
    "operator",
    "auto",
    "const_cast",
    "static_cast",
    "dynamic_cast",
    "reinterpret_cast",
    "and",
    "or",
    "not",
    "new",
    "delete",
}; // Unfinshed.

void print(Token &token) // Output to stdout.
{

    switch (token.type)
    {
    case LABEL:
        printf("@ LABEL       >> ");
        break;
    case OPERATOR:
        printf("+ OPERATOR    >> ");
        break;
    case KEYWORD:
        printf("* KEYWORD     >> ");
        break;
    case NUMBER:
        printf("$ NUMBER      >> ");
        break;
    case STRING:
        printf("~ STRING      >> ");
        break;
    case ERROR:
        printf("! ERROR       >> ");
        break;
    case CHAR:
        printf("^ CHAR        >> ");
        break;
    case INSTRUCTION:
        printf("& INSTRUCTION >> ");
        break;
    default:
        break;
    }
    printf("%s\n", token.str);
}

void fprint(FILE *file, Token &token)
{

    switch (token.type)
    {
    case LABEL:
        fprintf(file, "@ LABEL       >> ");
        break;
    case OPERATOR:
        fprintf(file, "+ OPERATOR    >> ");
        break;
    case KEYWORD:
        fprintf(file, "* KEYWORD     >> ");
        break;
    case NUMBER:
        fprintf(file, "$ NUMBER      >> ");
        break;
    case STRING:
        fprintf(file, "~ STRING      >> ");
        break;
    case ERROR:
        fprintf(file, "! ERROR       >> ");
        break;
    case CHAR:
        fprintf(file, "^ CHAR        >> ");
        break;
    case INSTRUCTION:
        fprintf(file, "& INSTRUCTION >> ");
        break;
    default:
        break;
    }
    fprintf(file, "%s\n", token.str);
}

static bool is_caracter(char ch)
{
    return (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or ch == '_';
}

static bool is_number(char ch)
{
    return (ch >= '0' and ch <= '9');
}

static bool is_blank(char ch)
{
    return ch == ' ' or ch == '\n' or ch == '\t';
}

static bool is_keyword(char *str)
{
    for (int i = 0; i < 39; i++)
        if (!strcmp(str, keyword_queue[i]))
            return true;
    return false;
}

void read_from_file(FILE *file, Results *results)
{
    char ch;
    char string_stack[LABEL_LIMITATION];
    int counter = 0;

    Token temp;

    do
    {
        ch = fgetc(file);
        if (is_blank(ch))
            continue;
        else if (is_caracter(ch))
        {
            string_stack[counter] = ch, counter++;
            ch = continue_as_label(file, string_stack, &counter, &temp, results);
            continue;
        }
        else if (is_number(ch))
        {
            string_stack[counter] = ch, counter++;
            ch = continue_as_number(file, string_stack, &counter, &temp, results);
            continue;
        }
        else if (ch != EOF)
        {
            string_stack[counter] = ch, counter++;
            ch = continue_as_operator(file, string_stack, &counter, &temp, results);
            continue;
        }
    } while (ch != EOF);
}

char continue_as_label(FILE *file, char *stack, int *counter, Token *aim, Results *results)
{
    char ch;
    do
    {
        ch = fgetc(file);
        if (is_caracter(ch) or is_number(ch))
        {
            if (*counter + 1 == LABEL_LIMITATION)
            {
                do
                {
                    ch = fgetc(file);
                } while (!is_caracter(ch) and !is_number(ch));

                stack[*counter] = '\0';
                aim->str = static_cast<char *>(malloc(*counter));
                memcpy(static_cast<void *>(aim->str), static_cast<const void *>(stack), *counter + 1);
                aim->type = LABEL;
                *counter = 0;

                *results << std::move(*aim);

                return ungetc(ch, file);
            }
            else
            {
                stack[*counter] = ch;
                (*counter)++;
            }
        }
        else if (is_blank(ch))
        {
            stack[*counter] = '\0';
            aim->str = static_cast<char *>(malloc(*counter + 1));
            memcpy(static_cast<void *>(aim->str), static_cast<const void *>(stack), *counter + 1);
            if (is_keyword(aim->str))
                aim->type = KEYWORD;
            else
                aim->type = LABEL;
            *counter = 0;

            *results << std::move(*aim);

            return ungetc(ch, file);
        }
        else
        {
            stack[*counter] = '\0';
            aim->str = static_cast<char *>(malloc(*counter + 1));
            memcpy(static_cast<void *>(aim->str), static_cast<const void *>(stack), *counter + 1);
            if (is_keyword(aim->str))
                aim->type = KEYWORD;
            else
                aim->type = LABEL;
            *counter = 0;

            *results << std::move(*aim);

            return ungetc(ch, file);
        }
    } while (ch != EOF);

    return EOF;
}

char continue_as_number(FILE *file, char *stack, int *counter, Token *aim, Results *results)
{
    char ch;
    do
    {
        ch = fgetc(file);
        if (is_number(ch))
        {
            stack[*counter] = ch;
            (*counter)++;
        }
        else if (is_caracter(ch))
        {
            do
            {
                ch = fgetc(file);
                if (*counter + 1 < LABEL_LIMITATION)
                    stack[*counter] = ch, (*counter)++;
            } while (is_caracter(ch) or is_number(ch));

            stack[*counter] = '\0';
            aim->str = static_cast<char *>(malloc(*counter + 1));
            memcpy(static_cast<void *>(aim->str), static_cast<const void *>(stack), *counter + 1);
            aim->type = ERROR;
            *counter = 0;

            *results << std::move(*aim);

            return ungetc(ch, file);
        }
        else
        {
            stack[*counter] = '\0';
            aim->str = static_cast<char *>(malloc(*counter + 1));
            memcpy(static_cast<void *>(aim->str), static_cast<const void *>(stack), *counter + 1);
            aim->type = NUMBER;
            *counter = 0;

            *results << std::move(*aim);

            return ungetc(ch, file);
        }
    } while (ch != EOF);

    return EOF;
}

char continue_as_operator(FILE *file, char *stack, int *counter, Token *aim, Results *results)
{
    char ch;
    do
    {
        ch = fgetc(file);
        if (is_caracter(ch) or is_number(ch) or is_blank(ch) or ch == EOF)
        {
            // It is belived that there would not be more than 128 operators once time.

            stack[*counter] = '\0';
            analysis_operators(stack, aim, results, *counter); // Seperate operators from each other.
            *counter = 0;

            return ungetc(ch, file);
        }
        else
        {
            stack[*counter] = ch;
            (*counter)++;
        }
    } while (ch != EOF);

    return EOF;
}
