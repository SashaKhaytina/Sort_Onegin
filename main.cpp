#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>


#define MAX(a, b) \
    a > b ? a : b

// Функция - чищу файл (???) или открывать и закрывать в main
// Или весь вывод засунуть в одну функцию, и в ней все выводить (тогда приколы с разными сортировками (порядок действий))


struct Onegin
{
    char** ind_arr;  // массив указателей
    char* text;
    int len_text;
    int len_strings;
};


void print_given_text(Onegin* Box, FILE* file);    // НАЧАЛЬНЫЙ!!!!  (в файл)
void print_sorted_text(Onegin* Box, FILE* file);   // Сортированный  (в тот же файл)
void sort_str(Onegin* Box);                        // запуск сортировки (пузырек)
void swap_str(Onegin* Box, int ind1, int ind2);    // переставление строк местами
void read_file(char* file_name, Onegin* Box);      // запись в двумерный массив
int str_len(char* str1);                           // Длина без '\0'
int go_to_next_letter(char* str1, int ind_now);    // Возвращает индекс близжайшей буквы

int compare_str(char* str1, char* str2);           // сравнение строк
                                                   // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2

int main()
{
    // чтение файла

    Onegin Box = {};

    read_file("text.txt", &Box);

//     printf("\n");
//
//     printf("%d - колво строк\n", Box.len_strings);
//     printf("%d - колво символов\n", Box.len_text);
//
//     printf("\n");
//
//     printf("%s\n", Box.text);
//
//     printf("\n");
//
    printf("%s\n\n", (Box.ind_arr)[7]);

    FILE* file = fopen("output.txt", "w");

    print_given_text(&Box, file);

    sort_str(&Box);

    print_sorted_text(&Box, file);

    fclose(file);
}


void print_given_text(Onegin* Box, FILE* file)
{
    assert(Box);
    assert(file);

    //FILE* file = fopen("output.txt", "w");

    char* point = NULL;
    point = Box->text;

    for (int i = 0; i < Box->len_text; i++)
    {
        char c = *point;

        if (c == '\0') fprintf(file, "\n");
        else           fprintf(file, "%c", c);

        point++;
    }

    fprintf(file, "\n");

    // fclose(file);
}

void print_sorted_text(Onegin* Box, FILE* file)
{
    assert(Box);
    assert(file);

    // FILE* file = fopen("output.txt", "w");

    for (int i = 0; i < (Box->len_strings); i++)
    {
        fprintf(file, "%s\n", (Box->ind_arr)[i]);
    }
    // fclose(file);
}


int str_len (char* str1)
{
    assert(str1);

    int ind_elem = 0;

    while (str1[ind_elem] != '\0') ind_elem++;
    return ind_elem;
}


void read_file(char* file_name, Onegin* Box)
{
    assert(Box);
    assert(file_name);

    FILE* file = NULL;
    file = fopen(file_name, "r");
    if ((file) == NULL) printf("Не получилось открыть");

    // Шаманство с курсором -> <-
    // Узнаем размер файла
    if (fseek(file, 0, SEEK_END) != 0) printf("Курсор не подвинулся\n");
    (Box->len_text) = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0) printf("Курсор не вернулся\n");


    (Box->text) = (char*) calloc((Box->len_text) + 1, sizeof(char));

    for (int i = 0; i < (Box->len_text); i++)
    {
        int c = getc(file);
        (Box->text)[i] = c;
        // printf("%c", (Box->text)[i]);

        if (c == '\n') ((Box->len_strings)++);
    }


    (Box->ind_arr) = (char**) calloc((Box->len_strings) + 1, sizeof(char*));

    (Box->ind_arr)[0] = (Box->text);
    int last_ind_mas = 0;

    for (int i = 0; i < (Box->len_text); i++)
    {
        //printf("%c - %d\n", (Box->text)[i], (Box->text)[i]);
        if ((Box->text)[i] == '\n')
        {
            (Box->ind_arr)[last_ind_mas + 1] = (Box->text) + i + 1;
            //printf("", )
            last_ind_mas++;
            (Box->text)[i] = '\0';  // Расставляю концы строк
        }
        // printf("%c - %d  ", (Box->text)[i], (Box->text)[i]);
    }

    fclose(file);
}


void sort_str(Onegin* Box)
{
    assert(Box);

    char* text = (Box->text);

    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0)
    {
        count_do_swap = 0;
        for (int j = 0; j < (Box->len_strings) - 1 - count_while; j++)
        {
            if (compare_str((Box->ind_arr)[j], (Box->ind_arr)[j + 1]) > 0)
            {
                swap_str(Box, j, j + 1);
                count_do_swap++;
            }
        }

        count_while++;
    }
}


int compare_str(char* str1, char* str2)  // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
{
    assert(str1);
    assert(str2);

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


void swap_str(Onegin* Box, int ind1, int ind2)
{
    assert(Box);

    char* additional_ind = NULL;
    additional_ind       = (Box->ind_arr)[ind2];
    (Box->ind_arr)[ind2] = (Box->ind_arr)[ind1];
    (Box->ind_arr)[ind1] = additional_ind;
}


int go_to_next_letter(char* str1, int ind_now) // Возвращает индекс близжайшей буквы
{
    assert(str1);

    int el = tolower(str1[ind_now]);

    while (((islower(el) == 0) && (el != '\0')))
    {
        (ind_now)++;
        el = tolower(str1[ind_now]);
    }

    return ind_now;
}
