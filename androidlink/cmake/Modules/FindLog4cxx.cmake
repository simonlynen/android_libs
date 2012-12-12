# - Try to find the log4cxx logging library
# Will define:
#
# LOG4CXX_INCLUDE_DIRS - include directories needed to use the library
# LOG4CXX_LIBRARIES - Libraries to link agains fpr the driver
#
# Possible hints:
# LOG4CXX_VISUAL_STUDIO_PROJECT - root directory of the log4cxx visual studio project on windows
#
# Copyright (C) 2010 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
#
# This program is free software; you can redistribute it
# and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation;
# either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

INCLUDE(FindPackageHandleStandardArgs)

# use pkg-config as a hint if available
INCLUDE(FindPkgConfig)
IF(PKG_CONFIG_FOUND)
    PKG_CHECK_MODULES(PKG liblog4cxx)
ENDIF()

FIND_PATH(LOG4CXX_INCLUDE_DIRS
          HINTS ${LOG4CXX_VISUAL_STUDIO_PROJECT}/src/main/include
                ${PKG_INCLUDE_DIRS}
          NAMES logger.h
          PATH_SUFFIXES log4cxx)

FIND_LIBRARY(LOG4CXX_LIBRARIES
             HINTS ${LOG4CXX_VISUAL_STUDIO_PROJECT}/projects/Debug
                   ${LOG4CXX_VISUAL_STUDIO_PROJECT}/projects/Release
                   ${PKG_LIBRARY_DIRS}
             NAMES log4cxx)
             
# post-process inlude path
IF(LOG4CXX_INCLUDE_DIRS)
    STRING(REGEX REPLACE log4cxx$$ "" LOG4CXX_INCLUDE_DIRS ${LOG4CXX_INCLUDE_DIRS})
    SET(LOG4CXX_INCLUDE_DIRS ${LOG4CXX_INCLUDE_DIRS} CACHE PATH "log4cxx include dirs" FORCE)
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Log4cxx DEFAULT_MSG LOG4CXX_INCLUDE_DIRS LOG4CXX_LIBRARIES)

# only visible in advanced view
MARK_AS_ADVANCED(LOG4CXX_INCLUDE_DIRS LOG4CXX_LIBRARIES)
