#include <gtest/gtest.h>
#include <stdio.h>

extern "C"
{
#include "letter.h"
#include "constants.h"
}

TEST(getLetterFromFile, emptyLetter)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/emptyLetter.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "");
    EXPECT_STREQ(mail.recipient, "");
    EXPECT_STREQ(mail.topic, "");
    EXPECT_STREQ(mail.content, "");
    free_letter(&mail);
    fclose(src);
}   

TEST(getLetterFromFile, emptyFile)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/emptyLetter.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_EQ(0, 0);
    EXPECT_STREQ(mail.sender, "");
    EXPECT_STREQ(mail.recipient, "");
    EXPECT_STREQ(mail.topic, "");
    EXPECT_STREQ(mail.content, "");
    free_letter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, letterWithoutEnd)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/letterWithoutEnd.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, -2);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1\nParagraph2\nAnd there is no \"END\"");
    free_letter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, oneStringContent)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/oneStringContent.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    free_letter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, complexContentLetter)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/complexContentLetter.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "This is sender");
    EXPECT_STREQ(mail.recipient, "This is 2345678987654№;%:?*(*?:%;) Sender");
    EXPECT_STREQ(mail.topic, "Strange  topic  with spaces");
    EXPECT_STREQ(mail.content, "And finally, content, this is it;'~`\n    Here it is");
    free_letter(&mail);
    fclose(src);
}

TEST(getLetterFromFile, russianLetter)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/russianLetter.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Отправитель");
    EXPECT_STREQ(mail.recipient, "Получатель");
    EXPECT_STREQ(mail.topic, "Тема");
    EXPECT_STREQ(mail.content, "Содержание");
    free_letter(&mail);
    fclose(src);
}

TEST(isSpam, notSpam)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/complexContentLetter.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "This is sender");
    EXPECT_STREQ(mail.recipient, "This is 2345678987654№;%:?*(*?:%;) Sender");
    EXPECT_STREQ(mail.topic, "Strange  topic  with spaces");
    EXPECT_STREQ(mail.content, "And finally, content, this is it;'~`\n    Here it is");
    check = is_spam(mail);
    EXPECT_EQ(check, 0);
    free_letter(&mail);
    fclose(src);
}

TEST(isSpam, spamInSender)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInSender.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender with швейцарские часы");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = is_spam(mail);
    EXPECT_EQ(check, 1);
    free_letter(&mail);
    fclose(src);
}

TEST(isSpam, spamInRecipient)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInRecipient.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient = швейцарские часы");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = is_spam(mail);
    EXPECT_EQ(check, 0);
    free_letter(&mail);
    fclose(src);
}

TEST(isSpam, spamInTopic)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInTopic.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic about швейцарские часы");
    EXPECT_STREQ(mail.content, "Paragraph1");
    check = is_spam(mail);
    EXPECT_EQ(check, 1);
    free_letter(&mail);
    fclose(src);
}

TEST(isSpam, spamInContent)
{
    letter_t mail = { NULL, NULL, NULL, NULL };
    int check = 0;
    FILE *src = fopen("../unit_tests/spamInContent.txt", "r");
    check = get_letter_from_file(src, &mail); 
    EXPECT_EQ(check, 0);
    EXPECT_STREQ(mail.sender, "Sender");
    EXPECT_STREQ(mail.recipient, "Recipient");
    EXPECT_STREQ(mail.topic, "Topic");
    EXPECT_STREQ(mail.content, "Paragraph1 about швейцарские часы");
    check = is_spam(mail);
    EXPECT_EQ(check, 1);
    free_letter(&mail);
    fclose(src);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}