/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-2-2      tzy          first implementation
 */
#include "mtest.h"
#include <stdio.h>
#include <string.h>

TEST(xx_module, connect_test) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(xx_module, disconnect_test) {
    EXPECT_STREQ("a", "a");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1); 
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(xx_module, open_test) {
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
    EXPECT_GT(4,3);
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
    mtest_list();
    mtest_run("xx_module", 1);
    return 0;
}
