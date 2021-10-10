cmake_minimum_required(VERSION 3.16)
project(homework_1_5)
enable_language(C)
enable_language(CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


if ("${TARGET_CPU}" STREQUAL "amd64")
    set (CMAKE_SIZEOF_VOID_P 8)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS TRUE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS FALSE)
elseif ("${TARGET_CPU}" STREQUAL "x86")
    set (CMAKE_SIZEOF_VOID_P 4)

    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
    set_property (GLOBAL PROPERTY FIND_LIBRARY_USE_LIB32_PATHS TRUE)

    if (GCC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
        set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32")
    endif ()
else ()
    message (FATAL_ERROR "Unsupported CPU: ${TARGET_CPU}")
endif ()

set(LIB_SOURCE_FILES src/letter.c)
set(LIB_HEADERS_FILES inc/letter.h inc/constants.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")

add_compile_options("--coverage")
add_link_options("--coverage")

add_library(letter STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})
include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(app src/main.c)
target_link_libraries(app letter)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}/inc/)
add_executable(letterTest unit_tests/testLetter.cpp)
target_link_libraries(letterTest ${GTEST_LIBRARIES} letter)
