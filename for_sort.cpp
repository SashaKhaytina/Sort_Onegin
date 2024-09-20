#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>

#include "func_sort.h"
#include "utils.h"
#include "errors.h"


struct Text
{
    char* text;
    int len_text;

    char** ind_arr;  // массив указателей
    int len_strings;
};


void print_given_text  (Text* onegin, FILE* file);      // НАЧАЛЬНЫЙ!!!!  (в файл)
void print_sorted_text (Text* onegin, FILE* file);      // Сортированный  (в тот же файл)
void print_errors_code (ProgramStatus status);

ProgramStatus read_file         (char* file_name, Text* onegin); // запись в двумерный массив
ProgramStatus filling_points_arr(Text* onegin);                  // Заполнение массива указателей



int main()
{
    ProgramStatus status = OK;

    Text onegin = {};

    status = read_file("text.txt", &onegin);
    if (status != OK)
    {
        print_errors_code(status);
        return 0;
    }


    // ---- вывод -----
    printf("%s\n\n", (onegin.ind_arr)[7]); 
    // ---- конец -----


    FILE* file = fopen("output.txt", "w");
    if (file == NULL)
    {
        status = ERROR_OPENING_FILE;
        print_errors_code(status);
        return 0;
    }


    // ---- вывод -----
    print_given_text(&onegin, file);
    printf("%p - значение! первый с массиве указателей\n", onegin.ind_arr[0]);
    // ---- конец -----


    // Сортировка с начала строки
    murderous_sort(onegin.ind_arr, onegin.len_strings, sizeof(char*), murderous_compare_str_first_elem);
    print_sorted_text(&onegin, file);

    // Сортировка с конца строки
    murderous_sort(onegin.ind_arr, onegin.len_strings, sizeof(char*), murderous_compare_str_end_elem);
    print_sorted_text(&onegin, file);

    fclose(file);

    free(onegin.ind_arr);
    free(onegin.text);

    print_errors_code(status);
}



void print_given_text(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    char* point = NULL;
    point = onegin->text;

    for (int i = 0; i < onegin->len_text; i++)
    {
        char c = *point;

        if (c == '\0') fprintf(file, "\n");
        else           fprintf(file, "%c", c);

        point++;
    }

    fprintf(file, "\n");
}


void print_sorted_text(Text* onegin, FILE* file)
{
    assert(onegin);
    assert(file);


    for (int i = 0; i < (onegin->len_strings); i++)
        fprintf(file, "%s\n", (onegin->ind_arr)[i]);
    
    fprintf(file, "\n\n");
}


ProgramStatus read_file(char* file_name, Text* onegin)
{
    assert(file_name);
    assert(onegin);


    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return ERROR_OPENING_FILE;

    onegin->len_text = size_file(file);

    onegin->text = (char*) calloc(onegin->len_text + 1, sizeof(char));


    // Считывание файла (fread)
    int count_symbol = fread(onegin->text, sizeof(char), onegin->len_text, file);
    if (count_symbol != onegin->len_text) 
        return ERROR_READING;

    onegin->len_strings = file_strings_counter(file);

    // Заполнение массива указателей
    filling_points_arr(onegin);

    fclose(file);

    return OK;
}


ProgramStatus filling_points_arr(Text* onegin)
{
    assert(onegin);

    
    onegin->ind_arr = (char**) calloc(onegin->len_strings + 1, sizeof(char*));
    if ((onegin->ind_arr) == NULL) 
        return ERROR_MEMORY;

    (onegin->ind_arr)[0] = onegin->text;
    int last_ind_mas = 0;

    for (int i = 0; i < onegin->len_text; i++)
    {
        if ((onegin->text)[i] == '\n')
        {
            (onegin->ind_arr)[last_ind_mas + 1] = onegin->text + i + 1;
            last_ind_mas++;
            (onegin->text)[i] = '\0';  // Расставляю концы строк
        }
    }

    return OK;
}
