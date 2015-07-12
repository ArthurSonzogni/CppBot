# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 2.8.11)
project(test)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Find the CPPBot library                                         |
# └──────────────────────────────────────────────────────────────────┘
find_library(CppBot_Lib NAMES CppBot)
find_path(CppBot_Include CPPBot.hpp)

if(NOT CppBot_Lib OR NOT CppBot_Include)
    message(FATAL_ERROR "I can't find the library, do you have builded and install the library ? (ie : make install in the main directory)")
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

include_directories(src)
add_executable(test src/main.cpp)
target_link_libraries(test ${CppBot_Lib})
include_directories(${CppBot_Include})

