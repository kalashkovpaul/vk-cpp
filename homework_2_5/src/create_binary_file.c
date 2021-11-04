#include <stdint.h>
#include <stdio.h>

void create_file(const char* filename)
{
    FILE* file = fopen(filename, "wb");
    int64_t bytes_amount = 10;
    int64_t i = 0;
    char byte = 0;
    for (i = 0; i < bytes_amount; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 1;
    }
    for (i = 0; i < bytes_amount - 1; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 2;
    }
    for (i = 0; i < bytes_amount - 2; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 4;
    }
    for (i = 0; i < bytes_amount - 3; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 5;
    }
    for (i = 0; i < bytes_amount - 4; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 6;
    }
    for (i = 0; i < bytes_amount - 5; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 7;
    }
    for (i = 0; i < bytes_amount - 6; i++) {
        fwrite(&byte, sizeof(char), 1, file);
        byte += 10;
    }
    fclose(file);
}