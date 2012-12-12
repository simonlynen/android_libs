# - Try to find the cppcheck utility
# Will define:
#
# CPPCHECK_EXECUTABLE - cppcheck executable
# CPPCHECK_VERSION - version of cppcheck
#
# Possible hints:
# CPPCHECK_ROOT - root directory of the mongodb installation
#
# Copyright (C) 2011 by Johannes Wienke <jwienke at techfak dot uni-bielefeld dot de>
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

# find server executable
FIND_PROGRAM(CPPCHECK_EXECUTABLE cppcheck
             HINTS ${CPPCHECK_ROOT}/bin
                   ${CPPCHECK_ROOT})

# get the version
SET(CPPCHEcK_VERSION "")
IF(CPPCHECK_EXECUTABLE)
    EXECUTE_PROCESS(COMMAND ${CPPCHECK_EXECUTABLE} --version OUTPUT_VARIABLE CPPCHECK_VERSION_OUT)
    STRING(REGEX MATCH "[0-9]\\.[0-9]+" CPPCHECK_VERSION "${CPPCHECK_VERSION_OUT}")
ENDIF()

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Cppcheck DEFAULT_MSG CPPCHECK_EXECUTABLE CPPCHECK_VERSION)

# only visible in advanced view
MARK_AS_ADVANCED(CPPCHECK_EXECUTABLE CPPCHECK_VERSION)
