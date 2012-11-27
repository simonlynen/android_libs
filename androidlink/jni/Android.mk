LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#all message definitions
MSG_PATH := $(LOCAL_PATH)/../build/msg
MSG_LOCAL_SRC_FILES := \
  $(wildcard $(MSG_PATH)/*.cc)

LOCAL_CPP_EXTENSION := .cc
LOCAL_LDLIBS +=  -llog -ldl
LOCAL_MODULE    := androidlink
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := ../src/androidlink_server.cc 
LOCAL_SRC_FILES += $(subst jni/, , $(MSG_LOCAL_SRC_FILES))
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build/msg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../build
LOCAL_STATIC_LIBRARIES := boost_system boost_thread boost_random libprotobuf

include $(BUILD_STATIC_LIBRARY)

$(call import-module,boost)
$(call import-module,protobuf)

