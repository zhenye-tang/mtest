#include "mtest.h"
#include <string.h>
#include <stdio.h>

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
extern int __mtest_begin;
extern int __mtest_end;
#endif

static const struct uint_test *mtest_begin_object;
static const struct uint_test *mtest_end_object;

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

//skip gap addr
static const struct uint_test *mtest_next(const struct uint_test *ut)
{
    unsigned int *ptr;
    ptr = (unsigned int *)(ut + 1);
    while ((*ptr == 0) && ((unsigned int *)ptr < (unsigned int *) &__mtest_end))
        ptr ++;
    return (const struct uint_test *)ptr;
}

static void mtest_prepare(void)
{
    static int prepared = 0;
    if(prepared)
        return;
#if defined(_MSC_VER)
    mtest_begin_object = &__mtest_begin + 1;
    mtest_end_object = &__mtest_end;
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
    mtest_begin_object = (const struct uint_test *)&__mtest_begin;
    mtest_end_object = (const struct uint_test *)&__mtest_end;
#endif
    prepared = 1;
}

void mtest_run(int argc, char** argv)
{
    mtest_prepare();


    const struct uint_test* begin = mtest_begin_object;
    printf("[----------] Global test environment set-up.\n");
    while (begin != mtest_end_object)
    {
        printf("[ RUN      ] %s.%s", begin->name, begin->desc);
        int res = begin->test_entry(begin->name, begin->desc);
        if(res == 0)
            printf("[       OK ] %s.%s (0 ms)", begin->name, begin->desc);
        else
            printf("[  FAILED  ] connect.connect (0 ms)", begin->name, begin->desc);;
        begin = mtest_next(begin);
    }
}
