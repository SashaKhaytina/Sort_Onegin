#include <stdio.h>
#include "errors.h"

void print_errors_code(ProgramStatus status)
{
    switch (status)
    {
    case OK:
        fprintf(stderr, "Программа завершила работу без ошибок\n");
        break;
    
    case ERROR_OPENING_FILE:
        fprintf(stderr, "Ошибка открытия файла\n");
        break;
    
    case ERROR_READING:
        fprintf(stderr, "Ошибка чтения файла\n");
        break;
    
    case ERROR_MEMORY:
        fprintf(stderr, "Ошибка выделения памяти\n");
        break;
    
    default:
        fprintf(stderr, "Ошибка в коде ошибки");
        break;
    }
}