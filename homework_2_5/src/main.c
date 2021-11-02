#include <stdio.h>
#include "static_differences.h"
#include "create_binary_file.h"
#include "constants.h"

int main(void)
{
    char filename[] = "test";
    int differences[MAX_OF_DIFFERENCES + 1] = { 0 };
    create_file(filename);
    FILE *file = fopen(filename, "rb");
    int check = OK;
    if (file)
    {
        find_amounts_of_differences(file, differences);
        print_differences(differences);
        fclose(file);
    }
    else
    {
        printf("Не удалось открыть файл!\n");
        check = ERR_FILE;
    }
    return check;
}