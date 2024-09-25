#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "utils.h"


int go_to_next_letter(char* str1, int ind_now)
{
    assert(str1);

    for (; !isalpha(str1[ind_now]); ind_now++) {}

    return ind_now;
}


int go_back_to_next_letter(char* str1, int ind_now)
{
    assert(str1);

    for (;isalpha(str1[ind_now]) == 0; ind_now--){}

    return ind_now;
}


size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}


int file_strings_counter(FILE* file)
{
    int counter_str = 0;

    size_t size_f = size_file(file);

    for (size_t i = 0; i < size_f; i++)
    {
        if (getc(file) == '\n')
        {
            counter_str++;
        }
    }

    return counter_str;
}


int strings_counter(const char* text)
{
    assert(text);

    int counter_str = 0;
    int ind = 0;

    while (text[ind] != '\0')
    {
        assert(text[ind]);

        if (text[ind] == '\n')
            counter_str++;
        ind++;
    }

    return counter_str;
}

