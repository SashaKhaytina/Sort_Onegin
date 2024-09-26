#ifndef FUNCSORT_H
#define FUNCSORT_H

#include <stdio.h>


void murderous_sort                   (void* mass, int len_strings, size_t elem_mass,
                                       int (*murderous_compare_str)(void* a1, void* a2)); // Указатель на функцию
int  murderous_compare_str_first_elem (void* str1, void* str2);                           // Сравнение двух строк с начала
int  murderous_compare_str_end_elem   (void* str1, void* str2);                           // Сравнение двух строк с конца


#endif