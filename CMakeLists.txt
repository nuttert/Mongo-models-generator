cmake_minimum_required(VERSION 3.5)
project(generator)

option(GENERATE "Generate models, collections, configs." ON)
option(BUILD_TESTING "Build unit tests." ON)

if (GENERATE)
  execute_process(COMMAND bash "-c" "${CMAKE_CURRENT_SOURCE_DIR}/generators/generate.sh '${CMAKE_CURRENT_SOURCE_DIR}' '${CMAKE_BINARY_DIR}'"
    RESULT_VARIABLE CMD_ERROR
    OUTPUT_VARIABLE CMD_OUTPUT)
  MESSAGE( STATUS "CMD_ERROR:" )
  MESSAGE( STATUS ${CMD_OUTPUT})
endif()

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# Set default build type to debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#detect build type
if (${CMAKE_BUILD_TYPE} MATCHES "[dD][eE][bB][uU][gG]")
    message("Build CORE project in debug mode")
    add_definitions(-D_DEBUG)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Werror -fpermissive -Wno-invalid-offsetof -Wno-unused-function -Wno-strict-aliasing -Wno-deprecated-declarations")
    add_definitions(-fno-deduce-init-list  -fPIC  -fno-omit-frame-pointer)
    add_definitions(-ggdb -DDEBUG_ON -fsanitize=address -fsanitize=undefined -fsanitize-recover=all -fstack-protector-all)
    add_link_options(-fsanitize=address -fsanitize=undefined)
else()
    message("Build CORE project in release mode")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB MODELS_LIST
  ${CMAKE_BINARY_DIR}/codegen/Models/*.cpp)
file(GLOB CONFIGS_LIST
  ${CMAKE_BINARY_DIR}/codegen/Configs/*.cpp)
file(GLOB CONFIGS_MODELS_LIST
  ${CMAKE_BINARY_DIR}/codegen/Configs/models/*.cpp)

add_library(
  generator 
  ${CMAKE_SOURCE_DIR}/json/base-model.cpp

  ${CMAKE_SOURCE_DIR}/configs/config_interface.cc

  ${CMAKE_SOURCE_DIR}/databases/mongodb/client.cc
  ${CMAKE_SOURCE_DIR}/databases/mongodb/manager.cc

  ${MODELS_LIST}
  ${CONFIGS_MODELS_LIST}
  ${CONFIGS_LIST}
)


find_package(GTest REQUIRED)
find_package(Threads REQUIRED) 
find_package(Poco REQUIRED Foundation) 
find_package(Boost 1.67 REQUIRED)
find_package(fmt REQUIRED)

  
target_include_directories(generator PUBLIC 
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_BINARY_DIR}/codegen ./
)

target_link_libraries(generator 
    ${GTEST_BOTH_LIBRARIES} 
    ${Boost_BOTH_LIBRARIES} 
    fmt
)

# Mongo
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")
target_link_libraries(${PROJECT_NAME} mongo::bsoncxx_shared mongo::mongocxx_shared)
#

if (BUILD_TESTING)
    add_subdirectory(test)
    include_directories(test)
endif()
