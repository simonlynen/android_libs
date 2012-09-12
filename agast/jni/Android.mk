LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_LIB_TYPE:=STATIC
OPENCV_INSTALL_MODULES:=on

include ../includeOpenCV.mk
ifeq ("$(wildcard $(OPENCV_MK_PATH))","")
	#try to load OpenCV.mk from default install location
	include $(TOOLCHAIN_PREBUILT_ROOT)/user/share/OpenCV/OpenCV.mk
else
	include $(OPENCV_MK_PATH)
endif

AGAST_SRC := agast/src
LOCAL_C_INCLUDES += $(LOCAL_PATH)/agast/include

#$(warning INFO: LOCAL_C_INCLUDES = '$(LOCAL_C_INCLUDES)')

#lib AGAST core
LOCAL_CPP_EXTENSION := .cc
LOCAL_MODULE    := agast
LOCAL_SRC_FILES += $(AGAST_SRC)/oast9_16.cc $(AGAST_SRC)/oast9_16_nms.cc \
	$(AGAST_SRC)/agast7_12d.cc $(AGAST_SRC)/agast7_12d_nms.cc \
	$(AGAST_SRC)/agast7_12s.cc $(AGAST_SRC)/agast7_12s_nms.cc \
	$(AGAST_SRC)/agast5_8.cc $(AGAST_SRC)/agast5_8_nms.cc \
	$(AGAST_SRC)/AstDetector.cc  $(AGAST_SRC)/nonMaximumSuppression.cc
LOCAL_LDLIBS +=  -llog -ldl
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES) #export opencv includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export opencv linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export opencv c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export opencv cpp flgs
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
#lib AGAST core
LOCAL_CPP_EXTENSION := .cc
LOCAL_MODULE    := jni_agast_bridge
LOCAL_SRC_FILES := jni_agast_bridge.cc
LOCAL_LDLIBS +=  -llog -ldl
LOCAL_STATIC_LIBRARIES := agast

include $(BUILD_SHARED_LIBRARY)
