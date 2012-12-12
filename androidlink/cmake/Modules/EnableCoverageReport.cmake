# - Creates a special coverage build type and target on GCC.
#
# Defines a function ENABLE_COVERAGE_REPORT which generates the coverage target
# for selected targets. Optional arguments to this function are used to filter
# unwanted results using globbing expressions. Moreover targets with tests for
# the source code can be specified to trigger regenerating the report if the
# test has changed
#
# ENABLE_COVERAGE_REPORT(TARGETS target... [FILTER filter...] [TESTS test targets...])
#
# To generate a coverage report first build the project with
# CMAKE_BUILD_TYPE=coverage, then call make test and afterwards make coverage.
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

INCLUDE(ParseArguments)

FIND_PACKAGE(Lcov)

FUNCTION(ENABLE_COVERAGE_REPORT)
    
    # argument parsing
    PARSE_ARGUMENTS(ARG "FILTER;TARGETS;TESTS" "" ${ARGN})
    
    # create coverage build type
    SET(CMAKE_CXX_FLAGS_COVERAGE ${CMAKE_CXX_FLAGS_DEBUG} PARENT_SCOPE)
    SET(CMAKE_C_FLAGS_COVERAGE ${CMAKE_C_FLAGS_DEBUG} PARENT_SCOPE)
    SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_CONFIGURATION_TYPES} coverage PARENT_SCOPE)
    
    STRING(TOLOWER "${CMAKE_BUILD_TYPE}" COVERAGE_BUILD_TYPE)
    IF(CMAKE_COMPILER_IS_GNUCXX AND LCOV_FOUND AND "${COVERAGE_BUILD_TYPE}" MATCHES "coverage")

        MESSAGE(STATUS "Coverage support enabled for targets: ${ARG_TARGETS}")

        # instrument targets
        SET_TARGET_PROPERTIES(${ARG_TARGETS} PROPERTIES COMPILE_FLAGS --coverage
                                                        LINK_FLAGS --coverage)
    
        # set up coverage target
        SET(COVERAGE_RAW_FILE "${CMAKE_BINARY_DIR}/coverage.raw.info")
        SET(COVERAGE_FILTERED_FILE "${CMAKE_BINARY_DIR}/coverage.info")
        SET(COVERAGE_REPORT_DIR "${CMAKE_BINARY_DIR}/coveragereport")
        
        ADD_CUSTOM_COMMAND(OUTPUT ${COVERAGE_RAW_FILE}
                           COMMAND ${LCOV_EXECUTABLE} -c -d ${CMAKE_BINARY_DIR} -o ${COVERAGE_RAW_FILE}
                           WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                           COMMENT "Collecting coverage data"
                           DEPENDS ${ARG_TARGETS} ${ARG_TESTS}
                           VERBATIM)
        
        # filter unwanted stuff
        LIST(LENGTH ARG_FILTER FILTER_LENGTH)
        IF(${FILTER_LENGTH} GREATER 0)
            SET(FILTER COMMAND ${LCOV_EXECUTABLE})
            FOREACH(F ${ARG_FILTER})
                SET(FILTER ${FILTER} -r ${COVERAGE_FILTERED_FILE} ${F})
            ENDFOREACH()
            SET(FILTER ${FILTER} -o ${COVERAGE_FILTERED_FILE})
        ELSE()
            SET(FILTER "")
        ENDIF()
        
        ADD_CUSTOM_COMMAND(OUTPUT ${COVERAGE_FILTERED_FILE}
                           COMMAND ${LCOV_EXECUTABLE} -e ${COVERAGE_RAW_FILE} "${CMAKE_SOURCE_DIR}*"  -o ${COVERAGE_FILTERED_FILE}
                           ${FILTER}
                           DEPENDS ${COVERAGE_RAW_FILE}
                           COMMENT "Filtering recorded coverage data for project-relevant entries"
                           VERBATIM)
        ADD_CUSTOM_COMMAND(OUTPUT ${COVERAGE_REPORT_DIR}
                           COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_REPORT_DIR}
                           COMMAND ${GENHTML_EXECUTABLE} --legend --show-details -t "${PROJECT_NAME} test coverage" -o ${COVERAGE_REPORT_DIR} ${COVERAGE_FILTERED_FILE}
                           DEPENDS ${COVERAGE_FILTERED_FILE}
                           COMMENT "Generating HTML coverage report in ${COVERAGE_REPORT_DIR}"
                           VERBATIM)
                           
        ADD_CUSTOM_TARGET(coverage
                          DEPENDS ${COVERAGE_REPORT_DIR})
                          
    ENDIF()

ENDFUNCTION()   
