// 练习 00 —— 工作区自检（非学习题，tester.h 的自检与目录模板）
// 正常构建运行应输出 [PASS]；想看 FAIL 的输出长什么样，
// 把下面任一断言改成错误值（如 CHECK_EQ_INT(2 * 21, 43)）再重新编译运行即可。
#include <stdio.h>

#include "tester.h"

int main(void)
{
    CHECK(1 + 1 == 2);
    CHECK_EQ_INT(2 * 21, 42);

    char buf[32];
    snprintf(buf, sizeof buf, "%s world", "hello");
    CHECK_EQ_STR(buf, "hello world");

    CHECK_NEAR(3.14159, 3.14159, 1e-6);

    return tester_summary();
}
