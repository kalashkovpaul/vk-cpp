#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "letter.h"

static int file_read_line(FILE* src, char** str)
{
    int check = OK;
    int allocated_length = 2;
    *str = malloc(allocated_length * sizeof(char));
    if (*str) {
        char ch = 0;
        char* tmp = NULL;
        int i = 0;
        while (ch != '\n' && check != ERR_MEMORY && !feof(src)) {
            fscanf(src, "%c", &ch);
            check = OK;
            if (i == allocated_length) {
                allocated_length *= 2;
                tmp = realloc(*str, allocated_length * sizeof(char));
                if (tmp)
                    *str = tmp;
                else
                    check = ERR_MEMORY;
            }
            if (check == OK)
                (*str)[i++] = ch;
        }
        if (ch != '\n')
            check = ERR_WITHOUT_END;
        else if (check == OK)
            (*str)[i - 1] = 0;
    } else
        check = ERR_MEMORY;
    return check;
}

static int concatenate_lines(char** beginning, char* end)
{
    int check = OK;
    int beginning_length = strlen(*beginning);
    int end_length = strlen(end);
    char* tmp = NULL;
    tmp = realloc(*beginning, (beginning_length + end_length + 2) * sizeof(char)); // +  2: 1 на перенос строки в центре, 1 на терм. ноль
    if (tmp) {
        *beginning = tmp;
        (*beginning)[beginning_length] = '\n';
        char* from = *beginning + beginning_length + 1;
        memcpy(from, end, end_length + 1);
        (*beginning)[beginning_length + end_length + 1] = 0;
    } else
        check = ERR_MEMORY;
    return check;
}

static int is_it_time_to_terminate(char* str)
{
    return (strncmp(str, CONTENT_TERMINATION_SEQUENSE, CONTENT_TERMINATION_SEQUENSE_LENGTH) == 0
        && str[CONTENT_TERMINATION_SEQUENSE_LENGTH] == 0);
}

static int file_get_content(FILE* src, char** content)
{
    char* line_of_content = NULL;
    int check = OK;
    check = file_read_line(src, content);
    if (check == OK && is_it_time_to_terminate(*content)) {
        free(*content);
        char* tmp = malloc(sizeof(char));
        *content = tmp;
        **content = '\0';
    } else if (check == OK && !is_it_time_to_terminate(*content)) {
        check = file_read_line(src, &line_of_content);
        while (check == OK && !is_it_time_to_terminate(line_of_content)) {
            concatenate_lines(content, line_of_content);
            free(line_of_content);
            check = file_read_line(src, &line_of_content);
        }
    }
    free(line_of_content);
    return check;
}

int get_letter_from_file(FILE* src, letter_t* current_letter)
{
    int check = OK;
    check = file_read_line(src, &(current_letter->sender));
    if (check == OK) {
        check = file_read_line(src, &(current_letter->recipient));
        if (check == OK) {
            check = file_read_line(src, &(current_letter->topic));
            if (check == OK)
                check = file_get_content(src, &(current_letter->content));
        }
    }
    return check;
}

int get_letter_from_user(letter_t* current_letter)
{
    int check = OK;
    printf("Отправитель: \n");
    check = file_read_line(stdin, &(current_letter->sender));
    if (check == OK) {
        printf("Получатель: \n");
        check = file_read_line(stdin, &(current_letter->recipient));
        if (check == OK) {
            printf("Тема письма: \n");
            check = file_read_line(stdin, &(current_letter->topic));
            if (check == OK) {
                printf("Содержание письма: \n");
                check = file_get_content(stdin, &(current_letter->content));
            }
        }
    }
    return check;
}

void file_print_letter_info(FILE* dst, letter_t current_letter)
{
    fprintf(dst, "Отправитель:\n");
    fprintf(dst, "%s\n", current_letter.sender);
    fprintf(dst, "Получатель:\n");
    fprintf(dst, "%s\n", current_letter.recipient);
    fprintf(dst, "Тема письма:\n");
    fprintf(dst, "%s\n", current_letter.topic);
    fprintf(dst, "Содержание письма:\n");
    fprintf(dst, "%s\n", current_letter.content);
}

void free_letter(letter_t* current_letter)
{
    free(current_letter->sender);
    current_letter->sender = NULL;
    free(current_letter->recipient);
    current_letter->recipient = NULL;
    free(current_letter->topic);
    current_letter->topic = NULL;
    free(current_letter->content);
    current_letter->content = NULL;
}

int is_spam(letter_t current_letter)
{
    return (strstr(current_letter.sender, SPAM_TRIGGER) != NULL || strstr(current_letter.topic, SPAM_TRIGGER) != NULL || strstr(current_letter.content, SPAM_TRIGGER) != NULL);
}
