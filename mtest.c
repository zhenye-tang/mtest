#include "mtest.h"
#include <string.h>
#include <stdio.h>
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

struct test_suites
{
    const char* suites_name;
    int suites_index;
    int test_num;
};

struct test_suites_record
{
    struct test_suites *suites;
    int suites_cnt;
    int test_cnt;
};

typedef int (*iterator_call)(const struct uint_test* item);

static const struct uint_test* mtest_begin_object;
static const struct uint_test* mtest_end_object;
struct test_suites_record suites_record = { NULL, 0 };

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
    EXPECT_STREQ("a", "b");
    EXPECT_STRCASEEQ("b", "B");
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
    EXPECT_NE(1, 2);
    EXPECT_END();
}

//skip gap addr
static const struct uint_test* mtest_next(const struct uint_test* ut)
{
    unsigned int* ptr;
    ptr = (unsigned int*)(ut + 1);
    while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*)&__mtest_end))
        ptr++;
    return (const struct uint_test*)ptr;
}

static void mtest_section_iterator(const struct uint_test* begin, const struct uint_test* end, iterator_call call)
{
    while (begin != end)
    {
        if (call)
            call(begin);
        begin = mtest_next(begin);
    }
}

static int mtest_record_test_suites(const struct uint_test* item)
{
    static const struct uint_test* last_item = NULL;
    static int suites_index = 0;
    if (last_item == NULL)
    {
        suites_record.suites[suites_index].test_num = 1;
        suites_record.suites_cnt = 1;
    }
    else if(!strcmp(last_item->name, item->name))
    {
        suites_record.suites[suites_index].test_num ++;
    }
    else
    {
        suites_index += 1;
        suites_record.suites[suites_index].test_num = 1;
        suites_record.suites_cnt ++;
    }

    suites_record.suites[suites_index].suites_name = item->name;
    suites_record.suites[suites_index].suites_index = suites_index;
    last_item = item;

    return 0;
}

static void mtest_prepare(void)
{
    static char prepared = 0;
    if (prepared)
        return;
#if defined(_MSC_VER)
    mtest_begin_object = &__mtest_begin + 1;
    mtest_end_object = &__mtest_end;
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
    mtest_begin_object = (const struct uint_test*)&__mtest_begin;
    mtest_end_object = (const struct uint_test*)&__mtest_end;
#endif
    suites_record.test_cnt = mtest_end_object - mtest_begin_object;
    if (suites_record.test_cnt > 0 && (suites_record.suites = rt_malloc(suites_record.test_cnt * sizeof(struct test_suites))))
    {
        mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_record_test_suites);
        for (int i = 0; i < suites_record.suites_cnt; i++)
        {
            printf("suites name : %s index = %d test cnt = %d.\n", suites_record.suites[i].suites_name, suites_record.suites[i].suites_index, suites_record.suites[i].test_num);
        }
    }
    prepared = 1;
}


static int mtest_run_all_testcase(const struct uint_test* item)
{
    printf("[==========] Running %d tests from %d test suites.", suites_record.test_cnt, suites_record.suites_cnt);
    printf("[----------] %d test from %s.", suites_record.suites[0].test_num, suites_record.suites[0].suites_name);
}


#include "rtthread.h"

/* run testcase */
void mtest_run(int argc, char** argv)
{
    mtest_prepare();
    mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_run_all_testcase);
}
MSH_CMD_EXPORT(mtest_run, mtest_run);