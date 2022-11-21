cmake_minimum_required(VERSION 3.23)
project(proxycpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(proxycpp main.cpp src/proxysocket.h)


target_include_directories(${PROJECT_NAME} PRIVATE src)

