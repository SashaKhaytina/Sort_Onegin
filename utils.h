#ifndef UTILS_H
#define UTILS_H

#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)

// struct StringPoint
// {
//     char* begin_str;
//     char* end_str;
// };


int    str_len               (char* str1);               // Длина без '\0'
int    go_to_next_letter     (char* str1, int ind_now);  // Возвращает индекс близжайшей буквы
int    go_back_to_next_letter(char* str1, int ind_now);  // Возвращает индекс близжайшей c конца буквы
size_t size_file             (FILE* file);
int    file_strings_counter  (FILE* file);
int    strings_counter       (const char* text);


#endif