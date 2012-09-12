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
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../installfiles
LOCAL_MODULE    := cvd

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS += -DHAVE_NEON=1
    LOCAL_CFLAGS += -DLOCAL_ARM_NEON=1
    LOCAL_ARM_NEON  := true
    LOCAL_SRC_FILES += ../installfiles/cvd_src/NEON/convert_rgb_to_y.cc ../installfiles/cvd_src/NEON/half_sample.cc                      
else
    LOCAL_SRC_FILES += ../installfiles/cvd_src/noarch/convert_rgb_to_y.cc ../installfiles/cvd_src/noarch/half_sample.cc                      
endif

LOCAL_SRC_FILES += ../installfiles/cvd_src/bayer.cc                      \
../installfiles/cvd_src/brezenham.cc                       \
../installfiles/cvd_src/colourspace_convert.cc                       \
../installfiles/cvd_src/connected_components.cc                      \
../installfiles/cvd_src/convolution.cc                      \
../installfiles/cvd_src/cvd_timer.cc                      \
../installfiles/cvd_src/deinterlacebuffer.cc                      \
../installfiles/cvd_src/diskbuffer2.cc                      \
../installfiles/cvd_src/draw.cc                      \
../installfiles/cvd_src/draw_toon.cc                      \
../installfiles/cvd_src/eventobject.cc                      \
../installfiles/cvd_src/exceptions.cc                      \
../installfiles/cvd_src/fast/fast_10_detect.cc                      \
../installfiles/cvd_src/fast/fast_10_score.cc                      \
../installfiles/cvd_src/fast/fast_11_detect.cc                      \
../installfiles/cvd_src/fast/fast_11_score.cc                      \
../installfiles/cvd_src/fast/fast_12_detect.cc                      \
../installfiles/cvd_src/fast/fast_12_score.cc                      \
../installfiles/cvd_src/fast/fast_7_detect.cc                      \
../installfiles/cvd_src/fast/fast_7_score.cc                      \
../installfiles/cvd_src/fast/fast_8_detect.cc                      \
../installfiles/cvd_src/fast/fast_8_score.cc                      \
../installfiles/cvd_src/fast/fast_9_detect.cc                      \
../installfiles/cvd_src/fast/fast_9_score.cc                      \
../installfiles/cvd_src/fast_corner.cc                      \
../installfiles/cvd_src/fast_corner_9_nonmax.cc                      \
../installfiles/cvd_src/image_io.cc                      \
../installfiles/cvd_src/Linux/videosource_nov4l1buffer.cc                      \
../installfiles/cvd_src/Linux/videosource_nov4lbuffer.cc                      \
../installfiles/cvd_src/morphology.cc                      \
../installfiles/cvd_src/noarch/convolve_gaussian.cc                      \
../installfiles/cvd_src/noarch/default_memalign.cc                      \
../installfiles/cvd_src/noarch/gradient.cc                      \
../installfiles/cvd_src/noarch/median_3x3.cc                      \
../installfiles/cvd_src/noarch/two_thirds_sample.cc                      \
../installfiles/cvd_src/noarch/utility_byte_differences.cc                      \
../installfiles/cvd_src/noarch/utility_double_int.cc                      \
../installfiles/cvd_src/noarch/utility_float.cc                      \
../installfiles/cvd_src/noarch/yuv422_wrapper.cc                      \
../installfiles/cvd_src/nonmax_suppression.cc                      \
../installfiles/cvd_src/thread/runnable_batch.cc                      \
../installfiles/cvd_src/OSX/videosource_noqtbuffer.cc                      \
../installfiles/cvd_src/noarch/slower_corner_10.cc                      \
../installfiles/cvd_src/slower_corner_11.cc                      \
../installfiles/cvd_src/slower_corner_12.cc                      \
../installfiles/cvd_src/slower_corner_7.cc                      \
../installfiles/cvd_src/slower_corner_8.cc                      \
../installfiles/cvd_src/slower_corner_9.cc                      \
../installfiles/cvd_src/synchronized.cc                      \
../installfiles/cvd_src/tensor_voting.cc                      \
../installfiles/cvd_src/thread.cc                      \
../installfiles/cvd_src/timeddiskbuffer.cc                      \
../installfiles/cvd_src/videosource.cc                      \
../installfiles/cvd_src/videosource_nodvbuffer.cc                      \
../installfiles/cvd_src/videosource_novideofilebuffer.cc                      \
../installfiles/cvd_src/yuv411_to_stuff.cc                      \
../installfiles/cvd_src/yuv420.cc                      \
../installfiles/cvd_src/yuv422.cc                      \
../installfiles/pnm_src/bmp_write.cc                      \
../installfiles/pnm_src/bmp.cc                      \
../installfiles/pnm_src/cvdimage.cc                      \
../installfiles/pnm_src/fits.cc                      \
../installfiles/pnm_src/fitswrite.cc                      \
../installfiles/pnm_src/pnm_grok.cc                      \
../installfiles/pnm_src/save_postscript.cc                      \
../installfiles/pnm_src/text.cc                      \
../installfiles/pnm_src/text_write.cc                      \
../installfiles/pnm_src/bmp_read.cc                      \
#../installfiles/cvd_src/glwindow.cc                      \
../installfiles/cvd_src/gltext.cc                      \


LOCAL_STATIC_LIBRARIES += TooN
LOCAL_STATIC_LIBRARIES += cpufeatures
LOCAL_LDLIBS    += -landroid

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES) #export includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export cpp flgs
LOCAL_EXPORT_CXXFLAGS := $(LOCAL_CXXFLAGS) #export cpp flgs

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_CPP_EXTENSION := .cc
LOCAL_MODULE    := testcvd

LOCAL_LDLIBS +=  -llog -ldl
LOCAL_LDLIBS    += -landroid -lGLESv2
LOCAL_SRC_FILES := hello-libcvd.cc

LOCAL_STATIC_LIBRARIES += cvd
LOCAL_STATIC_LIBRARIES += cpufeatures

include $(BUILD_SHARED_LIBRARY)
$(call import-module,cpufeatures)
$(call import-module,TooN)
