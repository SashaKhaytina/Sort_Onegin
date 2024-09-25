#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>

#include "main.h"
#include "func_sort.h"
#include "utils.h"
#include "errors.h"


void          print_given_text (Text* onegin, FILE* file);            // НАЧАЛЬНЫЙ!!!!  (в файл)
void          print_sorted_text(Text* onegin, FILE* file);            // Сортированный  (в тот же файл)

ProgramStatus get_text         (const char* file_name, Text* onegin); // запись в двумерный массив
ProgramStatus fill_strings_arr (Text* onegin);                        // Заполнение массива указателей



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



void print_given_text(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    char* point = onegin->text;

    for (int i = 0; i < (onegin->len_strings); i++)
        point += fprintf(file, "%s\n", point);

    fprintf(file, "\n");
}


void print_sorted_text(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    for (int i = 0; i < (onegin->len_strings); i++)
        fprintf(file, "%s\n", ((onegin->strings_arr_p) + i)->begin_str);
    
    fprintf(file, "\n\n");
}


ProgramStatus get_text(const char* file_name, Text* onegin)
{
    assert(file_name);
    assert(onegin);


    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return ERROR_OPENING_FILE;

    onegin->len_text = size_file(file);

    onegin->text = (char*) calloc((onegin->len_text + 1), sizeof(char));


    // Считывание файла (fread)
    size_t count_symbol = fread(onegin->text, sizeof(char), (onegin->len_text), file);
    if (count_symbol != onegin->len_text) 
        return ERROR_READING;

    onegin->len_strings = strings_counter(onegin->text);
    

    // Заполнение массива указателей
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
    int ind_fill_now = 0;

    for (size_t i = 0; i < onegin->len_text; i++)
    {
        if ((onegin->text)[i] == '\n')
        {
            onegin->strings_arr_p[ind_fill_now].end_str = onegin->text + i;
            ind_fill_now++;
            onegin->strings_arr_p[ind_fill_now].begin_str = onegin->text + i + 1;

            (onegin->text)[i] = '\0';  // Расставляем концы строк
        }
    }

    return OK;
}
