# - Execute a process and always return with status 0
#
# This is intended to be used in cmake script mode to execute a process and
# always return 0 even if the executed process failed. Use it like:
#   cmake -DCOMMAND="ls;-l;/tmp" -p IgnoreReturnCode.cmake
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

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(NOT COMMAND)
    MESSAGE(FATAL_ERROR "No command given with -DCOMMAND=\"command;one argument;another argument\"")
ENDIF()

MESSAGE(STATUS "Executing:")
FOREACH(COMMAND_PART ${COMMAND})
    MESSAGE(STATUS "  ${COMMAND_PART}")
ENDFOREACH()

EXECUTE_PROCESS(COMMAND ${COMMAND}
                RESULT_VARIABLE RETURN_CODE)
                
IF(RETURN_CODE STREQUAL "0")
    MESSAGE(STATUS "Command executed successfully: ${COMMAND}")
ELSE()
    MESSAGE(STATUS "Command execution was not successfull. Command ${COMMAND} returned exit code: ${RETURN_CODE}")
ENDIF()    
