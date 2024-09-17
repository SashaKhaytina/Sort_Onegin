#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>


#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)


struct PointerArr
{
    char** ind_arr;  // массив указателей
    int len_strings;
};


struct Text // TODO: change name
{
    //char** ind_arr;  // массив указателей // TODO: i think text doesn't need these
    char* text;
    int len_text;
    //int len_strings;
};


void print_given_text(Text* onegin, FILE* file);    // НАЧАЛЬНЫЙ!!!!  (в файл)
void print_sorted_text(PointerArr* pointer_arr, FILE* file);   // Сортированный  (в тот же файл)
//void sort_str(Text* onegin);                        // запуск сортировки (пузырек)
//void swap_str(Text* onegin, int ind1, int ind2);    // переставление строк местами
void read_file(char* file_name, Text* onegin, PointerArr* pointer_arr);      // запись в двумерный массив
int str_len(char* str1);                           // Длина без '\0'
int go_to_next_letter(char* str1, int ind_now);    // Возвращает индекс близжайшей буквы

int compare_str(char* str1, char* str2);           // сравнение строк
                                                   // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2




void murderous_sort(void* mass, int len_strings, size_t elem_mass, 
                    int (*murderous_compare_str)(void* a1, void* a2));

int murderous_compare_str(void* str1, void* str2);
void murderous_swap_str(void* mass, int ind1, int ind2, size_t size);







int main()
{
    // чтение файла

    Text onegin = {};
    PointerArr pointer_arr = {};


    read_file("text.txt", &onegin, &pointer_arr);

    printf("%s\n\n", (pointer_arr.ind_arr)[7]);

    FILE* file = fopen("output.txt", "w"); // TODO: check these please
    if (file == NULL) printf("Не удалось открыть файл.");

    print_given_text(&onegin, file);

    //sort_str(&onegin);

    //char** mass = onegin.ind_arr;
    printf("%p - значение! первый с массиве указателей\n", pointer_arr.ind_arr[0]);
    murderous_sort(pointer_arr.ind_arr, pointer_arr.len_strings, sizeof(char*), murderous_compare_str);

    //onegin.ind_arr = mass;

    print_sorted_text(&pointer_arr, file);

    fclose(file);

    free(pointer_arr.ind_arr);
    free(onegin.text);
}







void print_given_text(Text* onegin, FILE* file) // TODO: fwrite
{
    assert(onegin);
    assert(file);

    char* point = NULL;
    point = onegin->text;

    for (int i = 0; i < onegin->len_text; i++)
    {
        char c = *point;

        if (c == '\0') fprintf(file, "\n");
        else           fprintf(file, "%c", c);

        point++;
    }

    // int write_count_symbol = fwrite((onegin->text), sizeof(char), (onegin->len_text), file);
    // if (write_count_symbol != (onegin->len_text)) fprintf(stderr, "Считал не то количество\n"); 


    fprintf(file, "\n");
}




void print_sorted_text(PointerArr* pointer_arr, FILE* file)
{
    assert(pointer_arr);
    assert(file);

    for (int i = 0; i < (pointer_arr->len_strings); i++)
    {
        fprintf(file, "%s\n", (pointer_arr->ind_arr)[i]);
    }
}




int str_len (char* str1) // TODO: wtf (strlen())
{
    assert(str1);

    int ind_elem = 0;

    while (str1[ind_elem] != '\0') ind_elem++;
    return ind_elem;
}




void read_file(char* file_name, Text* onegin, PointerArr* pointer_arr)
{
    assert(onegin);
    assert(file_name);

    FILE* file = fopen(file_name, "r");
    if ((file) == NULL) printf("Не удалось открыть файл");

    // Шаманство с курсором -> <-
    // Узнаем размер файла
    if (fseek(file, 0, SEEK_END) != 0) printf("Курсор не подвинулся\n");
    (onegin->len_text) = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0) printf("Курсор не вернулся\n");


    (onegin->text) = (char*) calloc((onegin->len_text) + 1, sizeof(char));


    // Считывание файла (fread)
    int count_symbol = fread((onegin->text), sizeof(char), (onegin->len_text), file);
    if (count_symbol != (onegin->len_text)) fprintf(stderr, "Считал не то количество\n"); 


    for (int i = 0; i < (onegin->len_text); i++)  // Но тут все равно этот цикл, чтоб считать кол-во строк
    {
        if ((onegin->text)[i] == '\n') ((pointer_arr->len_strings)++);
    }


    (pointer_arr->ind_arr) = (char**) calloc((pointer_arr->len_strings) + 1, sizeof(char*));

    (pointer_arr->ind_arr)[0] = (onegin->text);
    int last_ind_mas = 0;

    for (int i = 0; i < (onegin->len_text); i++)
    {
        if ((onegin->text)[i] == '\n')
        {
            (pointer_arr->ind_arr)[last_ind_mas + 1] = (onegin->text) + i + 1;
            last_ind_mas++;
            (onegin->text)[i] = '\0';  // Расставляю концы строк
        }
    }

    fclose(file);
}




