# - Determines which method to use for methods that will be executed before main
# begins.
#
# Defines:
# INIT_METHOD_ATTRIBUTE_CONSTRUCTOR - if __attribute__ ((constructor)) can be used
# INIT_METHOD_CRT - if a CRT initialization on windows can be used
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

GET_FILENAME_COMPONENT(CHECK_INIT_METHOD_MODULE_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)

IF(INIT_METHOD_CRT OR INIT_METHOD_ATTRIBUTE_CONSTRUCTOR)
    MESSAGE(STATUS "Using cached init method values")
ELSE()
    MESSAGE(STATUS "Determining init method")

    MESSAGE(STATUS "Checking if __attribute__ ((constructor)) is working")
    TRY_RUN(ATTRIBUTE_CONSTRUCTOR_RESULT COMPILER_COMPILES_ATTRIBUTE_CONSTRUCTOR
            "${CMAKE_BINARY_DIR}"
            "${CHECK_INIT_METHOD_MODULE_DIR}/TestAttributeConstructor.cpp"
            RUN_OUTPUT_VARIABLE RUN_OUTPUT)
    
    IF(ATTRIBUTE_CONSTRUCTOR_RESULT)
        MESSAGE(STATUS "Checking if __attribute__ ((constructor)) is working - compiles")
        
        IF(RUN_OUTPUT MATCHES ".*CONSTRUCTOR.*")
            MESSAGE(STATUS "Checking if __attribute__ ((constructor)) is working - yes")
            SET(INIT_METHOD_ATTRIBUTE_CONSTRUCTOR TRUE CACHE BOOL "auto init method that can be used" FORCE)
        ELSE()
            MESSAGE(STATUS "Checking if __attribute__ ((constructor)) is working - no")
            SET(INIT_METHOD_ATTRIBUTE_CONSTRUCTOR FALSE CACHE BOOL "auto init method that can be used" FORCE)
        ENDIF()
        
    ELSE()
        MESSAGE(STATUS "Checking if __attribute__ ((constructor)) is working - does not compile")
        SET(INIT_METHOD_ATTRIBUTE_CONSTRUCTOR FALSE CACHE BOOL "auto init method that can be used" FORCE)
    ENDIF()
    
    MESSAGE(STATUS "Checking if CRT initialization is working")
    TRY_RUN(CRT_RESULT COMPILER_COMPILES_CRT
            "${CMAKE_BINARY_DIR}"
            "${CHECK_INIT_METHOD_MODULE_DIR}/TestCRTInit.cpp"
            RUN_OUTPUT_VARIABLE RUN_OUTPUT)
            
    IF(CRT_RESULT)
        MESSAGE(STATUS "Checking if CRT initialization is working - compiles")
        
        IF(RUN_OUTPUT MATCHES ".*CONSTRUCTOR.*")
            MESSAGE(STATUS "Checking if CRT initialization is working - yes")
            SET(INIT_METHOD_CRT TRUE CACHE BOOL "auto init method that can be used" FORCE)
        ELSE()
            MESSAGE(STATUS "Checking if CRT initialization is working - no")
            SET(INIT_METHOD_CRT FALSE CACHE BOOL "auto init method that can be used" FORCE)
        ENDIF()
        
    ELSE()
        MESSAGE(STATUS "Checking if CRT initialization is working - does not compile")
        SET(INIT_METHOD_CRT FALSE CACHE BOOL "auto init method that can be used" FORCE)
    ENDIF()
    
    MARK_AS_ADVANCED(INIT_METHOD_ATTRIBUTE_CONSTRUCTOR INIT_METHOD_CRT)

ENDIF()
