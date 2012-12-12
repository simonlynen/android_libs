
SET(CMAKE_MODULE_PATH "${RSC_CMAKE_MODULE_PATH}")
MESSAGE(STATUS "Installing CMake modules to: ${CMAKE_MODULE_PATH}")

INSTALL(FILES ExtractTBBVersion.cpp.in
              TestAttributeConstructor.cpp
              TestCRTInit.cpp
              CheckInitMethod.cmake
              CMakeDoxyfile.in
              EnableCoverageReport.cmake
              FindBoostThreadpool.cmake
              FindBoostUUID.cmake
              FindCppcheck.cmake
              FindEigen2.cmake
              FindJsonCpp.cmake
              FindLcov.cmake
              FindLog4cxx.cmake
              FindMongo.cmake
              FindProtocolBuffers.cmake
              FindSpread.cmake
              FindTBB.cmake
              GenerateCppcheck.cmake
              GenerateDoxygen.cmake
              IgnoreReturnCode.cmake
              InstallFilesRecursive.cmake
              ParseArguments.cmake
        DESTINATION ${CMAKE_MODULE_PATH})
