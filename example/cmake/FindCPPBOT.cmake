# - Try to find CPPBOT
# Once done this will define
#  CPPBOT_FOUND - System has CPPBOT
#  CPPBOT_INCLUDE_DIRS - The CPPBOT include directories
#  CPPBOT_LIBRARIES - The libraries needed to use CPPBOT

find_path(CPPBOT_INCLUDE_DIR CPPBot)
find_library(CPPBOT_LIBRARY NAMES CPPBot)


if(UNIX)
    find_package(X11 REQUIRED)
    set(NEEDED_LIB     "${NEEDED_LIB};${X11_LIBRARIES}"  )
    set(NEED_INC       "${NEED_INC};${X11_INCLUDE_DIR}")
elseif(WIN32)
    # Nothing until now
elseif(APPLE)
    # Nothing until now
else()
    message(FATAL_ERROR "You system is not supported")
endif()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CPPBOT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CPPBOT  DEFAULT_MSG
    CPPBOT_LIBRARY CPPBOT_INCLUDE_DIR NEEDED_LIB NEED_INC)

set(CPPBOT_LIBRARIES "${CPPBOT_LIBRARY};${NEEDED_LIB}")
set(CPPBOT_INCLUDE_DIRS "${CPPBOT_INCLUDE_DIR};${NEED_INC}")

mark_as_advanced(CPPBOT_INCLUDE_DIRS CPPBOT_LIBRARIES )
