#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "letter.h"

static int fileReadLine(FILE* src, char** str)
{
    int check = OK;
    int allocatedLength = 2;
    *str = malloc(allocatedLength * sizeof(char));
    if (*str) {
        char ch = 0;
        char* tmp = NULL;
        int i = 0;
        while (ch != '\n' && check != ERR_MEMORY && !feof(src)) {
            fscanf(src, "%c", &ch);
            check = OK;
            if (i == allocatedLength) {
                allocatedLength *= 2;
                tmp = realloc(*str, allocatedLength * sizeof(char));
                if (tmp)
                {
                    *str = tmp;
                    //memset(*str + i, 0, sizeof(char) * i);
                }
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

static int concatenateLines(char** beginning, char* end)
{
    int check = OK;
    int beginningLength = strlen(*beginning);
    int endLength = strlen(end);
    char* tmp = NULL;
    tmp = realloc(*beginning, (beginningLength + endLength + 2) * sizeof(char)); // +  2: 1 на перенос строки в центре, 1 на терм. ноль
    if (tmp) {
        *beginning = tmp;
        (*beginning)[beginningLength] = '\n';
        char* from = *beginning + beginningLength + 1;
        memcpy(from, end, endLength + 1);
        (*beginning)[beginningLength + endLength + 1] = 0;
    } else
        check = ERR_MEMORY;
    return check;
}

static int isItTimeToTerminate(char* str)
{
    return (strncmp(str, CONTENT_TERMINATION_SEQUENSE, CONTENT_TERMINATION_SEQUENSE_LENGTH) == 0
        && str[CONTENT_TERMINATION_SEQUENSE_LENGTH] == 0);
}

static int fileGetContent(FILE* src, char** content)
{
    char* lineOfContent = NULL;
    int check = OK;
    check = fileReadLine(src, content);
    if (check == OK && isItTimeToTerminate(*content)) {
        free(*content);
        char* tmp = malloc(sizeof(char));
        *content = tmp;
        **content = '\0';
    } else if (check == OK && !isItTimeToTerminate(*content)) {
        check = fileReadLine(src, &lineOfContent);
        while (check == OK && !isItTimeToTerminate(lineOfContent)) {
            concatenateLines(content, lineOfContent);
            free(lineOfContent);
            check = fileReadLine(src, &lineOfContent);
        }
    }
    free(lineOfContent);
    return check;
}

int getLetterFromFile(FILE* src, letter* currentLetter)
{
    int check = OK;
    check = fileReadLine(src, &(currentLetter->sender));
    if (check == OK) {
        check = fileReadLine(src, &(currentLetter->recipient));
        if (check == OK) {
            check = fileReadLine(src, &(currentLetter->topic));
            if (check == OK)
                check = fileGetContent(src, &(currentLetter->content));
        }
    }
    return check;
}

int getLetterFromUser(letter* currentLetter)
{
    int check = OK;
    printf("Отправитель: \n");
    check = fileReadLine(stdin, &(currentLetter->sender));
    if (check == OK) {
        printf("Получатель: \n");
        check = fileReadLine(stdin, &(currentLetter->recipient));
        if (check == OK) {
            printf("Тема письма: \n");
            check = fileReadLine(stdin, &(currentLetter->topic));
            if (check == OK) {
                printf("Содержание письма: \n");
                check = fileGetContent(stdin, &(currentLetter->content));
            }
        }
    }
    return check;
}

void filePrintLetterInfo(FILE* dst, letter currentLetter)
{
    fprintf(dst, "Отправитель:\n");
    fprintf(dst, "%s\n", currentLetter.sender);
    fprintf(dst, "Получатель:\n");
    fprintf(dst, "%s\n", currentLetter.recipient);
    fprintf(dst, "Тема письма:\n");
    fprintf(dst, "%s\n", currentLetter.topic);
    fprintf(dst, "Содержание письма:\n");
    fprintf(dst, "%s\n", currentLetter.content);
}

void freeLetter(letter* currentLetter)
{
    free(currentLetter->sender);
    currentLetter->sender = NULL;
    free(currentLetter->recipient);
    currentLetter->recipient = NULL;
    free(currentLetter->topic);
    currentLetter->topic = NULL;
    free(currentLetter->content);
    currentLetter->content = NULL;
}

int isSpam(letter currentLetter)
{
    return (strstr(currentLetter.sender, SPAM_TRIGGER) != NULL || strstr(currentLetter.topic, SPAM_TRIGGER) != NULL || strstr(currentLetter.content, SPAM_TRIGGER) != NULL);
}
