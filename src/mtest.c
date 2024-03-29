﻿/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-1-30      tzy          first implementation
 */

#include "mtest.h"
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
/* GNU GCC Compiler */
extern const int __mtest_begin;
extern const int __mtest_end;
#endif

struct test_suites
{
    const char* suites_name;
    int suites_index;
    int test_num;
    unsigned int consum_tick;
};

struct test_suites_cache
{
    struct test_suites* suites;
    int suites_cnt;
    unsigned int test_cnt;
};

struct uint_test_cache
{
    const struct uint_test** test;
    int test_cnt;
};

typedef int (*iterator_call)(const struct uint_test* item);

static struct test_suites_cache suites_cache;
static struct uint_test_cache tests_cache;

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

static int mtest_cache_test_suites(const struct uint_test* item)
{
    static const struct uint_test* last_item = NULL;
    static int suites_index = 0, cur_index = 0;
    if (last_item == NULL)
    {
        suites_cache.suites[0].test_num = 1;
        suites_cache.suites[0].suites_name = item->name;
        suites_cache.suites[0].suites_index = 0;
        suites_cache.suites_cnt = 1;
    }
    else if (!strcmp(last_item->name, item->name))
    {
        suites_cache.suites[suites_index].test_num++;
    }
    else
    {
        suites_index += 1;
        suites_cache.suites[suites_index].test_num = 1;
        suites_cache.suites[suites_index].suites_name = item->name;
        suites_cache.suites[suites_index].suites_index = cur_index;
        suites_cache.suites_cnt++;
    }
    tests_cache.test[cur_index] = item;

    cur_index++;
    last_item = item;

    return 0;
}

static int mtest_cache_tests(const struct uint_test* item)
{
    static const struct uint_test* last_item = NULL;
    if (last_item == NULL)
        suites_cache.suites_cnt = 1;
    else if (strcmp(last_item->name, item->name))
        suites_cache.suites_cnt++;
    last_item = item;
    tests_cache.test_cnt++;
    suites_cache.test_cnt++;
    return 0;
}

static void mtest_prepare(void)
{
    static const struct uint_test* mtest_begin_object;
    static const struct uint_test* mtest_end_object;
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
    mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_cache_tests);
    suites_cache.suites = MTEST_MALLOC(suites_cache.suites_cnt * sizeof(struct test_suites));
    tests_cache.test = MTEST_MALLOC(tests_cache.test_cnt * sizeof(struct uint_test*));
    if (suites_cache.suites && tests_cache.test)
    {
        memset(suites_cache.suites, 0, suites_cache.suites_cnt * sizeof(struct test_suites));
        memset(tests_cache.test, 0, tests_cache.test_cnt * sizeof(struct uint_test*));
        mtest_section_iterator(mtest_begin_object, mtest_end_object, mtest_cache_test_suites);
    }
    else
    {
        MTEST_PRINT_COLOR(RED, "Mtest prepare error!!!\n");
        MTEST_FREE(tests_cache.test);
    }

    prepared = 1;
}

static int mtest_run_suites(const char* name, int count)
{
    int i, res;
    unsigned int start, consum_tick;
    struct test_suites* suites = NULL;
    for (i = 0; i < suites_cache.suites_cnt; i++)
    {
        if (!strcmp(name, suites_cache.suites[i].suites_name))
        {
            suites = &suites_cache.suites[i];
            break;
        }
    }

    while (suites && count--)
    {
        MTEST_PRINT_NORMOL("[==========] Running %d tests from %s.\n", suites->test_num, suites->suites_name);
        for (i = suites->suites_index; i < suites->suites_index + suites->test_num; i++)
        {
            MTEST_PRINT_NORMOL("[ RUN      ] %s.%s.\n", tests_cache.test[i]->name, tests_cache.test[i]->desc);
            start = MTEST_GET_TICK;
            res = tests_cache.test[i]->test_entry();
            consum_tick = MTEST_GET_TICK - start;
            if (!res)
            {
                MTEST_PRINT_NORMOL("[       OK ] %s.%s. (%d tick).\n", tests_cache.test[i]->name, tests_cache.test[i]->desc, consum_tick);
            }
            else
            {
                MTEST_PRINT_ERROR("[  FAILED  ] %s.%s (%d tick).\n", tests_cache.test[i]->name, tests_cache.test[i]->desc, consum_tick);
            }
            suites->consum_tick += consum_tick;
        }
        MTEST_PRINT_NORMOL("[==========] Running %d tests from %s (%d tick total).\n", suites->test_num, suites->suites_name, suites->consum_tick);
        suites->consum_tick = 0;
    }

    return suites ? 0 : -1;
}

static int mtest_run_all(int count)
{
    int i, res;
    unsigned int start, consum_tick;
    static int index = 0, end = 0;
    while (count--)
    {
        MTEST_PRINT_NORMOL("[==========] Running %d tests from %d test suites.\n", suites_cache.test_cnt, suites_cache.suites_cnt);
        for (i = 0; i < suites_cache.suites_cnt; i++)
        {
            end += suites_cache.suites[i].test_num;
            MTEST_PRINT_NORMOL("[----------] %d test from %s.\n", suites_cache.suites[i].test_num, suites_cache.suites[i].suites_name);
            for (; index < end; index++)
            {
                MTEST_PRINT_NORMOL("[ RUN      ] %s.%s.\n", tests_cache.test[index]->name, tests_cache.test[index]->desc);
                start = MTEST_GET_TICK;
                res = tests_cache.test[i]->test_entry();
                consum_tick = MTEST_GET_TICK - start;
                if(!res)
                {
                    MTEST_PRINT_NORMOL("[       OK ] %s.%s. (%d tick).\n", tests_cache.test[index]->name, tests_cache.test[index]->desc, consum_tick);
                }
                else
                {
                    MTEST_PRINT_ERROR("[  FAILED  ] %s.%s (%d tick).\n", tests_cache.test[i]->name, tests_cache.test[i]->desc, consum_tick);
                }
                suites_cache.suites[i].consum_tick += consum_tick;
            }
            MTEST_PRINT_NORMOL("[----------] %d tests from %s (%d tick total).\n", suites_cache.suites[i].test_num, suites_cache.suites[i].suites_name, suites_cache.suites[i].consum_tick);
            suites_cache.suites[i].consum_tick = 0;
        }
        end = index = 0;
    }

    return 0;
}

int mtest_run(const char* name, int count)
{
    mtest_prepare();
    return name ? mtest_run_suites(name, count) : mtest_run_all(count);
}

void mtest_list(void)
{
    int i = 0;
    mtest_prepare();
    MTEST_PRINT_COLOR(BLUE, "------------------------ testcase -------------------------\n");
    MTEST_PRINT_COLOR(BLUE, "< have %d tests from %d test suites:\n", suites_cache.test_cnt, suites_cache.suites_cnt);

    for (; i < suites_cache.suites_cnt; i++)
    {
        MTEST_PRINT_COLOR(BLUE, "< %s:", suites_cache.suites[i].suites_name);
        for (int j = suites_cache.suites[i].suites_index; j < suites_cache.suites[i].suites_index + suites_cache.suites[i].test_num; j++)
        {
            MTEST_PRINT_COLOR(BLUE, " %s", tests_cache.test[j]->desc);
        }
        MTEST_PRINT_COLOR(BLUE, " >\n");
    }
    MTEST_PRINT_COLOR(BLUE, "-----------------------------------------------------------\n");
}