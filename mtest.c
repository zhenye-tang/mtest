#include "mtest.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
extern const int __mtest_begin;
extern const int __mtest_end;
#endif

struct test_suites
{
    const char* suites_name;
    int suites_index;
    int test_num;
};

struct test_suites_record
{
    struct test_suites* suites;
    int suites_cnt;
    unsigned int test_cnt;
};

struct mtest_commond
{
    const char *cmd;
    int (*cmd_entry)(int argc, char** argv);
};

struct uint_test_cache
{
    const struct uint_test** test;
    int test_cnt;
};

typedef int (*iterator_call)(const struct uint_test* item);

static const struct uint_test* mtest_begin_object;
static const struct uint_test* mtest_end_object;
static struct test_suites_record suites_record;
static struct uint_test_cache cache;

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
    static int suites_index = 0, cur_index = 0;
    if (last_item == NULL)
    {
        suites_record.suites[0].test_num = 1;
        suites_record.suites[0].suites_name = item->name;
        suites_record.suites[0].suites_index = 0;
        suites_record.suites_cnt = 1;
    }
    else if (!strcmp(last_item->name, item->name))
    {
        suites_record.suites[suites_index].test_num++;
    }
    else
    {
        suites_index += 1;
        suites_record.suites[suites_index].test_num = 1;
        suites_record.suites[suites_index].suites_name = item->name;
        suites_record.suites[suites_index].suites_index = cur_index;
        suites_record.suites_cnt++;
    }
    cache.test[cur_index] = item;

    cur_index++;
    last_item = item;

    return 0;
}

static int mtest_object_count(const struct uint_test* item)
{
    static const struct uint_test* last_item = NULL;
    if (last_item == NULL)
    {
        suites_record.suites_cnt = 1;
    }
    else if (strcmp(last_item->name, item->name))
    {
        suites_record.suites_cnt++;
    }
    last_item = item;
    cache.test_cnt++;
    suites_record.test_cnt++;

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
#elif defined (__GNUC__)
    mtest_begin_object = (const struct uint_test*)&__mtest_begin;
    mtest_end_object = (const struct uint_test*)&__mtest_end;
#endif
    mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_object_count);

    suites_record.suites = malloc(suites_record.suites_cnt * sizeof(struct test_suites));
    cache.test = malloc(cache.test_cnt * sizeof(struct uint_test *));

    if (suites_record.suites && cache.test)
    {
        mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_record_test_suites);
    }
    prepared = 1;
}

static int mtest_run_all_testcase(const struct uint_test* item)
{
    printf("[==========] Running %d tests from %d test suites.\n", suites_record.test_cnt, suites_record.suites_cnt);
    printf("[----------] %d test from %s.\n", suites_record.suites[0].test_num, suites_record.suites[0].suites_name);
    return 0;
}

int mtest_run_all(int count)
{
    while(count--)
    {
        for(int i = 0; i < cache.test_cnt; i++)
        {
            printf("name = %s, desc = %s.\n", cache.test[i]->name, cache.test[i]->desc);
        }
    }

    return 0;
}

int mtest_list(void)
{ 
    printf("have %d tests from %d test suites:\n", suites_record.test_cnt, suites_record.suites_cnt);

    for(int i = 0; i < suites_record.suites_cnt; i++)
    {
        printf("%s:", suites_record.suites[i].suites_name);
        for(int j = suites_record.suites[i].suites_index; j < suites_record.suites[i].suites_index + suites_record.suites[i].test_num; j++)
        {
            printf(" %s", cache.test[j]->desc);
            cache.test[j]->test_entry(cache.test[j]->name, cache.test[j]->desc);
        }
        printf("\n");
    }

    return 0;
}

static int mtest_suites_iterator(const struct uint_test* ut)
{
    printf("name : %s desc = %s.\n", ut->name, ut->desc);
    return 0;
}

int mtest_run_test_suites(const char *name, int count)
{
    struct test_suites *suites = NULL;
    for(int i = 0 ; i < suites_record.suites_cnt; i++)
    {
        if(!strcmp(name, suites_record.suites[i].suites_name))
        {
            suites = &suites_record.suites[i];
            break;
        }
    }

    while(count --)
    {
        for(int i = suites->suites_index; i < suites->suites_index + suites->test_num; i++)
        {
            printf("name = %s, desc = %s.\n", cache.test[i]->name, cache.test[i]->desc);
        }
    }

    return 0;
}

int mtest_cmd(int argc, char** argv)
{
    mtest_prepare();

    // mtest_run_test_suites("test", 1);
    // mtest_run_test_suites("gaga", 1);
    // mtest_run_test_suites("haha", 1);

    // mtest_run_all(2);
    mtest_list();

    return 0;
}