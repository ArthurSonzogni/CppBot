# - Try to find CPPBOT
# Once done this will define
#  CPPBOT_FOUND - System has CPPBOT
#  CPPBOT_INCLUDE_DIRS - The CPPBOT include directories
#  CPPBOT_LIBRARIES - The libraries needed to use CPPBOT

find_path(CPPBOT_INCLUDE_DIR CPPBot)
find_library(CPPBOT_LIBRARY NAMES CPPBot)


set(CPPBOT_LIBRARIES ${CPPBOT_LIBRARY} )
set(CPPBOT_INCLUDE_DIRS ${CPPBOT_INCLUDE_DIR} )
    #set(CPPBOT_LIBRARIES"${CPPBOT_LIBRARIES} ${X11_LIBRARIES}"  )
    #set(CPPBOT_INCLUDE_DIR "${CPPBOT_INCLUDE_DIR} ${X11_INCLUDE_DIR}")

if(UNIX)
    set(LIB_DIR lib/linux)
    find_package(X11 REQUIRED)
    set(NEEDED_LIBS     "${NEEDED_LIBS} ${X11_LIBRARIES}"  )
    set(NEEDED_INCLUDES "${NEEDED_INCLUDES} ${X11_INCLUDE_DIR}")
elseif(WIN32)
    set(LIB_DIR lib/windows)
elseif(APPLE)
    set(LIB_DIR lib/macos)
else()
    message(FATAL_ERROR "You system is not supported")
endif()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CPPBOT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CPPBOT  DEFAULT_MSG
    CPPBOT_LIBRARIES CPPBOT_INCLUDE_DIRS)

mark_as_advanced(CPPBOT_INCLUDE_DIRS CPPBOT_LIBRARIES )
