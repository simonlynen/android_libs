LOCAL_PATH:= $(call my-dir)
export MAINDIR:= $(LOCAL_PATH)

include $(CLEAR_VARS)

include $(MAINDIR)/clapack/Android.mk

LOCAL_PATH := $(MAINDIR)

include $(CLEAR_VARS)
LOCAL_MODULE:= lapack
LOCAL_STATIC_LIBRARIES := tmglib clapack blas f2c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:= testlapack
LOCAL_SRC_FILES:= testclapack.cpp
LOCAL_STATIC_LIBRARIES := lapack
include $(BUILD_SHARED_LIBRARY)
