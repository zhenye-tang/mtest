#ifndef __MTEST_H__
#define __MTEST_H__
#include <string.h>

struct uint_test
{
    const char* name;
    const char* desc;
    void (*test_entry)(void);
};

#pragma section("Mtest$f",read)

#define MTEST_PRINTF                printf

#define MTEST_PRINT_OK(...)        MTEST_PRINTF("\033[32m"); \
        MTEST_PRINTF(__VA_ARGS__); MTEST_PRINTF("\033[0m\n");

#define MTEST_PRINT_ERROR(...)     MTEST_PRINTF("\033[31m"); \
        MTEST_PRINTF(__VA_ARGS__); MTEST_PRINTF("\033[0m\n");

#define TO_STRINGI(x) #x
#define STRING(s) TO_STRINGI(s)

#define TEST(name, desc) \
    static void name##desc##_entry(void);\
    __declspec(allocate("Mtest$f")) \
    const struct uint_test _mtest##name##desc__ =             \
        {STRING(name), STRING(desc), name##desc##_entry};   \
    static void name##desc##_entry(void)
#pragma comment(linker, "/merge:Mtest=mytext") \

#define EXPECT_STR_COMPARE(s1, s2, ne, cmp) \
    do {   \
        if (!cmp(s1, s2)) {                     \
            if (ne) {                           \
                MTEST_PRINT_OK("success!"); \
            } else { \
                MTEST_PRINT_ERROR("error!"); \
            } \
        } else { \
            if (!ne) { \
                MTEST_PRINT_OK("success!"); \
            } else { \
                MTEST_PRINT_ERROR("error!"); \
            } \
        } \
    }while(0)

#define EXPECT_INTERGER_COMPARE(s1, s2, ne) \
    do{ \
        if(s1 == s2) { \
            if (ne) { \
                    MTEST_PRINT_OK("success!"); \
            } else { \
                    MTEST_PRINT_ERROR("error!"); \
            }\
        } else { \
            if (!ne) { \
                    MTEST_PRINT_OK("success!"); \
            } else { \
                    MTEST_PRINT_ERROR("error!"); \
            }\
        } \
    }while(0) \

#define EXPECT_STREQ(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 1, strcmp) \

#define EXPECT_STRNE(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 0, strcmp) \

#define EXPECT_STRCASEEQ(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 1, strcasecmp) \

#define EXPECT_STRCASENE(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 0, strcasecmp) \

#define EXPECT_EQ(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, 1);

#define EXPECT_NE(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, 0);

#define EXPECT_LE(val1, val2) \

#define EXPECT_LT(val1, val2) \

#define EXPECT_GE(val1, val2) \

#define EXPECT_GT(val1, val2) \

#endif //__MTEST_H__