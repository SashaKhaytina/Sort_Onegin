#include <stdio.h>
#include <assert.h>

#include "io.h"
#include "working_with_text.h"


void print_text_by_buffer(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    char* point = onegin->text;

    for (int i = 0; i < onegin->len_strings; i++)
        point += fprintf(file, "%s\n", point);

    fprintf(file, "\n");
}


void print_text_by_strings(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    for (int i = 0; i < (onegin->len_strings); i++)
        fprintf(file, "%s\n", ((onegin->strings_arr_p) + i)->begin_str);
    
    fprintf(file, "\n\n");
}
