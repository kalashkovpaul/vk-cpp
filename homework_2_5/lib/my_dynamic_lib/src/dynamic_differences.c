#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "constants.h"


#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)

static size_t find_size_of_file(FILE *file);

static int find_amount_of_fixed_difference(const char *data, int file_size, int difference);

static void copy_data_from_file(FILE *src, int file_size, char *dst);

static void print_differences(int *differences);

int find_amounts_of_differences(FILE *file, int *differences)
{
    if (file == NULL || differences == NULL)
        return ERR_ARG;
    struct stat file_info;
    int int_file = fileno(file);
    if (fstat(int_file, &file_info) == -1)
        return ERR_ARG;

    char *data = mmap(0, file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, int_file, 0);
    if (unlikely(data == MAP_FAILED))
        return ERR_MMAP;
    copy_data_from_file(file, file_info.st_size, data);

    char *fixed_difference = mmap(0, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (fixed_difference == MAP_FAILED)
        return ERR_MMAP;

    pid_t* pids = (pid_t*)mmap(0, (MAX_OF_DIFFERENCES + 1) * sizeof(pid_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (pids == MAP_FAILED)
        return ERR_MMAP;

    size_t* pid_number = (size_t*)mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (pid_number == MAP_FAILED)
        return ERR_MMAP;
    
    int check = OK;

    *fixed_difference = 0;

    size_t i = 0;

    for (i = 0; i <= MAX_OF_DIFFERENCES; i++)
    {
        pid_t pid = fork();
        if (pid)
        {
            if (i + 1 <= MAX_OF_DIFFERENCES)
            {
                i++;
                continue;
            }
            for (size_t j = 0; j <= MAX_OF_DIFFERENCES; j++)
            {
                int wstatus;
                waitpid(pids[i], &wstatus, 0);
                if (WIFEXITED(wstatus) == 0)
                    return ERR_FORK;
            }
        }
        else
        {
            pids[*pid_number] = pid;
            if (*fixed_difference <= MAX_OF_DIFFERENCES)
            {
                differences[*fixed_difference] = find_amount_of_fixed_difference(data, file_info.st_size, *fixed_difference);
            }
            *fixed_difference += 1;
            *pid_number += 1;
            pid_t daughter_pid = fork();
            if (daughter_pid)
            {
                if (unlikely(wait(0) == -1))
                    return ERR_FORK;
                exit(0);
            }
            else
            {
                if (*fixed_difference <= MAX_OF_DIFFERENCES)
                {
                    differences[*fixed_difference] = find_amount_of_fixed_difference(data, file_info.st_size, *fixed_difference);
                }
                *fixed_difference += 1;
                exit(0);
            }

        }
    }
    return OK;
}

static void copy_data_from_file(FILE *src, int file_size, char *dst)
{
    if (src == NULL || dst == NULL || file_size <= 0)
        return;
    fseek(src, 0, SEEK_SET);
    fread(dst, sizeof(char) * file_size, 1, src);
}

static int find_amount_of_fixed_difference(const char *data, int file_size, int difference)
{
    if (data == NULL)
    {
        errno = ERR_ARG;
        return ERR_ARG;
    }
    int index = 0;
    char current_byte = 0, previous_byte = 0;
    int value = 0;
    previous_byte = data[index++];
    while (index < file_size)
    {
        current_byte = data[index++];
        if (current_byte - previous_byte == difference || current_byte - previous_byte == -difference)
            value += 1;
        previous_byte = current_byte;
    }
    return value;
}

void print_differences(int *differences)
{
    for (int i = 0; i <= MAX_OF_DIFFERENCES; i++)
        printf("%d ", differences[i]);
    printf("\n");
}