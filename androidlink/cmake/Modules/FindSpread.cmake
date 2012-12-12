# - Find the Spread Toolkit
# This module defines:
#  SPREAD_INCLUDE_DIRS, where to find sp.h, etc.
#  SPREAD_LIBRARIES, the libraries needed to use spread.
#  SPREAD_EXECUTABLE, the spread daemon executable.
#
# Will react on:
#  SPREAD_ROOT, additional directory to search for spread
#  SPREAD_USE_STATIC, if enabled, search for static lib instead of shared, default OFF
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

FIND_PATH(SPREAD_INCLUDE_DIRS
          NAMES sp.h
          PATHS "${SPREAD_ROOT}/include"
                "$ENV{HOME}/include")

FIND_PROGRAM(SPREAD_EXECUTABLE
             NAMES spread
             PATHS "${SPREAD_ROOT}/sbin"
                   "${SPREAD_ROOT}/bin"
                   "sbin")

SET(SPREAD_LIBNAME "libspread${CMAKE_SHARED_LIBRARY_SUFFIX}")
IF(SPREAD_USE_STATIC)
    SET(SPREAD_LIBNAME "libspread${CMAKE_STATIC_LIBRARY_SUFFIX}")
ENDIF()

MESSAGE(STATUS "Searching for spread library with name ${SPREAD_LIBNAME}")

FIND_LIBRARY(SPREAD_LIBRARIES
             NAMES ${SPREAD_LIBNAME}
             PATHS "${SPREAD_ROOT}/lib"
                   "${SPREAD_ROOT}/bin"
                   "$ENV{HOME}/lib")

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Spread DEFAULT_MSG SPREAD_LIBRARIES SPREAD_INCLUDE_DIRS SPREAD_EXECUTABLE)

MARK_AS_ADVANCED(SPREAD_INCLUDE_DIRS SPREAD_LIBNAME SPREAD_LIBRARIES SPREAD_EXECUTABLE)
