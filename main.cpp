#include "tla.hpp"

void read_from_file(FILE *file, Results *results);

int main(int argc, char *argv[])
{
    FILE *file = fopen("List.hpp", "rt");
    Results results;
    read_from_file(file, &results);

    FILE *out = fopen("out-test.txt", "w");

    auto iter = results.begin();
    for (int i = 0; i < results.length(); i++, iter++)
        fprint(out, *iter);

    /* Clear. */
    for (int i = 0; i < results.length(); i++, iter++)
        free(static_cast<void *>((*iter).str));
    fclose(file);
    fclose(out);
}
