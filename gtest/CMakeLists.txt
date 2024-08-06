cmake_minimum_required(VERSION 3.10)
project(GTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} test.cpp ${SRC_DIR}/curl.cpp ${SRC_DIR}/jsoncpp.cpp ${SRC_DIR}/verify.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SRC_DIR}/include/custom)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SRC_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} GTest::gtest GTest::gtest_main pthread CURL::libcurl OpenSSL::Crypto OpenSSL::SSL)


