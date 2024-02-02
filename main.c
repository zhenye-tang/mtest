#include <stdio.h>
#include "mtest.h"

int main(int argc, char *argv[])
{
    mtest_list();
    mtest_run("xx_module", 1);
    return 0;
}