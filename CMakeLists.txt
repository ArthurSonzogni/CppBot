# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 2.8.11)
project(test)


# ┌──────────────────────────────────────────────────────────────────┐
# │  Linux Library                                                   |
# └──────────────────────────────────────────────────────────────────┘
if(UNIX)
    set(LIB_DIR lib/linux)
    find_package(X11 REQUIRED)
    set(NEEDED_LIBS     "${NEEDED_LIBS}${X11_LIBRARIES}"  )
    set(NEEDED_INCLUDES "${NEEDED_INCLUDES} ${X11_INCLUDE_DIR}")
elseif(WIN32)
    set(LIB_DIR lib/windows)
elseif(APPLE)
    set(LIB_DIR lib/macos)
else()
    message(FATAL_ERROR "You system is not supported")
endif()

file(GLOB_RECURSE libs ${LIB_DIR}/*.cpp)
add_library (CPPBot ${libs})
target_include_directories(CPPBot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Install library                                                 |
# └──────────────────────────────────────────────────────────────────┘

INSTALL(TARGETS CPPBot
    DESTINATION "lib"
)

INSTALL(FILES include/CPPBot
    DESTINATION "include"
)

# ┌──────────────────────────────────────────────────────────────────┐
# │  test                   
# └──────────────────────────────────────────────────────────────────┘

include_directories(include)
add_executable(test test/test.cpp)
target_link_libraries (test LINK_PUBLIC CPPBot ${NEEDED_LIBS})
include_directories(${NEEDED_INCLUDES})

# ┌──────────────────────────────────────────────────────────────────┐
# │  make run (command)                                              │ 
# └──────────────────────────────────────────────────────────────────┘
add_custom_target(run
    COMMAND ./test
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

