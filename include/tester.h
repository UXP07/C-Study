#pragma once
// 练习自检工具：把验收标准写成断言，机器判定 PASS/FAIL
// 用法：
//   CHECK(cond);                     条件为真则通过
//   CHECK_EQ_INT(actual, expect);    整数相等则通过，失败时打印两值
//   CHECK_EQ_STR(actual, expect);    字符串相等则通过
//   CHECK_NEAR(actual, expect, tol); 浮点差值不超过 tol 则通过
//   main 末尾 return tester_summary();  全部通过返回 0，否则返回 1
// 计数器为 static：断言与 tester_summary() 须在同一 .c 文件（练习默认单 main.c）
#include <stdio.h>
#include <string.h>

// MinGW 的 msvcrt printf 不支持 %lld 等 C99 格式：MinGW 下改用其自带的 C99 兼容实现
#if defined(__MINGW32__) || defined(__MINGW64__)
#define tester_printf __mingw_printf
#else
#define tester_printf printf
#endif

static int tester_checks = 0;
static int tester_failures = 0;

static void tester_report(int ok, const char* expr, const char* file, int line)
{
    ++tester_checks;
    if (!ok) {
        ++tester_failures;
        tester_printf("  [FAIL] %s:%d  %s\n", file, line, expr);
    }
}

static int tester_summary(void)
{
    if (tester_failures == 0) {
        tester_printf("[PASS] %d checks passed\n", tester_checks);
        return 0;
    }
    tester_printf("[FAIL] %d/%d checks failed\n", tester_failures, tester_checks);
    return 1;
}

#define CHECK(cond) tester_report(!!(cond), #cond, __FILE__, __LINE__)

#define CHECK_EQ_INT(actual, expected)                                    \
    do {                                                                  \
        long long a_ = (long long)(actual);                               \
        long long e_ = (long long)(expected);                             \
        int ok_ = (a_ == e_);                                             \
        tester_report(ok_, #actual " == " #expected, __FILE__, __LINE__); \
        if (!ok_)                                                         \
            tester_printf("      actual: %lld  expected: %lld\n", a_, e_);       \
    } while (0)

#define CHECK_EQ_STR(actual, expected)                                    \
    do {                                                                  \
        const char* a_ = (actual);                                        \
        const char* e_ = (expected);                                      \
        int ok_ = (a_ != NULL && e_ != NULL && strcmp(a_, e_) == 0);      \
        tester_report(ok_, #actual " == " #expected, __FILE__, __LINE__); \
        if (!ok_)                                                         \
            tester_printf("      actual: %s  expected: %s\n",                    \
                   a_ != NULL ? a_ : "(null)", e_ != NULL ? e_ : "(null)"); \
    } while (0)

#define CHECK_NEAR(actual, expected, tol)                                 \
    do {                                                                  \
        double a_ = (double)(actual);                                     \
        double e_ = (double)(expected);                                   \
        double d_ = a_ - e_;                                              \
        if (d_ < 0) d_ = -d_;                                             \
        int ok_ = (d_ <= (double)(tol));                                  \
        tester_report(ok_,                                                \
                      #actual " ~= " #expected " (tol " #tol ")",         \
                      __FILE__, __LINE__);                                \
        if (!ok_)                                                         \
            tester_printf("      actual: %g  expected: %g\n", a_, e_);           \
    } while (0)
