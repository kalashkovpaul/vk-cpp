#ifndef LETTER_H_

#define LETTER_H_

#include "stdio.h"

#include "constants.h"

#define CONTENT_TERMINATION_SEQUENSE "END"
#define CONTENT_TERMINATION_SEQUENSE_LENGTH 3
#define SPAM_TRIGGER "швейцарские часы"

typedef struct
{
    char *sender;
    char *recipient;
    char *topic;
    char *content;
} letter;

int getLetterFromFile(FILE *src, letter *currentLetter);

int getLetterFromUser(letter *currentLetter);

void filePrintLetterInfo(FILE *dst, letter currentLetter);

void freeLetter(letter *currentLetter);

int isSpam(letter currentLetter);

#endif
