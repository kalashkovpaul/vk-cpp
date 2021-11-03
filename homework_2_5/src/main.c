#include <stdio.h>
//#include "static_differences.h"
#include "dynamic_differences.h"
#include "create_binary_file.h"
#include "constants.h"

int main(void)
{
    int array[11] = { 0 };
    time_to_fork(array);
    for (int i = 0; i < 11; i++)
        printf("%d ", array[i]);
    int check = OK;
    // char filename[] = "test";
    // int differences[MAX_OF_DIFFERENCES + 1] = { 0 };
    // create_file(filename);
    // FILE *file = fopen(filename, "rb");
    // if (file)
    // {
    //     find_amounts_of_differences(file, differences);
    //     print_differences(differences);
    //     fclose(file);
    // }
    // else
    // {
    //     printf("Не удалось открыть файл!\n");
    //     check = ERR_FILE;
    // }
    printf("This is the end\n");
    return check;
}