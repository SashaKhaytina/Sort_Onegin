#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

#include "main.h"
#include "func_sort.h"
#include "utils.h"
#include "errors.h"
#include "io.h"


int main()
{
    ProgramStatus status = OK;

    Text onegin = {};

    status = get_text("text.txt", &onegin);
    if (status != OK)
    {
        print_errors_code(status);
        return 0;
    }


    FILE* file = fopen("output.txt", "w");
    if (file == NULL)
    {
        status = ERROR_OPENING_FILE;
        print_errors_code(status);
        return 0;
    }


    // Сортировка с начала строки
    murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_first_elem);
    print_sorted_text(&onegin, file);

    // Сортировка с конца строки
    murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_end_elem);
    print_sorted_text(&onegin, file);


    print_given_text(&onegin, file);

    fclose(file);

    free(onegin.strings_arr_p);
    free(onegin.text);

    print_errors_code(status);
}
