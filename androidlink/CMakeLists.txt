cmake_minimum_required(VERSION 2.4.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

#protobuf
find_package(ProtocolBuffers REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS PROTOFILES msg/androidlink.proto msg/state.proto msg/pose.proto msg/posestamped.proto msg/posewithcovariancestamped.proto   msg/vector3.proto  msg/quaternion.proto msg/plane.proto msg/point3d.proto)
include_directories(${PROJECT_SOURCE_DIR}/build/msg)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(androidlink_client jni/androidlink_client_main.cc jni/androidlink_client.cc  ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(androidlink_client ${Boost_LIBRARIES}) 
target_link_libraries(androidlink_client ${PROTOBUF_LIBRARY})


#add_executable(androidlink_server jni/androidlink_server_main.cc jni/androidlink_server.cc  ${PROTO_SRCS} ${PROTO_HDRS})
#target_link_libraries(androidlink_server ${Boost_LIBRARIES}) 
#target_link_libraries(androidlink_server ${PROTOBUF_LIBRARY})
