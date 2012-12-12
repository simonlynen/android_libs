# - Try to find the boost threadpool library
# Will define:
#
# BOOSTTHREADPOOL_INCLUDE_DIRS - include directories needed to use the library
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

FIND_PATH(BOOSTTHREADPOOL_INCLUDE_DIRS
          NAMES threadpool.hpp
          PATH_SUFFIXES boost)
             
# post-process inlude path
IF(BOOSTTHREADPOOL_INCLUDE_DIRS)
    STRING(REGEX REPLACE boost$$ "" BOOSTTHREADPOOL_INCLUDE_DIRS ${BOOSTTHREADPOOL_INCLUDE_DIRS})
    SET(BOOSTTHREADPOOL_INCLUDE_DIRS ${BOOSTTHREADPOOL_INCLUDE_DIRS} CACHE PATH "Boost threadpool include dirs" FORCE)
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(BoostThreadpool DEFAULT_MSG BOOSTTHREADPOOL_INCLUDE_DIRS)

# only visible in advanced view
MARK_AS_ADVANCED(BOOSTTHREADPOOL_INCLUDE_DIRS)
