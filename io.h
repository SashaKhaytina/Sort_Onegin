#ifndef IO_H
#define IO_H

#include "working_with_text.h"


void print_text_by_buffer (Text* onegin, FILE* file); // Начальный текст     (в файл)
void print_text_by_strings(Text* onegin, FILE* file); // Сортированный текст (в файл)


#endif