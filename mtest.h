#ifndef __MTEST_H__
#define __MTEST_H__
#include <string.h>

struct uint_test
{
    const char* name;
    const char* desc;
    int (*test_entry)(const char *_name, const char *_desc);
};

#pragma section("Mtest$f",read)

#define MTEST_PRINTF                printf

#define MTEST_PRINT_OK(...)        MTEST_PRINTF("\033[32m"); \
        MTEST_PRINTF(__VA_ARGS__); MTEST_PRINTF("\033[0m\n");

#define MTEST_PRINT_ERROR(...)     MTEST_PRINTF("\033[31m"); \
        MTEST_PRINTF("[%s] %s:%d", _name, __FILE__, __LINE__); \
        MTEST_PRINTF(__VA_ARGS__); MTEST_PRINTF("\033[0m\n");

#define TO_STRINGI(x) #x
#define STRING(s) TO_STRINGI(s)

#define TEST(name, desc) \
    static int _##name##desc##_entry(const char *_name, const char *_desc);\
    __declspec(allocate("Mtest$f")) \
    const struct uint_test _mtest_##name##_##desc##_ =             \
        {STRING(name), STRING(desc), _##name##desc##_entry};   \
    static int _##name##desc##_entry(const char *_name, const char *_desc)

#pragma comment(linker, "/merge:Mtest=mytext") \

#define MTEST_COMPARE(ne) \
    if (!ne) {                           \
        MTEST_PRINT_ERROR(" Failure"); \
    }\

#define EXPECT_STR_COMPARE(s1, s2, ne, cmp) \
    do {   \
        if (!cmp(s1, s2)) {                     \
            MTEST_COMPARE(ne) \
        } else { \
            MTEST_COMPARE(!ne) \
        } \
    }while(0)

#define EXPECT_INTERGER_COMPARE(s1, s2, ne) \
    do{ \
        if(s1 == s2) { \
            MTEST_COMPARE(ne) \
        } else { \
            MTEST_COMPARE(!ne) \
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

#define EXPECT_END()          \
    return 0;

#endif //__MTEST_H__