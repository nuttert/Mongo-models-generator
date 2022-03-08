cmake_minimum_required(VERSION 3.5)
project(test)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++20
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Werror -fpermissive -Wno-invalid-offsetof -Wno-unused-function -Wno-strict-aliasing -Wno-deprecated-declarations")
add_definitions(-fno-deduce-init-list  -fPIC  -fno-omit-frame-pointer)
add_definitions(-ggdb -DDEBUG_ON -fsanitize=address -fsanitize=undefined -fsanitize-recover=all -fstack-protector-all)
add_link_options(-fsanitize=address -fsanitize=undefined)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED) 
find_package(Poco REQUIRED Foundation) 
find_package(Boost 1.67 REQUIRED)
find_package(fmt REQUIRED)

file(GLOB MODELS_LIST
  ${CMAKE_SOURCE_DIR}/build/codegen/Models/*.cpp)
file(GLOB CONFIGS_LIST
  ${CMAKE_SOURCE_DIR}/build/codegen/Configs/*.cpp)
file(GLOB CONFIGS_MODELS_LIST
  ${CMAKE_SOURCE_DIR}/build/codegen/Configs/models/*.cpp)


add_executable(
  test 
  ${CMAKE_SOURCE_DIR}/main.cpp
  ${CMAKE_SOURCE_DIR}/json/base-model.cpp

  ${CMAKE_SOURCE_DIR}/configs/config_interface.cc

  ${CMAKE_SOURCE_DIR}/databases/mongodb/client.cc
  ${CMAKE_SOURCE_DIR}/databases/mongodb/manager.cc

  ${MODELS_LIST}
  ${CONFIGS_MODELS_LIST}
  ${CONFIGS_LIST}
)

  
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR} build/codegen ./)

target_link_libraries(test 
    ${GTEST_BOTH_LIBRARIES} 
    ${Boost_BOTH_LIBRARIES} 
    fmt
)

##########
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
##########
