#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../include/add_operations.h"

int is_digit(char *line)
{
    if (strlen(line) == 0)
    {
        return 0;
    }
    for (int i = 0; i < strlen(line); i++)
    {
        if (!isdigit(line[i]))
        {
            return 0;
        }
    }
    return 1;
}