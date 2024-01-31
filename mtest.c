#include "mtest.h"
#include <string.h>
#include <stdio.h>
#include <finsh.h>
#include "rtthread.h"

#if defined(_MSC_VER)
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
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
/* GNU GCC Compiler and TI CCS */
extern struct uint_test __mtest_begin;
extern struct uint_test __mtest_end;
#endif

TEST(haha, gaga) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(test, kaka) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

TEST(test, qqq) {
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

void mtest_run(int argc, char* argv)
{
    const struct uint_test* begin = (const struct uint_test*)&__mtest_begin + 1;
    while (begin != &__mtest_end)
    {
        rt_kprintf("name = %s desc = %s\n", begin->name, begin->desc);
        begin->test_entry(begin->name, begin->desc);
        begin++;
    }

}
MSH_CMD_EXPORT(mtest_run, mtest_run);
