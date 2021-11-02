add_library(static_differences STATIC src/static_differences.c)

target_include_directories(static_differences PUBLIC inc)

add_subdirectory(unit_tests)