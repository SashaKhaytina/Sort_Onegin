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


struct Text
{
    char* text;
    int len_text;
};


void print_given_text     (Text* onegin, FILE* file);                               // НАЧАЛЬНЫЙ!!!!  (в файл)
void print_sorted_text    (PointerArr* pointer_arr, FILE* file);                    // Сортированный  (в тот же файл)
void read_file            (char* file_name, Text* onegin, PointerArr* pointer_arr); // запись в двумерный массив
void filling_points_arr   (Text* onegin, PointerArr* pointer_arr);                  // Заполнение массива указателей
int  str_len              (char* str1);                                             // Длина без '\0'
int  go_to_next_letter    (char* str1, int ind_now);                                // Возвращает индекс близжайшей буквы

int  compare_str          (char* str1, char* str2);                                 // сравнение строк
                                                                                    // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
void murderous_sort       (void* mass, int len_strings, size_t elem_mass, 
                           int (*murderous_compare_str)(void* a1, void* a2));       // Указатель на функцию (а если * пеерставить, то сломается?)
int  murderous_compare_str_first_elem (void* str1, void* str2);                                 // Сравнение двух !строк!
void murderous_swap_str   (void* mass, int ind1, int ind2, size_t size);            // swap (строк?)
//int  compare_str_end      (char* str1, char* str2);
//int  murderous_compare_str_end_elem (void* str1, void* str2);



int main()
{
    Text onegin = {};
    PointerArr pointer_arr = {};

    read_file("text.txt", &onegin, &pointer_arr);


    // ---- вывод -----
    printf("%s\n\n", (pointer_arr.ind_arr)[7]); 
    // ---- конец -----


    FILE* file = fopen("output.txt", "w");
    if (file == NULL) printf("Не удалось открыть файл.");


    // ---- вывод -----
    print_given_text(&onegin, file);
    printf("%p - значение! первый с массиве указателей\n", pointer_arr.ind_arr[0]);
    // ---- конец -----


    //murderous_sort(pointer_arr.ind_arr, pointer_arr.len_strings, sizeof(char*), murderous_compare_str);
    murderous_sort(pointer_arr.ind_arr, pointer_arr.len_strings, sizeof(char*), murderous_compare_str_first_elem);

    print_sorted_text(&pointer_arr, file);

    fclose(file);

    free(pointer_arr.ind_arr);
    free(onegin.text);
}



void print_given_text(Text* onegin, FILE* file)
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
    assert(file_name);
    assert(onegin);
    assert(pointer_arr);


    int* len_text    = &(onegin->len_text);
    char** text      = &(onegin->text);
    int* len_strings = &(pointer_arr->len_strings);
    char*** ind_arr  = &(pointer_arr->ind_arr);


    FILE* file = fopen(file_name, "r");
    if ((file) == NULL) printf("Не удалось открыть файл");

    // Узнаем размер файла
    if (fseek(file, 0, SEEK_END) != 0) printf("Курсор не подвинулся\n");
    *len_text = ftell(file);
    if (fseek(file, 0, SEEK_SET) != 0) printf("Курсор не вернулся\n");


    *text = (char*) calloc(*len_text + 1, sizeof(char));


    // Считывание файла (fread)
    int count_symbol = fread(*text, sizeof(char), *len_text, file);
    if (count_symbol != *len_text) fprintf(stderr, "Считал не то количество\n"); 


    // Но тут все равно этот цикл, чтоб считать кол-во строк
    for (int i = 0; i < *len_text; i++)
    {
        if ((*text)[i] == '\n') ((*len_strings)++);
    }

    // Заполнение массива указателей  (Хотелось бы в другую функцию)
    filling_points_arr(onegin, pointer_arr);

    fclose(file);
}


void filling_points_arr(Text* onegin, PointerArr* pointer_arr)
{
    assert(onegin);
    assert(pointer_arr);

    int* len_text    = &(onegin->len_text);
    char** text      = &(onegin->text);
    int* len_strings = &(pointer_arr->len_strings);
    char*** ind_arr  = &(pointer_arr->ind_arr);

    
    *ind_arr = (char**) calloc((*len_strings) + 1, sizeof(char*));

    (*ind_arr)[0] = *text;
    int last_ind_mas = 0;

    for (int i = 0; i < *len_text; i++)
    {
        if ((*text)[i] == '\n')
        {
            (*ind_arr)[last_ind_mas + 1] = (*text) + i + 1;
            last_ind_mas++;
            (*text)[i] = '\0';  // Расставляю концы строк
        }
    }
}


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









