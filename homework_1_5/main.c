#include "letter.h"

#include <stdio.h>

int main(void)
{
    int check = OK;
    letter mail = { 0 };
    check = getLetterFromUser(&mail);
    if (check == OK)
    {
        filePrintLetterInfo(stdout, mail);
        if (isSpam(mail))
            printf("Спам!\n");
        else
            printf("Ладно, не спам...\n");
        freeLetter(&mail);
    }
    return check;
}