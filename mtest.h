#ifndef __MTEST_H__
#define __MTEST_H__
#include <string.h>

struct uint_test
{
    const char* name;
    const char* desc;
    int (*test_entry)(void);
};

#define BLACK    "30"
#define RED      "31"
#define GREEN    "32"
#define YELLOW   "33"
#define BLUE     "34"
#define PURPLE   "35"
#define CYAN     "36"
#define WHITE    "37"

#define MTEST_PRINTF                        printf

#define MTEST_PRINT_COLOR(n, ...)           MTEST_PRINTF("\033["n"m");\
              MTEST_PRINTF(__VA_ARGS__);    MTEST_PRINTF("\033[0m");

#define MTEST_PRINT_NORMOL(...)             MTEST_PRINT_COLOR(GREEN, __VA_ARGS__)
#define MTEST_PRINT_ERROR(...)              MTEST_PRINT_COLOR(RED, __VA_ARGS__)

#define TO_STRINGI(x) #x
#define STRING(s) TO_STRINGI(s)

#if defined(_MSC_VER)
#pragma section("Mtest$f",read)
#define TEST(name, desc) \
    static int _##name##desc##_entry(void);\
    __declspec(allocate("Mtest$f")) \
    const struct uint_test _mtest_##name##_##desc##_ =             \
        { STRING(name), STRING(desc), _##name##desc##_entry };   \
    static int _##name##desc##_entry(void)
#pragma comment(linker, "/merge:Mtest=mytext") 
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
#define TEST(name, desc) \
    static int _##name##desc##_entry(void); \
    __attribute((used))  const struct uint_test _mtest_##name##_##desc##_ __attribute__((section("Mtest"))) = \
    { STRING(name), STRING(desc), _##name##desc##_entry };   \
    static int _##name##desc##_entry(void)
#endif

#define MTEST_COMPARE(ne) \
    do{ \
        if (!ne) {                           \
            MTEST_PRINT_ERROR("%s:%d.\n",__FILE__, __LINE__); \
            return -1; \
        } \
    } while(0);

#define EXPECT_STR_COMPARE(s1, s2, ne, cmp) \
    do {   \
        if (!cmp(s1, s2)) {                     \
            MTEST_COMPARE(ne) \
        } else { \
            MTEST_COMPARE(!ne) \
        } \
    }while(0)

#define EXPECT_INTERGER_COMPARE(s1, s2, ops, ne) \
    do{ \
        if(s1 ops s2) { \
            MTEST_COMPARE(ne) \
        } else { \
            MTEST_COMPARE(!ne) \
        } \
    }while(0)

#define EXPECT_STREQ(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 1, strcmp)

#define EXPECT_STRNE(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 0, strcmp)

#define EXPECT_STRCASEEQ(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 1, strcasecmp)

#define EXPECT_STRCASENE(s1, s2) \
    EXPECT_STR_COMPARE(s1, s2, 0, strcasecmp)

#define EXPECT_EQ(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, ==, 1);

#define EXPECT_NE(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, ==, 0);

#define EXPECT_LE(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, <=, 1);

#define EXPECT_LT(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, <, 1);

#define EXPECT_GE(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, >=, 1);

#define EXPECT_GT(val1, val2) \
    EXPECT_INTERGER_COMPARE(val1, val2, >, 1);

#define EXPECT_END()          \
    return 0;

/**
 * @brief This function will run unit tests.
 *
 * @param name is the name of the test suite. If name is NULL, runs all test suites.
 *
 * @param count is the number of runs.
 * 
 * @return Return the operation status. ONLY When the return value is 0, the operation is successful.
 */
int mtest_run(const char *name, int count);

/**
 * @brief This function will list all test cases under the test suite.
 */
void mtest_list(void);

#endif //__MTEST_H__