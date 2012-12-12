# - Generate a doxygen documentation for a project.
# The function GENERATE_DOXYGEN is provided to create a "doc" target that
# generates a doxygen documentation (currently only as HTML report).
#
# GENERATE_DOXYGEN([AUTO_INSTALL] [NAME <project name>] [VERSION <project version>] [INSTALL_DIR <doc install dir>])
#
#     AUTO_INSTALL: if given the documentation is automatically generated with
#                   the install target and then installed (sometimes buggy)
#     NAME: name of the project used for the documentation, defaults to
#           CMAKE_PROJECT_NAME
#     VERSION: version of the software, if not given, no version is passed to
#              doxygen
#     INSTALL_DIR: directory under which to install the generated documentation.
#                  If not given, this defaults to
#                  ${CMAKE_INSTALL_PREFIX}/share/${NAME}
#
# This function can always be called, even if no doxygen was found. Then no
# target is created.
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

GET_FILENAME_COMPONENT(GENERATE_DOXYGEN_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

INCLUDE(ParseArguments)
FIND_PACKAGE(Doxygen)

FUNCTION(GENERATE_DOXYGEN)

    IF(DOXYGEN_FOUND)
        
        # argument parsing
        PARSE_ARGUMENTS(ARG "NAME;VERSION;INSTALL_DIR" "AUTO_INSTALL" ${ARGN})
    
        # name
        SET(DOC_PROJECT_NAME "${CMAKE_PROJECT_NAME}")
        LIST(LENGTH ARG_NAME NAME_LENGTH)
        IF(${NAME_LENGTH} EQUAL 1)
            SET(DOC_PROJECT_NAME "${ARG_NAME}")
        ENDIF()
        
        # version
        SET(DOC_PROJECT_VERSION "")
        LIST(LENGTH ARG_VERSION VERSION_LENGTH)
        IF(${VERSION_LENGTH} EQUAL 1)
            SET(DOC_PROJECT_VERSION "${ARG_VERSION}")
        ENDIF()
        
        # install dir
        SET(DOC_INSTALL_DIR "share/${DOC_PROJECT_NAME}") 
        LIST(LENGTH ARG_INSTALL_DIR INSTALL_DIR_LENGTH)
        IF(${INSTALL_DIR_LENGTH} EQUAL 1)
            SET(DOC_INSTALL_DIR "${ARG_INSTALL_DIR}")
        ENDIF()
        
        SET(DOC_API_DIR ${CMAKE_BINARY_DIR}/doc)
        SET(DOC_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
        SET(DOC_WARN_FILE ${CMAKE_BINARY_DIR}/doxygen-warn.log)
        
        SET(DOXYFILE ${CMAKE_BINARY_DIR}/Doxyfile)
        CONFIGURE_FILE("${GENERATE_DOXYGEN_MODULE_DIR}/CMakeDoxyfile.in" "${DOXYFILE}")
        
        ADD_CUSTOM_COMMAND(OUTPUT ${DOC_API_DIR}
                           DEPENDS ${DOXYFILE}
                           COMMAND ${DOXYGEN_EXECUTABLE}
                           ARGS ${DOXYFILE}
                           WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
        ADD_CUSTOM_TARGET(doc DEPENDS ${DOC_API_DIR})
        
        IF(ARG_AUTO_INSTALL)
            INSTALL(CODE "execute_process(COMMAND ${CMAKE_BUILD_TOOL} doc)")
            INSTALL(DIRECTORY ${DOC_API_DIR} DESTINATION "${DOC_INSTALL_DIR}")
        ENDIF()
        
        MESSAGE(STATUS "Generated doxygen target (doc):
       PROJECT_NAME: ${DOC_PROJECT_NAME}
       PROJECT_VERSION: ${DOC_PROJECT_VERSION}
       INSTALL_DIR: ${DOC_INSTALL_DIR}
       AUTO_INSTALL: ${ARG_AUTO_INSTALL}")
    
    ENDIF()

ENDFUNCTION()
