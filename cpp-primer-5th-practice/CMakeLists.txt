cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(CppPrimer5th LANGUAGES CXX)

set(CXX_STANDARD C++17) # 使用 C++ 17 标准
set(CXX_EXTENSIONS OFF)  # 只启用 ISO C++ 标准的编译器标志，不使用特定编译器的扩展
set(CXX_STANDARD_REQUIRED ON) # C++17 不可用就让 CMake 停止工作

add_subdirectory(chap01)