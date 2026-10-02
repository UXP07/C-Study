cmake_minimum_required(VERSION 3.20)
project(project01 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 可执行文件输出目录：Debug -> build/bin，Release -> build/bin-release（互不覆盖）
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin-release)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
endif()

add_compile_options(-Wall -Wextra)

# 自动发现练习：exercises/ 下每个子目录是一个练习（目录名即可执行文件名），
# 目录内全部 .c 编入该练习——新建目录即自动纳入构建，无需改本文件
# test/ 为草稿区，排除在构建外（草稿写错不阻塞正式练习）
file(GLOB EXERCISE_DIRS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/exercises/*)
foreach(dir ${EXERCISE_DIRS})
    if(IS_DIRECTORY ${dir})
        get_filename_component(topic ${dir} NAME)
        if(NOT topic STREQUAL "test")
            file(GLOB topic_sources CONFIGURE_DEPENDS ${dir}/*.c)
            if(topic_sources)
                add_executable(${topic} ${topic_sources})
                target_include_directories(${topic} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
            endif()
        endif()
    endif()
endforeach()
