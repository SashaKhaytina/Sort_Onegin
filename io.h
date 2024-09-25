#ifndef IO_H
#define IO_H

#include "main.h"
#include "errors.h"


void          print_given_text (Text* onegin, FILE* file);            // НАЧАЛЬНЫЙ!!!!  (в файл)
void          print_sorted_text(Text* onegin, FILE* file);            // Сортированный  (в тот же файл)

ProgramStatus get_text         (const char* file_name, Text* onegin); // запись в двумерный массив
ProgramStatus fill_strings_arr (Text* onegin);                        // Заполнение массива указателей


#endif