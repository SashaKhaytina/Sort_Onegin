#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>

#include "func_sort.h"
#include "utils.h"
#include "errors.h"


// struct StringPoint
// {
//     char* begin_str;
//     char* end_str;
// };


struct Text
{
    char* text;
    int len_text;

    StringPoint* ind_arr;  // массив указателей // TODO: rename to strings_arr
    int len_strings;
};


void print_given_text  (Text* onegin, FILE* file);      // НАЧАЛЬНЫЙ!!!!  (в файл)
void print_sorted_text (Text* onegin, FILE* file);      // Сортированный  (в тот же файл)

ProgramStatus read_file         (const char* file_name, Text* onegin); // запись в двумерный массив
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
    //printf("%s\n\n", (onegin.ind_arr)[7]); 
    // ---- конец -----


    FILE* file = fopen("output.txt", "w");
    if (file == NULL)
    {
        status = ERROR_OPENING_FILE;
        print_errors_code(status);
        return 0;
    }


    // ---- вывод -----
    print_given_text(&onegin, file); // TODO: print given text after printing sorted text
    //printf("%p - значение! первый с массиве указателей\n", onegin.ind_arr[0]);
    // ---- конец -----


    for (size_t i = 0; i < sizeof(onegin.len_strings); ++i) {
        printf("%s\n", onegin.ind_arr[i].begin_str);
    }
    // Сортировка с начала строки
    murderous_sort(onegin.ind_arr, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_first_elem);
    print_sorted_text(&onegin, file);

    // Сортировка с конца строки
    murderous_sort(onegin.ind_arr, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_end_elem);
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

    char* point = onegin->text;

    for (int i = 0; i < onegin->len_text; i++) // TODO: fprintf("%s")
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
        fprintf(file, "%s\n", ((onegin->ind_arr) + i)->begin_str);
    
    fprintf(file, "\n\n");
}


ProgramStatus read_file(const char* file_name, Text* onegin) // TODO: rename to get_text
{
    assert(file_name);
    assert(onegin);


    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return ERROR_OPENING_FILE;

    onegin->len_text = size_file(file);

    onegin->text = (char*) calloc((size_t)(onegin->len_text + 1), sizeof(char));


    // Считывание файла (fread)
    int count_symbol = (int)fread(onegin->text, sizeof(char), (size_t)(onegin->len_text), file); // TODO: conversion to int is weird imho
    if (count_symbol != onegin->len_text) 
        return ERROR_READING;

    onegin->len_strings = file_strings_counter(file); // TODO: read from buffer, not from file

    printf("%d\n", onegin->len_strings);

    // Заполнение массива указателей
    filling_points_arr(onegin);

    fclose(file);

    return OK;
}


ProgramStatus filling_points_arr(Text* onegin) // TODO: rename
{
    assert(onegin);

    
    onegin->ind_arr = (StringPoint*) calloc((size_t)(onegin->len_strings + 1), sizeof(StringPoint)); // TODO звезды....
    if (onegin->ind_arr == NULL) 
        return ERROR_MEMORY;

    onegin->ind_arr->begin_str = onegin->text;  
    int last_ind_mas = 0; // TODO: rename

    for (int i = 0; i < onegin->len_text; i++)
    {
        if ((onegin->text)[i] == '\n')
        {
            onegin->ind_arr[last_ind_mas].end_str = onegin->text + i;
            last_ind_mas++;
            onegin->ind_arr[last_ind_mas].begin_str = onegin->text + i + 1;
            //last_ind_mas++;
            // printf("%p - НАЧАЛО СТРОКИ!!!!!!!!!!!!\n%s - СТРОКА\n\n\n", onegin->text + i + 1, onegin->text + i + 1);
            (onegin->text)[i] = '\0';  // Расставляю концы строк
        }
    }

    return OK;
}
