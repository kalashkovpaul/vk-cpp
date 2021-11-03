#include "gtest/gtest.h"

extern "C" {
#include <sys/mman.h>
#include "dynamic_differences.h"
}

#include <stdio.h>

TEST(dynamic_differences, single_value_test)
{
    //const char filename[] = "single_value_test";
    // TODO: после 11.06.2021 изменить
    FILE *file = fopen("../../../../lib/my_dynamic_lib/unit_tests/src/single_value_test", "rb");
    ASSERT_FALSE(file == NULL);
    int* differences = (int *) mmap(NULL, sizeof(int) * 11, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ASSERT_FALSE(differences == MAP_FAILED);
    int check = 0;
    check = find_amounts_of_differences(file, differences);
    EXPECT_EQ(check, 0);
    EXPECT_EQ(differences[0], 0);
    EXPECT_EQ(differences[1], 0);
    EXPECT_EQ(differences[2], 0);
    EXPECT_EQ(differences[3], 0);
    EXPECT_EQ(differences[4], 14);
    EXPECT_EQ(differences[5], 0);
    EXPECT_EQ(differences[6], 0);
    EXPECT_EQ(differences[7], 0);
    EXPECT_EQ(differences[8], 0);
    EXPECT_EQ(differences[9], 0);
    EXPECT_EQ(differences[10], 0);
    fclose(file);
}

TEST(dynamic_differences, two_values_test)
{
    //const char filename[] = "two_values_test";
    // TODO: после 11.06.2021 изменить
    FILE *file = fopen("../../../../lib/my_dynamic_lib/unit_tests/src/two_values_test", "rb");
    ASSERT_FALSE(file == NULL);
    int* differences = (int *) mmap(NULL, sizeof(int) * 11, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ASSERT_FALSE(differences == MAP_FAILED);
    int check;
    check = find_amounts_of_differences(file, differences);
    EXPECT_EQ(check, 0);
    EXPECT_EQ(differences[0], 0);
    EXPECT_EQ(differences[1], 0);
    EXPECT_EQ(differences[2], 0);
    EXPECT_EQ(differences[3], 0);
    EXPECT_EQ(differences[4], 4);
    EXPECT_EQ(differences[5], 3);
    EXPECT_EQ(differences[6], 1);
    EXPECT_EQ(differences[7], 0);
    EXPECT_EQ(differences[8], 0);
    EXPECT_EQ(differences[9], 0);
    EXPECT_EQ(differences[10], 0);
    fclose(file);
}

TEST(dynamic_differences, wrong_file_test)
{
    int differences[11] = { 0 };
    int check;
    FILE *file = NULL;
    check = find_amounts_of_differences(file, differences);
    EXPECT_EQ(check, -1);
}

TEST(dynamic_differences, wrong_value_test)
{
    //const char filename[] = "single_value_test";
    // TODO: после 11.06.2021 изменить
    FILE *file = fopen("../../../../lib/my_dynamic_lib/unit_tests/src/single_value_test", "rb");
    ASSERT_FALSE(file == NULL);
    int *differences = NULL;
    int check;
    check = find_amounts_of_differences(file, differences);
    EXPECT_EQ(check, -1);
}

TEST(dynamic_differences, multiple_values_test)
{
    //const char filename[] = "two_values_test";
    // TODO: после 11.06.2021 изменить
    FILE *file = fopen("../../../../lib/my_dynamic_lib/unit_tests/src/multiple_values_test", "rb");
    ASSERT_FALSE(file == NULL);
    int* differences = (int *) mmap(NULL, sizeof(int) * 11, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ASSERT_FALSE(differences == MAP_FAILED);
    int check;
    check = find_amounts_of_differences(file, differences);
    EXPECT_EQ(check, 0);
    EXPECT_EQ(differences[0], 0);
    EXPECT_EQ(differences[1], 10);
    EXPECT_EQ(differences[2], 9);
    EXPECT_EQ(differences[3], 0);
    EXPECT_EQ(differences[4], 8);
    EXPECT_EQ(differences[5], 7);
    EXPECT_EQ(differences[6], 5);
    EXPECT_EQ(differences[7], 5);
    EXPECT_EQ(differences[8], 0);
    EXPECT_EQ(differences[9], 0);
    EXPECT_EQ(differences[10], 3);
    fclose(file);
}