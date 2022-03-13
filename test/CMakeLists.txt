cmake_minimum_required(VERSION 3.10)
project(generator_tests)

find_package(GTest REQUIRED)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} generator)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
