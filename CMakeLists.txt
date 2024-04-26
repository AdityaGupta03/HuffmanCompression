cmake_minimum_required(VERSION 3.20)
project(FileCompression)
set(CMAKE_CXX_STANDARD 20)
add_executable(FileCompression
    ./src/main.cpp
    ./src/FileCompression.cpp
    ./src/FileCompression.h
)
