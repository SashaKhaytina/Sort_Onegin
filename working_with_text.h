#ifndef WWT_H
#define WWT_H

#include <stdio.h>

#include "errors.h"


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


ProgramStatus get_text         (const char* file_name, Text* onegin); // Запись в двумерный массив
ProgramStatus fill_strings_arr (Text* onegin);                        // Заполнение массива указателей


#endif 