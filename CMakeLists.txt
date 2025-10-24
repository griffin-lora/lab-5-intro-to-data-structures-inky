cmake_minimum_required(VERSION 3.22.0)
project(lab5-intro-to-data-structures)

set(CMAKE_CXX_STANDARD 20)

# 3504 Flags
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wextra -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(/usr/include/)

file(GLOB MAIN_SRCS *.cpp *.hpp)

set(GRADESCOPE_SRCS ${MAIN_SRCS})

# excludes main.cpp from compilation
list(REMOVE_ITEM GRADESCOPE_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")


add_executable(RunMain
        ${MAIN_SRCS}
)
# adds back main.cpp by defining MAIN with -DMAIN in the compilation line
target_compile_definitions(RunMain PRIVATE MAIN)

