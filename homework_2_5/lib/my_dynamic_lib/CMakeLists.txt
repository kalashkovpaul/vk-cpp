add_library(dynamic_differences SHARED src/dynamic_differences.c)

target_include_directories(dynamic_differences PUBLIC inc)

#add_subdirectory(unit_tests)