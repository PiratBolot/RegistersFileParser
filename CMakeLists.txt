cmake_minimum_required(VERSION 3.8)
project(RegisterFileParser)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Sources/RegisterFileConverter.cpp Headers/RegisterFileConverter.h Sources/RegisterFileParser.cpp Headers/RegisterFileParser.h converter_windows.cpp converter_linux.cpp)
add_executable(RegisterFileParser ${SOURCE_FILES})