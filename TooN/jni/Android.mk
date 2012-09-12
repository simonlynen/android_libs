# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.ccrg/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_MODULE    := TooN

LOCAL_LDLIBS +=  -llog -ldl
LOCAL_LDLIBS    += -landroid
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES) #export includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export cpp flgs

LOCAL_STATIC_LIBRARIES += lapack
LOCAL_STATIC_LIBRARIES += cpufeatures

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_MODULE    := testtoon

LOCAL_SRC_FILES := hello-toon.cc

LOCAL_LDLIBS +=  -llog -ldl
LOCAL_LDLIBS    += -landroid

LOCAL_STATIC_LIBRARIES += TooN

include $(BUILD_SHARED_LIBRARY)
$(call import-module,cpufeatures)
$(call import-module,lapack/jni)
