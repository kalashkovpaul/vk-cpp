cmake_minimum_required(VERSION 3.8)
project(homework_2_5)
enable_language(C)
enable_language(CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CXX g++)

set(LIB_SOURCE_FILES src/create_binary_file.c)
set(LIB_HEADERS_FILES inc/create_binary_file.h inc/constants.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wvla -Iinc -Wfloat-equal -pthread -Wpedantic -Wextra")
add_compile_options("--coverage")

add_library(create_file STATIC ${LIB_SOURCE_FILES} ${LIB_HEADERS_FILES})

include_directories(${PROJECT_SOURCE_DIR}/inc)


enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(lib/my_static_lib)

add_executable(app src/main.c)

target_link_libraries(app create_file static_differences gcov)
