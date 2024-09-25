#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

#include "func_sort.h"
#include "utils.h"



static void murderous_swap_str(void* mass, int ind1, int ind2, size_t size);


static void murderous_swap_str(void* mass, int ind1, int ind2, size_t size) // Тут меняется массив указателей!
{
    assert(mass);

    char* point1 = (char*) mass + ((size_t) ind1) * size; 
    char* point2 = (char*) mass + ((size_t) ind2) * size;

    for (size_t i = 0; i < size; i++)
    {
        char something = *point1;
        *point1 = *point2;
        *point2 = something;

        point1++;
        point2++;
    }
}


void murderous_sort(void* mass, int len_strings, size_t elem_mass, 
                    int (*murderous_compare_str)(void* a1, void* a2))
{
    assert(mass);
    assert(murderous_compare_str); 


    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0) 
    {
        count_do_swap = 0;
        for (int j = 0; j < len_strings - 1 - count_while; j++)
        {
            if (murderous_compare_str(((char*) mass + ((size_t)j) * elem_mass), ((char*)mass + ((size_t)(j + 1)) * elem_mass)) > 0) 
            {
                murderous_swap_str(mass, j, j + 1, elem_mass);
                count_do_swap++;
            }
        }

        count_while++;
    }
}


int murderous_compare_str_first_elem(void* str1, void* str2)
{
    assert(str1);
    assert(str2);

    char* real_str1 = ((StringPoint*)str1)->begin_str; // (char**)str1 - указатель на ячейку, в которой лежит указатель на char
                                                       // * в начале - чтоб по первому указателю перейти (попасть в ячейку, в которой лежит указатель на char)
    char* real_str2 = ((StringPoint*)str2)->begin_str;


    int ind_elem_1 = 0;
    int ind_elem_2 = 0;

    while ((real_str1[ind_elem_1] != '\0') && (real_str2[ind_elem_2] != '\0')) // TODO: for can do your code smaller and clearer than while
    {
        // Смещение счетчика до буквы в str1 и str2
        ind_elem_1 = go_to_next_letter(real_str1, ind_elem_1);
        ind_elem_2 = go_to_next_letter(real_str2, ind_elem_2);

        int el1 = tolower(real_str1[ind_elem_1]);
        int el2 = tolower(real_str2[ind_elem_2]);

        int comp = el1 - el2;
        if (comp != 0)
        {
            return comp;
        }

        if (el1 == '\0') // Значит и el2 = '/0' 
        {
            return 0;
        }

        // Значит простое совпадение букв
        ind_elem_1++;
        ind_elem_2++;
    }

    return (real_str1[ind_elem_1] - real_str2[ind_elem_2]);  // Тут кто-то '\0', поэтому без tolower()
}


int murderous_compare_str_end_elem(void* str1, void* str2)
{
    assert(str1);
    assert(str2);

    char* real_str1     = ((StringPoint*)str1)->begin_str;
    char* real_end_str1 = ((StringPoint*)str1)->end_str;

    char* real_str2     = ((StringPoint*)str2)->begin_str;
    char* real_end_str2 = ((StringPoint*)str2)->end_str;


    int ind_elem_1 = (int) (real_end_str1 - real_str1) - 1;
    int ind_elem_2 = (int) (real_end_str2 - real_str2) - 1;


    while ((ind_elem_1 != 0) && (ind_elem_2 != 0)) // TODO: for can do your code smaller and clearer than while
    {
        // Смещение счетчика до буквы в str1 и str2
        ind_elem_1 = go_back_to_next_letter(real_str1, ind_elem_1);
        ind_elem_2 = go_back_to_next_letter(real_str2, ind_elem_2);

        int el1 = tolower(real_str1[ind_elem_1]);
        int el2 = tolower(real_str2[ind_elem_2]);

        int comp = el1 - el2;
        if (comp != 0)
        {
            return comp;
        }

        // if (el1 == '\0') // Значит и el2 = '/0' 
        // {
        //     return 0;
        // }

        // Значит простое совпадение букв
        ind_elem_1--;
        ind_elem_2--;
    }

    return (real_str1[ind_elem_1] - real_str2[ind_elem_2]);
}

