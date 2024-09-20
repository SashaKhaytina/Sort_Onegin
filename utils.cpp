#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "utils.h"


int go_to_next_letter(char* str1, int ind_now) // Возвращает индекс близжайшей буквы
{
    assert(str1);

    for (;isalpha(str1[ind_now]) == 0; ind_now++){}

    return ind_now;
}


int go_back_to_next_letter(char* str1, int ind_now) // Возвращает индекс близжайшей буквы
{
    assert(str1);

    for (;isalpha(str1[ind_now]) == 0; ind_now--){}

    return ind_now;
}


int size_file(FILE* file)
{
    int size = 0;

    if (fseek(file, 0, SEEK_END) != 0) printf("Курсор не подвинулся\n"); // TODO: delete this checking
    size = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0) printf("Курсор не вернулся\n");

    return size;
}


int file_strings_counter(FILE* file)
{
    int counter_str = 0;

    int size_f = size_file(file);

    for (int i = 0; i < size_f; i++)
    {
        if (getc(file) == '\n')
        {
            counter_str++;
        }
    }

    return counter_str;
    // for (int i = 0; i < *len_text; i++)
    // {
    //     if ((*text)[i] == '\n') 
    //         (*len_strings)++;
    // }
}


// int str_len (char* str1) // TODO: wtf (strlen())
// {
//     assert(str1);

//     int ind_elem = 0;

//     while (str1[ind_elem] != '\0') ind_elem++;
//     return ind_elem;
// }
