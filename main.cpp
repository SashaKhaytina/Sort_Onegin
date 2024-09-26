#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

#include "working_with_text.h"
#include "func_sort.h"
#include "utils.h"
#include "errors.h"
#include "io.h"


#define ASSERT(status, ...) \
    if (!(__VA_ARGS__)) \
    { \
        print_errors_code(status); \
        return status; \
    }


void text_free(Text* onegin);


int main()
{
    ProgramStatus status = OK;

    Text onegin = {};

    status = get_text("text.txt", &onegin);
    ASSERT(status, status == OK);

    FILE* file = fopen("output.txt", "w");
    ASSERT(ERROR_OPENING_FILE, file != NULL);
    

    // Сортировка с начала строки
    murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_first_elem);
    print_text_by_strings(&onegin, file);

    // Сортировка с конца строки
    murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_end_elem);
    print_text_by_strings(&onegin, file);

    print_text_by_buffer(&onegin, file);

    fclose(file);

    text_free(&onegin);

    print_errors_code(status);
}


void text_free(Text* onegin)
{
    free(onegin->strings_arr_p);
    free(onegin->text);
}