#include "letter.h"

#include <stdio.h>

int main(void)
{
    printf("Домашнее задание 1\n");
    int check = OK;
    letter_t mail = { NULL, NULL, NULL, NULL };
    check = get_letter_from_user(&mail);
    if (check == OK) {
        file_print_letter_info(stdout, mail);
        if (is_spam(mail))
            printf("Спам!\n");
        else
            printf("Ладно, не спам...\n");
        free_letter(&mail);
    }
    return check;
}