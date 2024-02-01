#include "mtest.h"
#include <stdio.h>

TEST(test, qqq) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(test, ppp) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1); 
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(test, xxx) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(gaga, xxx) {
    EXPECT_STREQ("a", "a");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_LE(2,2);
    EXPECT_LT(1,2);
    EXPECT_GE(3,2);
    EXPECT_GT(3,3);
    EXPECT_END();
}

TEST(gaga, www) {
    EXPECT_STREQ("a", "a");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(kaka, www) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(gugu, www) {
    EXPECT_STREQ("a", "a");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}


int main(int argc, char *argv[])
{
    // MTEST_PRINT_NORMOL("kaka\n");
    // MTEST_PRINT_ERROR("gaga\n");

    // MTEST_PRINT_COLOR(BLACK, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(RED, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(GREEN, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(YELLOW, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(BLUE, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(PURPLE, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(CYAN, "hello %s.\n", "world");
    // MTEST_PRINT_COLOR(WHITE, "hello %s.\n", "world");

    extern int mtest_cmd(int argc, char** argv);
    mtest_cmd(argc, argv);
    return 0;
}