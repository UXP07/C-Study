# exercises — 练习题

一题一目录，目录名即可执行文件名（两位编号 + 主题，如 `01_pointer_basics`）。

## test/ —— 学习草稿区

`test/` 不是正式练习：学习时随手试验代码的地方，**不参与构建、不参与验收、不记录进度**。
约定只保留一个 `main.c`（当前试验），有价值的试验建议自行整理进笔记。
草稿已被 CMake 排除在构建外（写错不挡正式练习）；手动编译（在 test/ 内）：
```
gcc -Wall -Wextra -std=c11 main.c -o main && ./main
```

## 约定
- 目录内所有 `.c` 编入该练习的可执行文件（多文件练习随意加，头文件也放本目录）
- 题目在 `REQUIREMENT.md`（出题产出：背景、需求、验收标准、简答题）
- 验收标准写成 `include/tester.h` 的 `CHECK` / `CHECK_EQ_INT` / `CHECK_EQ_STR` / `CHECK_NEAR` 断言
- 跨练习的公共代码放根目录 `include/`
- `00_selfcheck` 是 tester.h 的自检示例，可当作练习目录的模板

## 构建与运行（单题）
```
cmake --preset default
cmake --build --preset default --target 01_pointer_basics
./build/bin/01_pointer_basics.exe
```
Linux（WSL2）下用 `--preset linux`，产物同名无 `.exe` 后缀：
```
cmake --preset linux
cmake --build --preset linux --target 01_pointer_basics
./build/bin/01_pointer_basics
```

新建子目录即自动纳入构建（CMakeLists.txt 自动发现），无需改任何配置。
