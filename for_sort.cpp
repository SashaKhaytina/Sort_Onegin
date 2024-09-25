// #include <stdio.h>
// #include <ctype.h>
// #include <malloc.h>
// #include <assert.h>

// #include "func_sort.h"
// #include "utils.h"
// #include "errors.h"


// // struct StringPoint
// // {
// //     char* begin_str;
// //     char* end_str;
// // };


// struct Text
// {
//     char* text;
//     int len_text;

//     StringPoint* strings_arr_p;  // массив указателей // TOD: rename to strings_arr
//     int len_strings;
// };


// void          print_given_text (Text* onegin, FILE* file);            // НАЧАЛЬНЫЙ!!!!  (в файл)
// void          print_sorted_text(Text* onegin, FILE* file);            // Сортированный  (в тот же файл)

// ProgramStatus get_text         (const char* file_name, Text* onegin); // запись в двумерный массив
// ProgramStatus fill_strings_arr (Text* onegin);                        // Заполнение массива указателей



// int main()
// {
//     ProgramStatus status = OK;

//     Text onegin = {};

//     status = get_text("text.txt", &onegin);
//     if (status != OK)
//     {
//         print_errors_code(status);
//         return 0;
//     }


//     // ---- вывод -----
//     //printf("%s\n\n", (onegin.strings_arr_p)[7]); 
//     // ---- конец -----


//     FILE* file = fopen("output.txt", "w");
//     if (file == NULL)
//     {
//         status = ERROR_OPENING_FILE;
//         print_errors_code(status);
//         return 0;
//     }


//     // ---- вывод -----
//     // Тут был вывод начального
//     //printf("%p - значение! первый с массиве указателей\n", onegin.strings_arr_p[0]);
//     // ---- конец -----


//     for (size_t i = 0; i < sizeof(onegin.len_strings); ++i) {
//         printf("%s\n", onegin.strings_arr_p[i].begin_str);
//     }
//     // Сортировка с начала строки
//     murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_first_elem);
//     print_sorted_text(&onegin, file);

//     // Сортировка с конца строки
//     murderous_sort(onegin.strings_arr_p, onegin.len_strings, sizeof(StringPoint), murderous_compare_str_end_elem);
//     print_sorted_text(&onegin, file);

//     print_given_text(&onegin, file); // TOD: print given text after printing sorted text

//     fclose(file);

//     free(onegin.strings_arr_p);
//     free(onegin.text);

//     print_errors_code(status);
// }



// void print_given_text(Text* onegin, FILE* file)
// {
//     assert(onegin);
//     assert(file);

//     char* point = onegin->text;

//     for (int i = 0; i < (onegin->len_strings); i++)
//         point += fprintf(file, "%s\n", point);

//     fprintf(file, "\n");
// }


// void print_sorted_text(Text* onegin, FILE* file)
// {
//     assert(onegin);
//     assert(file);


//     for (int i = 0; i < (onegin->len_strings); i++)
//         fprintf(file, "%s\n", ((onegin->strings_arr_p) + i)->begin_str);
    
//     fprintf(file, "\n\n");
// }


// ProgramStatus get_text(const char* file_name, Text* onegin) // TOD: rename to get_text
// {
//     assert(file_name);
//     assert(onegin);


//     FILE* file = fopen(file_name, "r");
//     if (file == NULL)
//         return ERROR_OPENING_FILE;

//     onegin->len_text = size_file(file);

//     onegin->text = (char*) calloc((size_t)(onegin->len_text + 1), sizeof(char));


//     // Считывание файла (fread)
//     int count_symbol = (int) fread(onegin->text, sizeof(char), (size_t)(onegin->len_text), file); // TODO: conversion to int is weird imho
//     if (count_symbol != onegin->len_text) 
//         return ERROR_READING;

//     //onegin->len_strings = file_strings_counter(file); // TOD: read from buffer, not from file
//     onegin->len_strings = strings_counter(onegin->text);

//     printf("%d\n", onegin->len_strings);

//     // Заполнение массива указателей
//     fill_strings_arr(onegin);

//     fclose(file);

//     return OK;
// }


// ProgramStatus fill_strings_arr(Text* onegin) // TOD: rename
// {
//     assert(onegin);

    
//     onegin->strings_arr_p = (StringPoint*) calloc((size_t)(onegin->len_strings + 1), sizeof(StringPoint));
//     if (onegin->strings_arr_p == NULL) 
//         return ERROR_MEMORY;

//     onegin->strings_arr_p->begin_str = onegin->text;  
//     int ind_fill_now = 0; // TOD: rename

//     for (int i = 0; i < onegin->len_text; i++)
//     {
//         if ((onegin->text)[i] == '\n')
//         {
//             onegin->strings_arr_p[ind_fill_now].end_str = onegin->text + i;
//             ind_fill_now++;
//             onegin->strings_arr_p[ind_fill_now].begin_str = onegin->text + i + 1;

//             (onegin->text)[i] = '\0';  // Расставляем концы строк
//         }
//     }

//     return OK;
// }
