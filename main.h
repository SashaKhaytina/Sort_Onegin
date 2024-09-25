#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

struct StringPoint
{
    char* begin_str;
    char* end_str;
};

struct Text
{
    char* text;
    size_t len_text;

    StringPoint* strings_arr_p;  // массив указателей
    int len_strings;
};



#endif