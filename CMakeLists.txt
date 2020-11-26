cmake_minimum_required(VERSION 3.8)
project(MD5)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c md5.c md5.h)
add_executable(MD5 ${SOURCE_FILES} md5.c md5.h)