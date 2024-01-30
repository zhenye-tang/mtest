#include "mtest.h"
#include <string.h>
#include <stdio.h>
#include <finsh.h>


#pragma section("Mtest$a", read)
const char __mtest_begin_name[] = "__start";
const char __mtest_begin_desc[] = "begin of mtest";
__declspec(allocate("Mtest$a")) const struct uint_test __mtest_begin =
{
    __mtest_begin_name,
    __mtest_begin_desc,
    NULL
};

#pragma section("Mtest$z", read)
const char __mtest_end_name[] = "__end";
const char __mtest_end_desc[] = "end of mtest";
__declspec(allocate("Mtest$z")) const struct uint_test __mtest_end =
{
    __mtest_end_name,
    __mtest_end_desc,
    NULL
};

TEST(haha, gaga) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 2);
    EXPECT_NE(1, 2);
}

void mtest_run(int argc, char* argv)
{
    /* 遍历段内测试单元 */


}
