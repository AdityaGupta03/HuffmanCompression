cmake_minimum_required(VERSION 3.20)

project(FileCompression)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileCompression ./src/FileCompression.cpp
        src/FrequencyTable.cpp
        src/FrequencyTable.h)
