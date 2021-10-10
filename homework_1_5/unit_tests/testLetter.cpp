#include <gtest/gtest.h>
#include <stdio.h>

extern "C"
{
#include "letter.h"
#include "constants.h"
}

TEST(getLetterFromFile, emptyLetter)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/emptyLetter.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "");
    EXPECT_STREQ(mail.recipient, "");
    EXPECT_STREQ(mail.topic, "");
    EXPECT_STREQ(mail.content, "");
    freeLetter(&mail);
    fclose(src);
}   

TEST(getLetterFromFile, emptyFile)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/emptyLetter.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_EQ(0, 0);
    EXPECT_STREQ(mail.sender, "");
    EXPECT_STREQ(mail.recipient, "");
    EXPECT_STREQ(mail.topic, "");
    EXPECT_STREQ(mail.content, "");
    freeLetter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, letterWithoutEnd)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/letterWithoutEnd.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, -2);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1\nParagraph2\nAnd there is no \"END\"");
    freeLetter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, oneStringContent)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/oneStringContent.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    freeLetter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, complexContentLetter)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/complexContentLetter.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "This is sender");
    EXPECT_STREQ(mail.recipient, "This is 2345678987654№;%:?*(*?:%;) Sender");
    EXPECT_STREQ(mail.topic, "Strange  topic  with spaces");
    EXPECT_STREQ(mail.content, "And finally, content, this is it;'~`\n    Here it is");
    freeLetter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, russianLetter)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/russianLetter.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Отправитель");
    EXPECT_STREQ(mail.recipient, "Получатель");
    EXPECT_STREQ(mail.topic, "Тема");
    EXPECT_STREQ(mail.content, "Содержание");
    freeLetter(&mail);
    fclose(src);
}

TEST(isSpam, notSpam)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/complexContentLetter.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "This is sender");
    EXPECT_STREQ(mail.recipient, "This is 2345678987654№;%:?*(*?:%;) Sender");
    EXPECT_STREQ(mail.topic, "Strange  topic  with spaces");
    EXPECT_STREQ(mail.content, "And finally, content, this is it;'~`\n    Here it is");
    check = isSpam(mail);
    EXPECT_EQ(check, 0);
    freeLetter(&mail);
    fclose(src);
}

TEST(isSpam, spamInSender)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInSender.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender with швейцарские часы");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = isSpam(mail);
    EXPECT_EQ(check, 1);
    freeLetter(&mail);
    fclose(src);
}

TEST(isSpam, spamInRecipient)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInRecipient.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient = швейцарские часы");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = isSpam(mail);
    EXPECT_EQ(check, 0);
    freeLetter(&mail);
    fclose(src);
}

TEST(isSpam, spamInTopic)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInTopic.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic about швейцарские часы");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = isSpam(mail);
    EXPECT_EQ(check, 1);
    freeLetter(&mail);
    fclose(src);
}

TEST(isSpam, spamInContent)
{
    letter mail = {};
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInContent.txt", "r");
    check = getLetterFromFile(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1 about швейцарские часы");
    check = isSpam(mail);
    EXPECT_EQ(check, 1);
    freeLetter(&mail);
    fclose(src);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}