#ifndef LETTER_H_

#define LETTER_H_

#include "stdio.h"

#include "constants.h"

#define CONTENT_TERMINATION_SEQUENSE "END"
#define CONTENT_TERMINATION_SEQUENSE_LENGTH 3
#define SPAM_TRIGGER "швейцарские часы"

typedef struct
{
    char* sender;
    char* recipient;
    char* topic;
    char* content;
} letter_t;

int get_letter_from_file(FILE* src, letter_t* currentLetter);

int get_letter_from_user(letter_t* currentLetter);

void file_print_letter_info(FILE* dst, letter_t currentLetter);

void free_letter(letter_t* currentLetter);

int is_spam(letter_t currentLetter);

#endif
