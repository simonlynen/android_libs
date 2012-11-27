LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#all message definitions
MSG_PATH := $(LOCAL_PATH)/../build/msg
MSG_LOCAL_SRC_FILES := \
  $(wildcard $(MSG_PATH)/*.cc)

LOCAL_CPP_EXTENSION := .cc
LOCAL_LDLIBS +=  -llog -ldl
LOCAL_LDLIBS    += -landroid
LOCAL_MODULE    := androidlink
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := ../jni/androidlink_server.cc ../jni/androidlink.cc 
LOCAL_SRC_FILES += $(subst jni/, , $(MSG_LOCAL_SRC_FILES))
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build/msg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_STATIC_LIBRARIES := boost_system boost_thread boost_random libprotobuf boost_random boost_math_c99 boost_system boost_math_c99f eigen ros_time ros_serialization sensorhandler_native
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES) #export includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export cpp flgs
include $(BUILD_SHARED_LIBRARY)

$(call import-module,eigen)
$(call import-module,boost)
$(call import-module,sensor_handler)
$(call import-module,protobuf)

