LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := androidlink
LOCAL_CPP_EXTENSION := .cc

LOCAL_C_INCLUDES += $(LOCAL_PATH)/androlink
LOCAL_LDLIBS +=  -llog -ldl
LOCAL_LDLIBS    += -landroid
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := ../jni/androidlink_server.cc ../jni/androidlink.cc 
#all message definitions
#MSG_PATH := $(LOCAL_PATH)/../build/msg/src
#MSG_LOCAL_SRC_FILES += $(wildcard $(MSG_PATH)/*.cc)
#LOCAL_SRC_FILES += $(subst jni/, , $(MSG_LOCAL_SRC_FILES))

LOCAL_SRC_FILES += ../build/msg/androidlink.pb.cc ../build/msg/plane.pb.cc ../build/msg/point3d.pb.cc ../build/msg/pose.pb.cc ../build/msg/posestamped.pb.cc ../build/msg/posewithcovariancestamped.pb.cc ../build/msg/quaternion.pb.cc ../build/msg/state.pb.cc ../build/msg/vector3.pb.cc

#MSG_LOCAL_INCLUDE_FILES += $(wildcard $(MSG_PATH)/*.h)
#LOCAL_C_INCLUDES += $(subst jni/, , $(MSG_LOCAL_INCLUDE_FILES))
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build/msg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_STATIC_LIBRARIES := boost_system boost_thread boost_random boost_random boost_math_c99 boost_system boost_math_c99f eigen ros_time ros_serialization sensorhandler_native protobuf
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES) #export includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export cpp flgs
include $(BUILD_STATIC_LIBRARY)

$(call import-module,eigen)
$(call import-module,boost)
$(call import-module,sensor_handler)
$(call import-module,protobuf)

