# - Find JSONCpp
#
# This module defines
#  JSONCPP_INCLUDE_DIR, where to find json.h, etc.
#  JSONCPP_LIBRARIES, the libraries needed to use jsoncpp.
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
# adapted from http://code.google.com/p/emeraldviewer/

FIND_PATH(JSONCPP_INCLUDE_DIR
          NAMES json.h
          PATHS "/usr/local/include" "/usr/include"
          PATH_SUFFIXES jsoncpp json)

# post-process inlude path
IF(JSONCPP_INCLUDE_DIR)
    STRING(REGEX REPLACE "/json.*$$" "" JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR})
    SET(JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR} CACHE PATH "JsonCpp include dir" FORCE)
ENDIF()

# get the GCC compiler version
EXEC_PROGRAM(${CMAKE_CXX_COMPILER}
             ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
             OUTPUT_VARIABLE _gcc_COMPILER_VERSION
             OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(JSONCPP_NAMES ${JSONCPP_NAMES} libjson_linux-gcc-${_gcc_COMPILER_VERSION}_libmt.so)
FIND_LIBRARY(JSONCPP_LIBRARIES
             NAMES ${JSONCPP_NAMES})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonCpp DEFAULT_MSG JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIR)

MARK_AS_ADVANCED(JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIR)
