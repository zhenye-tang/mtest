# Mtest

## 介绍
Mtest (micro testcase) 是一个占用资源小的单元测试框架，兼容 gtest

## 目录结构

```
mtest
├─── examples							// 示例
|       |———0.lds                       // gcc 链接脚本
|       |———CMakeLists.txt              // cmake 文件
|       └───testcase_0.c                // 单元测试示例
├─── src                                // mtest 源码
|     |———mtest.c                       // mtest 源文件
|     |———mtest.h                       // mtest 头文件
|     └───CMakeLists.txt                // cmake 文件
├─── CMakeLists.txt						// cmake 文件
├─── SConscript                         // scons 文件
└─── README.md                          // 软件说明文件
```

## API 介绍
### 运行单元测试
`int mtest_run(const char *name, int count)`

该接口用于运行指定或所有的单元测试

| 参数      | 描述                     |
| :-------- | :----------------------- |
| name |   单元测试名称，传入 NULL 则运行所有单元测试    |
| **返回**  | **描述**                 |
|    0   |  运行成功               |
| != 0    | 运行失败               |

### 列出所有单元测试
`void mtest_list(void)`

该接口会将所有的测试用例打印出来

## 判定宏介绍

| 名称             | 介绍 |
| ---------------- | ---- |
| EXPECT_STREQ(s1, s2) |  字符串 s1 等于 s2    |
| EXPECT_STRNE(s1, s2)     |    字符串 s1 不等于 s2  |
| EXPECT_STRCASEEQ(s1, s2)     |  字符串 s1 等于 s2, 不区分大小写    |
| EXPECT_STRCASENE(s1, s2) |  字符串 s1 不等于 s2, 不区分大小写    |
| EXPECT_EQ(val1, val2) |  数字 val1  等于  val2   |
| EXPECT_NE(val1, val2)        |  数字 val1  不等于  val2    |
| EXPECT_LE(val1, val2)        |  数字 val1  小于等于  val2    |
| EXPECT_LT(val1, val2)        |  数字 val1  小于  val2    |
| EXPECT_GE(val1, val2)        |  数字 val1  大于等于  val2    |
| EXPECT_GT(val1, val2)        |  数字 val1  大于  val2    |
| EXPECT_END()        |   测试用例结尾（必须放到结尾，可参考 examples 下的示例文件）   |

## 编译示例

在本软件根目录下，执行如下命令：
```
mkdir build
cd build
cmake .. && cmake --build .
cd bin
./example
```

输出如下：
```
------------------------ testcase -------------------------
< have 7 tests from 4 test suites:
< xx_module: connect_test disconnect_test open_test >
< gaga: xxx www >
< kaka: www >
< gugu: www >
-----------------------------------------------------------
[==========] Running 3 tests from xx_module.
[ RUN      ] xx_module.connect_test.
/home/null/mtest/examples/testcase_0.c:13.
[  FAILED  ] xx_module.connect_test (0 tick).
[ RUN      ] xx_module.disconnect_test.
[       OK ] xx_module.disconnect_test. (0 tick).
[ RUN      ] xx_module.open_test.
/home/null/mtest/examples/testcase_0.c:31.
[  FAILED  ] xx_module.open_test (0 tick).
[==========] Running 3 tests from xx_module (0 tick total).
```