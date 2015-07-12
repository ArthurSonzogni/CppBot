# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘
cmake_minimum_required(VERSION 2.8.11)
project(test)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Find the CPPBot library                                         |
# └──────────────────────────────────────────────────────────────────┘
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(CPPBOT)

if(NOT CPPBOT_FOUND)
    message(FATAL_ERROR "I can't find the library, do you have builded and install the library ? (ie : make install in the main directory)")
endif()


# ┌──────────────────────────────────────────────────────────────────┐
# │  Source file                                                     │
# └──────────────────────────────────────────────────────────────────┘

include_directories(src)
add_executable(test src/main.cpp)
target_link_libraries(test ${CPPBOT_LIBRARIES})
include_directories(${CPPBOT_INCLUDE_DIRS})

