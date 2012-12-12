# - Try to find the Intel Threading Building Blocks library
# Will define:
#
# TBB_INCLUDE_DIRS - include directories needed to use the C++ driver
# TBB_LIBRARIES - Libraries to link agains fpr the driver
# TBB_LIBRARY_DIRS - Directories containing the libraries (win)
# TBB_VERSION - Version of the TBB library that was found
#
# Possible hints:
# TBB_ROOT - root directory of the TBB installation
# TBB_DEBUG - if true, use the debug libraries of tbb instead of stripped ones
# TBB_BITS - value of 32 or 64 indicating the os type, default 32
# TBB_LIB_PATH - path containing the libraries to use
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

GET_FILENAME_COMPONENT(FIND_TBB_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(TBB_INCLUDE_DIRS
          HINTS ${TBB_ROOT}/include
                ${CMAKE_INSTALL_PREFIX}/include
          NAMES tbb.h
          PATH_SUFFIXES tbb)

IF(TBB_DEBUG)
    MESSAGE(STATUS "TBB debug version requested (TBB_DEBUG: ${TBB_DEBUG})")
    SET(TBB_LIB_NAME "tbb_debug")
    SET(TBBMALLOC_LIB_NAME "tbbmalloc_debug")
ELSE()
    MESSAGE(STATUS "TBB normal version requested (TBB_DEBUG: ${TBB_DEBUG})")
    SET(TBB_LIB_NAME "tbb")
    SET(TBBMALLOC_LIB_NAME "tbbmalloc")
ENDIF()

SET(TBB_LIBRARIES "")

# find out if this is a visual studio build and if so which version
STRING(REGEX MATCH "Visual Studio ([0-9]+)" VMATCH ${CMAKE_GENERATOR})
IF(VMATCH)
    STRING(LENGTH ${VMATCH} MATCH_LENGTH)
    STRING(LENGTH "Visual Studio " PREFIX_LENGTH)
    MATH(EXPR VERSION_LENGTH "${MATCH_LENGTH} - ${PREFIX_LENGTH}")
    STRING(SUBSTRING ${VMATCH} ${PREFIX_LENGTH} ${VERSION_LENGTH} VC_VERSION)
    MESSAGE("Visual studio version: ${VC_VERSION}")
ENDIF()

# decide if 32 or 64 bits
# TODO jwienke: do this automatically by using one of cmake's size check methods
IF(NOT TBB_BITS)
    MESSAGE(STATUS "Assuming 32 bit system")
    SET(TBB_BITS "32")
ENDIF()

SET(WIN_LIB_PATH "${TBB_ROOT}/lib/ia${TBB_BITS}/vc${VC_VERSION}")
SET(TBB_LIBRARY_DIRS "${TBB_ROOT}/bin/ia${TBB_BITS}/vc${VC_VERSION}")

FIND_LIBRARY(TBB_LIBRARY
             HINTS ${TBB_ROOT}/lib
                   ${TBB_ROOT}
                   ${TBB_LIB_PATH}
                   ${WIN_LIB_PATH}
                   ${CMAKE_INSTALL_PREFIX}
                   ${CMAKE_INSTALL_PREFIX}/lib
             NAMES ${TBB_LIB_NAME})
FIND_LIBRARY(TBBMALLOC_LIBRARY
             HINTS ${TBB_ROOT}/lib
                   ${TBB_ROOT}
                   ${TBB_LIB_PATH}
                   ${WIN_LIB_PATH}
                   ${CMAKE_INSTALL_PREFIX}
                   ${CMAKE_INSTALL_PREFIX}/lib
             NAMES ${TBBMALLOC_LIB_NAME})
             
IF(TBB_LIBRARY AND TBBMALLOC_LIBRARY)
    SET(TBB_LIBRARIES ${TBB_LIBRARY} ${TBBMALLOC_LIBRARY})
ENDIF()
             
# post-process inlude path
IF(TBB_INCLUDE_DIRS)
    STRING(REGEX REPLACE tbb/?$$ "" TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIRS})
ENDIF()
SET(TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIRS} CACHE PATH "TBB include dirs" FORCE)

# find out the TBB version that is present
CONFIGURE_FILE("${FIND_TBB_MODULE_DIR}/ExtractTBBVersion.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/ExtractTBBVersion.cpp" @ONLY)
TRY_RUN(TBB_VERSION_RUN_RESULT TBB_VERSION_COMPILE_RESULT
        "${CMAKE_BINARY_DIR}"
        "${CMAKE_CURRENT_BINARY_DIR}/ExtractTBBVersion.cpp"
        RUN_OUTPUT_VARIABLE TBB_VERSION)
MESSAGE(STATUS "TBB_VERSION: ${TBB_VERSION}")

# check if the version is acceptable
SET(TBB_VERSION_ACCEPTABLE TRUE)
IF(TBB_FIND_VERSION)
    
    MESSAGE(STATUS "TBB version check requested with target version ${TBB_FIND_VERSION}")
    
    IF(NOT TBB_VERSION_COMPILE_RESULT)
        # compiling did not work, no version extracted
        SET(TBB_VERSION_ACCEPTABLE FALSE)
    ELSEIF(NOT TBB_VERSION_RUN_RESULT EQUAL 0)
        # running did not work
        SET(TBB_VERSION_ACCEPTABLE FALSE)
    ELSEIF(${TBB_VERSION} VERSION_LESS ${TBB_FIND_VERSION})
        # wrong version
        SET(TBB_VERSION_ACCEPTABLE FALSE)
    ENDIF()
    
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(TBB DEFAULT_MSG TBB_INCLUDE_DIRS TBB_LIBRARIES TBB_VERSION_ACCEPTABLE)

# only visible in advanced view
MARK_AS_ADVANCED(TBB_INCLUDE_DIRS TBB_LIBRARIES TBB_LIBRARY TBBMALLOC_LIBRARY)
