#include <stdio.h>
#include <ctype.h>
#include <malloc.h>


#define MAX(a, b) \
    a > b ? a : b

// Массив "индексов" строк
// Массив указателей на строки

//int const WIDTH = 100;
int const HEIGHT = 8;

void sort_str(char*** text, int a);                      // запуск сортировки (пузырек)
void swap_str(char* str1, char* str2);          // переставление строк местами
char** read_file(FILE **file, int* len_strs);      // запись в двумерный массив
int str_len(char* str1);                        // Длина без '\0'
int go_to_next_letter(char* str1, int ind_now); // Возвращает индекс близжайшей буквы

int compare_str(char* str1, char* str2);        // сравнение строк
                                                // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2

int main()
{
    //char* text[HEIGHT] = {}; // или можно через calloc (char** text = ...)

    //char** index_strs = (char**) calloc(1, sizeof(char*));
    // чтение файла

    FILE* file = NULL;
    file = fopen("text.txt", "r");
    if ((file) == NULL) printf("Не получилось открыть");


    int len_strs = 0;
    char** index_strs = read_file(&file, &len_strs);

    for (int i = 0; i < len_strs; i++)
    {
        puts(index_strs[i]); // выводит, заменяя "\0" на "\n"
    }

    sort_str(&index_strs, len_strs);
    printf("\n\n\n");

    for (int i = 0; i < len_strs; i++)
    {
        puts(index_strs[i]); // выводит, заменяя "\0" на "\n"
    }
}


int str_len(char* str1)
{
    int ind_elem = 0;

    while (str1[ind_elem] != '\0') ind_elem++;
    return ind_elem;
}


char** read_file(FILE **file, int* len_strs) // Хочу вернуть массив указателей
{
    char* stroka = (char*) calloc(100, sizeof(char));

    // Гарантирую, что одна строка есть (или тут можно проверку поставить, а вернуть что-то непонятное...)
    fgets(stroka, 100, *file);
    stroka = (char*) realloc(stroka, str_len(stroka) + 1, sizeof(char));

    // указатель на 1 строку в массив указателей
    char** index_strs = calloc(1, sizeof(char*));
    index_strs[0] = stroka;
    *len_strs = 1;

    while (fgets(stroka, 100, *file) != NULL)
    {
        index_strs = (char**) realloc(index_strs, len_strs + 1, sizeof(char*));
        len_strs++;

        stroka = (char*) realloc(stroka, str_len(stroka) + 1, sizeof(char));

        index_strs[len_strs - 1] = stroka;
    }

    return index_strs;
}


void sort_str(char*** index_strs, int len_strs)
{
    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0)
    {
        count_do_swap = 0;
        for (int j = 0; j < len_strs - 1 - count_while; j++)
        {
            char* str1 = (*index_strs)[j];
            char* str2 = (*index_strs)[j+1];

            if (compare_str(str1, str2) > 0) // * или ** ???
            {
                swap_str(str1, str2);
                count_do_swap++;
            }
        }

        count_while++;
    }
}


int compare_str(char* str1, char* str2)  // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
{
    int ind_elem_1 = 0;
    int ind_elem_2 = 0;

    while ((str1[ind_elem_1] != '\0') && (str2[ind_elem_2] != '\0'))
    {
        // Смещение счетчика до буквы в str1 и str2
        ind_elem_1 = go_to_next_letter(str1, ind_elem_1);
        ind_elem_2 = go_to_next_letter(str2, ind_elem_2);

        int el1 = tolower(str1[ind_elem_1]);
        int el2 = tolower(str2[ind_elem_2]);

        int comp = el1 - el2;
        if (comp != 0)
        {
            return comp;
        }
        else
        {
            if (el1 = '\0') // Значит и el2 = '/0'
            {
                return 0;
            }
            else            // Значит простое совпадение букв
            {
                ind_elem_1++;
                ind_elem_2++;
            }
        }
    }

    return (str1[ind_elem_1] - str2[ind_elem_2]);  // Тут кто-то '\0', поэтому без tolower()
}


void swap_str(char* str1, char* str2)
{
    int ind_elem = 0;
    char symbol = '0';

    int len_str1 = str_len(str1);
    int len_str2 = str_len(str2);

    while (ind_elem < (MAX(len_str1, len_str2)))
    {
        symbol         = str1[ind_elem];
        str1[ind_elem] = str2[ind_elem];
        str2[ind_elem] = symbol;

        ind_elem++;
    }
}


int go_to_next_letter(char* str1, int ind_now) // Возвращает индекс близжайшей буквы
{
    int el = tolower(str1[ind_now]);

    while (((islower(el) == 0) && (el != '\0')))
    {
        (ind_now)++;
        el = tolower(str1[ind_now]);
    }

    return ind_now;
}
