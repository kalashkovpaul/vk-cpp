cmake_minimum_required(VERSION 3.16)
project(homework_1_5)
enable_language(C)
enable_language(CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(LIB_SOURCE_FILES src/letter.c)
set(LIB_HEADERS_FILES inc/letter.h inc/constants.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")

add_library(letter STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})
include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(app src/main.c)
target_link_libraries(app letter)

add_compile_options("--coverage")
add_link_options("--coverage")

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}/inc/)
add_executable(letterTest unit_tests/testLetter.cpp)
target_link_libraries(letterTest ${GTEST_LIBRARIES} letter)