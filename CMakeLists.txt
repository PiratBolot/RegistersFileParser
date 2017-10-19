project(RegisterFileParser)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    set(MAIN_CPP_FNAME "converter_windows.cpp" )
else()
    set(MAIN_CPP_FNAME "converter_linux.cpp" )
endif()

set(SOURCE_FILES Sources/RegisterFileConverter.cpp Headers/RegisterFileConverter.h Sources/RegisterFileParser.cpp Headers/RegisterFileParser.h converter_windows.cpp converter_linux.cpp)
add_executable(RegisterFileParser ${SOURCE_FILES})
