#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <assert.h>


void murderous_swap_str(void* mass, int ind1, int ind2, size_t size) // Эмммммм... Работает ли оно для ЛЮБЫХ (по типу) массивов?
{
    assert(mass);

    char* additional_ind = NULL;

    additional_ind                = *(char**)(mass + ind2 * size);
    printf("%c\n", *additional_ind);
    *(char**)(mass + ind2 * size) = *(char**)(mass + ind1 * size);
    printf("%s\n", *(char**)(mass + ind2 * size));
    *(char**)(mass + ind1 * size) = additional_ind;
}


int main()
{
    int mas1[10] = {2, 4, 3, 7, 1, 8, 9, 5, 6, 7};

    // murderous_swap_str(mas1, 2, 5, sizeof(int)); // runtime error store to misaligned address 0x7090f6909044 
    //                                              //for type 'char *', which requires 8 byte alignment 0x7090f6909044
    // printf("%d, %d\n", mas1[2], mas1[5]);        // но выводит




    // printf("!1111\n");

    // int mas2[5] = {'a', 'b', 'c', 'd'};
    // printf("%c, %c\n", mas2[2], mas2[0]);         // 

    // murderous_swap_str(mas2, 2, 0, sizeof(char));
    // printf("%c, %c\n", mas2[2], mas2[0]);         // выводит ,  -  че блин 0_o :(  ༼;´༎ຶ ۝ ༎ຶ༽

    
    
    
    int mas3[5] = {'a', 'b', 'c', 'd', 'e'};
    printf("%c, %c\n", mas3[2], mas3[0]);

    murderous_swap_str(mas3, 2, 0, sizeof(char)); // ༼;´༎ຶ ۝ ༎ຶ༽   (⁠╥⁠﹏⁠╥⁠)  (ಥ﹏ಥ)  ༼ಢ_ಢ༽
    printf("%c, %c\n", mas3[2], mas3[0]);

    return 0;
}