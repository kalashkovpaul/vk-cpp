#include <stdio.h>
#include <sys/mman.h>

#include "static_differences.h"
#include "constants.h"
#include "create_binary_file.h"
//#include "dynamic_differences.h"

int main(void)
{
    // int array[11] = { 0 };
    // time_to_fork(array);
    // for (int i = 0; i < 11; i++)
    //     printf("%d ", array[i]);
    int check = OK;
    char filename[] = "test";
    int* differences = mmap(NULL, sizeof(int) * (MAX_OF_DIFFERENCES + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (differences == MAP_FAILED)
        check = ERR_MMAP;
    //int differences[MAX_OF_DIFFERENCES + 1] = { 0 };
    create_file(filename);
    FILE* file = fopen(filename, "rb");
    if (file && check == OK) {
        find_amounts_of_differences(file, differences);
        print_differences(differences);
        fclose(file);
    } else {
        printf("Не удалось открыть файл!\n");
        check = ERR_FILE;
    }
    return check;
}