// void sort_str(PointerArr* point_arr)  // Можно в 
// {
//     assert(point_arr);

//     //char* text = (onegin->text);

//     int count_while = 0;
//     int count_do_swap = 1;

//     while(count_do_swap > 0)
//     {
//         count_do_swap = 0;
//         for (int j = 0; j < (point_arr->len_strings) - 1 - count_while; j++)
//         {
//             if (compare_str((point_arr->ind_arr)[j], (point_arr->ind_arr)[j + 1]) > 0) 
//             {
//                 swap_str(point_arr, j, j + 1);
//                 count_do_swap++;
//             }
//         }

//         count_while++;
//     }
// }




//void murderous_sort(void* mass, int len_strings, size_t elem_mass, func)




int compare_str(char* str1, char* str2)  // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
{
    assert(str1);
    assert(str2);

    int ind_elem_1 = 0;
    int ind_elem_2 = 0;

    while ((str1[ind_elem_1] != '\0') && (str2[ind_elem_2] != '\0')) // TODO: for can do your code smaller and clearer than while
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

        if (el1 == '\0') // Значит и el2 = '/0' 
        {
            return 0;
        }

        // Значит простое совпадение букв
        ind_elem_1++;
        ind_elem_2++;
    }

    return (str1[ind_elem_1] - str2[ind_elem_2]);  // Тут кто-то '\0', поэтому без tolower()
}




// void swap_str(PointerArr* point_arr, int ind1, int ind2)
// {
//     assert(point_arr);

//     char* additional_ind = NULL;
//     additional_ind       = (point_arr->ind_arr)[ind2];
//     (point_arr->ind_arr)[ind2] = (point_arr->ind_arr)[ind1];
//     (point_arr->ind_arr)[ind1] = additional_ind;
// }




int go_to_next_letter(char* str1, int ind_now) // Возвращает индекс близжайшей буквы // TODO: isalpha
{
    assert(str1);

    for (;isalpha(str1[ind_now]) == 0; ind_now++){}

    return ind_now;
}
















void murderous_sort(void* mass, int len_strings, size_t elem_mass, 
                    int (*murderous_compare_str)(void* a1, void* a2))
{
    PRINTF_CYAN("Я в функции сортировки\n");
    printf("%p -значение! первый с массиве указателей\n", *(char**)mass);
    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0)
    {
        count_do_swap = 0;
        for (int j = 0; j < len_strings - 1 - count_while; j++)
        {



            // сравнение

            printf("%p - ячейка  mass \n",       (mass));
            printf("%p - ячейка  j-ого\n",       (mass + j * elem_mass));
            printf("%p - ячейка  (j + 1)-ого\n", (mass + (j + 1) * elem_mass));

            if (murderous_compare_str((mass + j * elem_mass), (mass + (j + 1) * elem_mass)) > 0) 
            {
                printf("ОНО ЗАШЛО (1-ое \"больше\" 2-ого)\n");   // ОНО НЕ РАЗУ НЕ ВЫВЕЛОСЬ
                //swap_str(onegin, j, j + 1);    //
                murderous_swap_str(mass, j, j + 1, elem_mass);
                count_do_swap++;

                printf("После swap\n");

                // Эти 2 строчки (вывод) работают только для массивов таких типов!
                printf("%s, %p - ячейка  j-ого\n",       *(char**)(mass + j * elem_mass), (mass + j * elem_mass));
                printf("%s, %p - ячейка  (j + 1)-ого\n", *(char**)(mass + (j + 1) * elem_mass), (mass + (j + 1) * elem_mass));
            }

            printf("Сравнение этой пары закончилось\n\n\n");






        }

        count_while++;
    }
    // Эта строчка (вывод) работает только для массивов таких типов!
    printf("%s - 1-ая строка отсортированного массива \n", *(char**)mass);
    PRINTF_CYAN("Я выхожу из функции сортировки\n");
}





int murderous_compare_str(void* str1, void* str2)
{
    char* real_str1 = *(char**)str1; // (char**)str1 - указатель на ячейку, в которой лежит указатель на char
                                     // * в начале - чтоб по первому указателю перейти (попасть в ячейку, в которой лежит указатель на char)
    char* real_str2 = *(char**)str2;


    PRINTF_CYAN("\n\n Я в функции сравнения\n\n");

    printf("%p - ячейка  j-ого\n",       str1);
    printf("%p - ячейка  (j + 1)-ого\n", str2);

    printf("%s, %p - строка j\n",           real_str1, str1);
    printf("%s, %p - строка (j + 1)-ого\n", real_str2, str2);

    PRINTF_CYAN("\n Я выхожу из функции сравнения\n\n");



    return compare_str(real_str1, real_str2);
}



void murderous_swap_str(void* mass, int ind1, int ind2, size_t size) // Эмммммм... Работает ли оно для ЛЮБЫХ (по типу) массивов?
{
    char* additional_ind = NULL;

    additional_ind                = *(char**)(mass + ind2 * size);
    *(char**)(mass + ind2 * size) = *(char**)(mass + ind1 * size);
    *(char**)(mass + ind1 * size) = additional_ind;
}