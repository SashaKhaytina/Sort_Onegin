#ifndef ERRORS_H
#define ERRORS_H

enum ProgramStatus
{
    OK,
    ERROR_OPENING_FILE,
    ERROR_READING,
    ERROR_MEMORY
};


void print_errors_code(ProgramStatus status);

#endif