#include <stdio.h>
#include "constants.h"

static int find_amount_of_fixed_difference(FILE *file, int *value, int difference);

int find_amounts_of_differences(FILE *file, int *differences)
{
    int check = OK;
    for (int i = 0; i <= MAX_OF_DIFFERENCES && check == OK; i++)
        check = find_amount_of_fixed_difference(file, differences + i, i);
    return check;
}

static int find_amount_of_fixed_difference(FILE *file, int *value, int difference)
{
    if (file == NULL || value == NULL)
        return ERR_ARG;
    fseek(file, 0, SEEK_SET);
    char current_byte = 0, previous_byte = 0;
    int check = 0;
    check = fread(&previous_byte, sizeof(char), 1, file);
    while (check)
    {
        check = fread(&current_byte, sizeof(char), 1, file);
        if (check)
        {
            if (current_byte - previous_byte == difference || current_byte - previous_byte == -difference)
                *value += 1;
            previous_byte = current_byte;
        }
    }
    return OK;
}

void print_differences(int *differences)
{
    for (int i = 0; i <= MAX_OF_DIFFERENCES; i++)
        printf("%d ", differences[i]);
    printf("\n");
}