void murderous_sort(void* mass, int len_strings, size_t elem_mass, 
                    int (*murderous_compare_str)(void* a1, void* a2))
{
    assert(mass);
    assert(murderous_compare_str); // assert на функцию???


    // ---- вывод -----
    PRINTF_CYAN("Я в функции сортировки\n");
    printf("%p -значение! первый с массиве указателей\n", *(char**)mass);
    // ---- конец -----


    int count_while = 0;
    int count_do_swap = 1;

    while(count_do_swap > 0)
    {
        count_do_swap = 0;
        for (int j = 0; j < len_strings - 1 - count_while; j++)
        {
            // сравнение

            // ---- вывод -----
            printf("%p - ячейка  mass \n",       (mass));
            printf("%p - ячейка  j-ого\n",       (mass + j * elem_mass));
            printf("%p - ячейка  (j + 1)-ого\n", (mass + (j + 1) * elem_mass));
            // ---- конец -----


            if (murderous_compare_str_first_elem((mass + j * elem_mass), (mass + (j + 1) * elem_mass)) > 0) 
            {
                // ---- вывод -----
                printf("ОНО ЗАШЛО (1-ое \"больше\" 2-ого)\n");
                // ---- конец -----


                murderous_swap_str(mass, j, j + 1, elem_mass);
                count_do_swap++;


                // ---- вывод -----
                printf("После swap\n");
                // ---- конец -----


                // Эти 2 строчки (вывод) работают только для массивов таких типов!
                printf("%s, %p - ячейка  j-ого\n",       *(char**)(mass + j * elem_mass), (mass + j * elem_mass));
                printf("%s, %p - ячейка  (j + 1)-ого\n", *(char**)(mass + (j + 1) * elem_mass), (mass + (j + 1) * elem_mass));
            }


            printf("Сравнение этой пары закончилось\n\n\n");


        }

        count_while++;
    }

    // Эта строчка (вывод) работает только для массивов таких типов!
    
    // ---- вывод -----
    printf("%s - 1-ая строка отсортированного массива \n", *(char**)mass);
    PRINTF_CYAN("Я выхожу из функции сортировки\n");
    // ---- конец -----
}





int murderous_compare_str_first_elem(void* str1, void* str2)
{
    assert(str1);
    assert(str2);

    char* real_str1 = *(char**)str1; // (char**)str1 - указатель на ячейку, в которой лежит указатель на char
                                     // * в начале - чтоб по первому указателю перейти (попасть в ячейку, в которой лежит указатель на char)
    char* real_str2 = *(char**)str2;


    // ---- вывод -----
    PRINTF_CYAN("\n\n Я в функции сравнения\n\n");

    printf("%p - ячейка  j-ого\n",       str1);
    printf("%p - ячейка  (j + 1)-ого\n", str2);

    printf("%s, %p - строка j\n",           real_str1, str1);
    printf("%s, %p - строка (j + 1)-ого\n", real_str2, str2);

    PRINTF_CYAN("\n Я выхожу из функции сравнения\n\n");
    // ---- конец -----


    return compare_str(real_str1, real_str2);
}


// int murderous_compare_str_end_elem(void* str1, void* str2)
// {
//     assert(str1);
//     assert(str2);

//     char* real_str1 = *(char**)str1; // (char**)str1 - указатель на ячейку, в которой лежит указатель на char
//                                      // * в начале - чтоб по первому указателю перейти (попасть в ячейку, в которой лежит указатель на char)
//     char* real_str2 = *(char**)str2;


//     // ---- вывод -----
//     PRINTF_CYAN("\n\n Я в функции сравнения\n\n");

//     printf("%p - ячейка  j-ого\n",       str1);
//     printf("%p - ячейка  (j + 1)-ого\n", str2);

//     printf("%s, %p - строка j\n",           real_str1, str1);
//     printf("%s, %p - строка (j + 1)-ого\n", real_str2, str2);

//     PRINTF_CYAN("\n Я выхожу из функции сравнения\n\n");
//     // ---- конец -----


//     return compare_str(real_str1, real_str2);
// }





void murderous_swap_str(void* mass, int ind1, int ind2, size_t size) // Работает для любых (по типу) массивов
{
    assert(mass);

    char* additional_ind = NULL;

    additional_ind                = *(char**)(mass + ind2 * size);
    *(char**)(mass + ind2 * size) = *(char**)(mass + ind1 * size);
    *(char**)(mass + ind1 * size) = additional_ind;
}












// int compare_str_end(char* str1, char* str2)  // Вернет > 0 при str1 > str2, < 0 при str1 < str2, = 0 при str1 = str2
// {
//     assert(str1);
//     assert(str2);

//     int ind_elem_1 = str_len(str1) - 1;
//     int ind_elem_2 = str_len(str2) - 1;

//     while ((ind_elem_1 != 0) && (ind_elem_2 != 0)) // TODO: for can do your code smaller and clearer than while
//     {
//         // Смещение счетчика до буквы в str1 и str2
//         ind_elem_1 = go_back_to_next_letter(str1, ind_elem_1);
//         ind_elem_2 = go_back_to_next_letter(str2, ind_elem_2);

//         int el1 = tolower(str1[ind_elem_1]);
//         int el2 = tolower(str2[ind_elem_2]);

//         int comp = el1 - el2;
//         if (comp != 0)
//         {
//             return comp;
//         }

//         if (el1 == '\0') // Значит и el2 = '/0' 
//         {
//             return 0;
//         }

//         // Значит простое совпадение букв
//         ind_elem_1--;
//         ind_elem_2--;
//     }

//     return (str1[ind_elem_1] - str2[ind_elem_2]);  // Тут кто-то '\0', поэтому без tolower()
// }