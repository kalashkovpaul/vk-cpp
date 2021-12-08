#include <stdio.h>
#include <sys/mman.h>
#include <time.h>

#include "static_differences.h"
#include "constants.h"
#include "create_binary_file.h"
//#include "dynamic_differences.h"

int main(void)
{
    int check = OK;

    struct timespec start, finish;
    double time;

    char filename[] = "test";
    int* differences = mmap(NULL, sizeof(int) * (MAX_OF_DIFFERENCES + 1), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (differences == MAP_FAILED)
        check = ERR_MMAP;
    create_file(filename);
    FILE* file = fopen(filename, "rb");
    if (file && check == OK) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        find_amounts_of_differences(file, differences);
        print_differences(differences);
        fclose(file);
        clock_gettime(CLOCK_MONOTONIC, &finish);
        time = (finish.tv_sec - start.tv_sec);
        time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("time: %lf\n", time);
    } else {
        printf("Не удалось открыть файл!\n");
        check = ERR_FILE;
    }
    return check;
}