#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "working_with_text.h"
#include "utils.h"


ProgramStatus get_text(const char* file_name, Text* onegin)
{
    assert(file_name);
    assert(onegin);


    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return ERROR_OPENING_FILE;

    onegin->len_text = size_file(file);

    onegin->text = (char*) calloc(onegin->len_text + 1, sizeof(char));

    size_t count_symbol = fread(onegin->text, sizeof(char), (onegin->len_text), file);
    if (count_symbol != onegin->len_text) 
        return ERROR_READING;

    onegin->len_strings = strings_counter(onegin->text);
    
    fill_strings_arr(onegin);

    fclose(file);

    return OK;
}


ProgramStatus fill_strings_arr(Text* onegin)
{
    assert(onegin);


    onegin->strings_arr_p = (StringPoint*) calloc((size_t)(onegin->len_strings + 1), sizeof(StringPoint));
    if (onegin->strings_arr_p == NULL) 
        return ERROR_MEMORY;

    onegin->strings_arr_p->begin_str = onegin->text;  
    int current_str = 0;

    for (size_t i = 0; i < onegin->len_text; i++)
    {
        if ((onegin->text)[i] == '\n')
        {
            onegin->strings_arr_p[current_str].end_str = onegin->text + i;
            current_str++;
            onegin->strings_arr_p[current_str].begin_str = onegin->text + i + 1;

            (onegin->text)[i] = '\0';  // Расставляем концы строк
        }
    }

    return OK;
}
