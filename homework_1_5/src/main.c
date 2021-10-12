#include "letter.h"

#include <stdio.h>

int main(void)
{
    printf("Домашнее задание 1\n");
    int check = OK;
    letter mail = { NULL, NULL, NULL, NULL };
    check = getLetterFromUser(&mail);
    if (check == OK) {
        filePrintLetterInfo(stdout, mail);
        if (isSpam(mail))
            printf("Спам!\n");
        else
            printf("Ладно, не спам...\n");
        freeLetter(&mail);
    }
    return check;
}