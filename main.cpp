#include <stdio.h>
#include <ctype.h>


#define MAX(a, b) \
    a > b ? a : b

int const WIDTH = 100;
int const HEIGHT = 8;

void sort_str(char* text); // запуск сортировки (пузырек)

int compare_str(char* str1, char* str2); // сравнение строк
// Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2

void swap_str(char* str1, char* str2);    // переставление строк местами
void read_file(FILE **file, char* text);  // запись в двумерный массив
int str_len(char* str1);  // Длина без '\0'

void go_to_next_letter(char* str1, int* ind_now);


int main()
{
    char text[HEIGHT][WIDTH] = {};

    // чтение файла

    FILE* file = NULL;
    file = fopen("text.txt", "r");
    if ((file) == NULL) printf("Не получилось открыть");

    read_file(&file, text[0]);

    for (int i = 0; i < HEIGHT; i++)
    {
        puts(text[i]); // выводит, заменяя "\0" на "\n"
    }

    sort_str(*text);
    printf("\n\n\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        puts(text[i]); // выводит, заменяя "\0" на "\n"
    }
}


int str_len (char* str1)
{
    int ind_elem = 0;
    while (str1[ind_elem] != '\0') ind_elem++;
    return ind_elem;
}


void read_file(FILE **file, char* text) // char** указатель на начало строки
{
    for (int i = 0; i < HEIGHT; i++)
    {
        fgets(text + WIDTH * i, WIDTH, *file);
    }
}


void sort_str(char* text)
{
    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0)
    {
        count_do_swap = 0;
        for (int j = 0; j < HEIGHT - 1 - count_while; j++)
        {
            if (compare_str(text + WIDTH * j, text + WIDTH * (j+1)) > 0)
            {
                swap_str(text + WIDTH * j, text + WIDTH * (j+1));
                count_do_swap++;
            }
        }

        count_while++;
    }
}


int compare_str(char* str1, char* str2)  // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
{

//     Без пропуска небуквенных символов
//     int ind_elem = 0;
//
//     while ((str1[ind_elem] != '\0') && (str2[ind_elem] != '\0'))
//     {
//         // printf("%c%c, ", str1[ind_elem], str2[ind_elem]);
//
//         int el1 = tolower(str1[ind_elem]);
//         int el2 = tolower(str2[ind_elem]);
//
//         int comp = el1 - el2;
//         if (comp != 0)  return comp;
//         else            ind_elem++;
//     }
//
//     return (str1[ind_elem] - str2[ind_elem]);  // Тут кто-то '\0', поэтому без tolower()


    int ind_elem_1 = 0;
    int ind_elem_2 = 0;

    while ((str1[ind_elem_1] != '\0') && (str2[ind_elem_2] != '\0'))
    {
        // printf("%c%c, ", str1[ind_elem], str2[ind_elem]);

        int el1 = tolower(str1[ind_elem_1]);
        int el2 = tolower(str2[ind_elem_2]);

        //Смещение счетчика до буквы в str1
        while ((!islower(el1)) && (el1 != '\0'))
        {
            ind_elem_1++;
            el1 = tolower(str1[ind_elem_1]);
        }

        //go_to_next_letter(str1, &ind_elem_1);

        //Смещение счетчика до буквы в str2
        while ((!islower(el2)) && (el2 != '\0'))
        {
            ind_elem_2++;
            el2 = tolower(str2[ind_elem_2]);
        }

        //go_to_next_letter(str2, &ind_elem_2);


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
        symbol = str1[ind_elem];
        str1[ind_elem] = str2[ind_elem];
        str2[ind_elem] = symbol;

        ind_elem++;
    }
}


void go_to_next_letter(char* str1, int* ind_now)
{
    int el1 = tolower(str1[*ind_now]);

    while ((!islower(el1)) && (el1 != '\0'))
    {
        *ind_now++;
        el1 = tolower(str1[*ind_now]);
    }
}
