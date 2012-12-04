# Copyright (C) 2009 The Android Open Source Project
    #
    # Licensed under the Apache License, Version 2.0 (the "License");
    # you may not use this file except in compliance with the License.
    # You may obtain a copy of the License at
    #
    #      http://www.apache.org/licenses/LICENSE-2.0
    #
    # Unless required by applicable law or agreed to in writing, software
    # distributed under the License is distributed on an "AS IS" BASIS,
    # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    # See the License for the specific language governing permissions and
    # limitations under the License.
    #
    #

    LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    CC_LITE_SRC_FILES := \
        src/google/protobuf/stubs/common.cc                              \
        src/google/protobuf/stubs/once.cc                                \
        src/google/protobuf/extension_set.cc                             \
        src/google/protobuf/generated_message_util.cc                    \
        src/google/protobuf/message_lite.cc                              \
        src/google/protobuf/repeated_field.cc                            \
        src/google/protobuf/wire_format_lite.cc                          \
        src/google/protobuf/io/coded_stream.cc                           \
        src/google/protobuf/io/zero_copy_stream.cc                       \
        src/google/protobuf/io/zero_copy_stream_impl_lite.cc



    COMPILER_SRC_FILES :=  \
        src/google/protobuf/descriptor.cc \
        src/google/protobuf/descriptor.pb.cc \
        src/google/protobuf/descriptor_database.cc \
        src/google/protobuf/dynamic_message.cc \
        src/google/protobuf/extension_set.cc \
        src/google/protobuf/extension_set_heavy.cc \
        src/google/protobuf/generated_message_reflection.cc \
        src/google/protobuf/generated_message_util.cc \
        src/google/protobuf/message.cc \
        src/google/protobuf/message_lite.cc \
        src/google/protobuf/reflection_ops.cc \
        src/google/protobuf/repeated_field.cc \
        src/google/protobuf/service.cc \
        src/google/protobuf/text_format.cc \
        src/google/protobuf/unknown_field_set.cc \
        src/google/protobuf/wire_format.cc \
        src/google/protobuf/wire_format_lite.cc \
        src/google/protobuf/compiler/code_generator.cc \
        src/google/protobuf/compiler/command_line_interface.cc \
        src/google/protobuf/compiler/importer.cc \
        src/google/protobuf/compiler/main.cc \
        src/google/protobuf/compiler/parser.cc \
        src/google/protobuf/compiler/plugin.cc \
        src/google/protobuf/compiler/plugin.pb.cc \
        src/google/protobuf/compiler/subprocess.cc \
        src/google/protobuf/compiler/zip_writer.cc \
        src/google/protobuf/compiler/cpp/cpp_enum.cc \
        src/google/protobuf/compiler/cpp/cpp_enum_field.cc \
        src/google/protobuf/compiler/cpp/cpp_extension.cc \
        src/google/protobuf/compiler/cpp/cpp_field.cc \
        src/google/protobuf/compiler/cpp/cpp_file.cc \
        src/google/protobuf/compiler/cpp/cpp_generator.cc \
        src/google/protobuf/compiler/cpp/cpp_helpers.cc \
        src/google/protobuf/compiler/cpp/cpp_message.cc \
        src/google/protobuf/compiler/cpp/cpp_message_field.cc \
        src/google/protobuf/compiler/cpp/cpp_primitive_field.cc \
        src/google/protobuf/compiler/cpp/cpp_service.cc \
        src/google/protobuf/compiler/cpp/cpp_string_field.cc \
        src/google/protobuf/compiler/java/java_enum.cc \
        src/google/protobuf/compiler/java/java_enum_field.cc \
        src/google/protobuf/compiler/java/java_extension.cc \
        src/google/protobuf/compiler/java/java_field.cc \
        src/google/protobuf/compiler/java/java_file.cc \
        src/google/protobuf/compiler/java/java_generator.cc \
        src/google/protobuf/compiler/java/java_helpers.cc \
        src/google/protobuf/compiler/java/java_message.cc \
        src/google/protobuf/compiler/java/java_message_field.cc \
        src/google/protobuf/compiler/java/java_primitive_field.cc \
        src/google/protobuf/compiler/java/java_service.cc \
        src/google/protobuf/compiler/python/python_generator.cc \
        src/google/protobuf/io/coded_stream.cc \
        src/google/protobuf/io/gzip_stream.cc \
        src/google/protobuf/io/printer.cc \
        src/google/protobuf/io/tokenizer.cc \
        src/google/protobuf/io/zero_copy_stream.cc \
        src/google/protobuf/io/zero_copy_stream_impl.cc \
        src/google/protobuf/io/zero_copy_stream_impl_lite.cc \
        src/google/protobuf/stubs/common.cc \
        src/google/protobuf/stubs/once.cc \
        src/google/protobuf/stubs/structurally_valid.cc \
        src/google/protobuf/stubs/strutil.cc \
        src/google/protobuf/stubs/substitute.cc

    # C++ full library
    # =======================================================
    #include $(CLEAR_VARS)

    LOCAL_MODULE := protobuf
    LOCAL_MODULE_TAGS := optional

    LOCAL_CPP_EXTENSION := .cc

LOCAL_ARM_MODE := arm #some instructions are not in the thumb set

    LOCAL_SRC_FILES := \
        $(CC_LITE_SRC_FILES)                                             \
        src/google/protobuf/stubs/strutil.cc                             \
        src/google/protobuf/stubs/substitute.cc                          \
        src/google/protobuf/stubs/structurally_valid.cc                  \
        src/google/protobuf/descriptor.cc                                \
        src/google/protobuf/descriptor.pb.cc                             \
        src/google/protobuf/descriptor_database.cc                       \
        src/google/protobuf/dynamic_message.cc                           \
        src/google/protobuf/extension_set_heavy.cc                       \
        src/google/protobuf/generated_message_reflection.cc              \
        src/google/protobuf/message.cc                                   \
        src/google/protobuf/reflection_ops.cc                            \
        src/google/protobuf/service.cc                                   \
        src/google/protobuf/text_format.cc                               \
        src/google/protobuf/unknown_field_set.cc                         \
        src/google/protobuf/wire_format.cc                               \
        src/google/protobuf/io/gzip_stream.cc                            \
        src/google/protobuf/io/printer.cc                                \
        src/google/protobuf/io/tokenizer.cc                              \
        src/google/protobuf/io/zero_copy_stream_impl.cc                  \
        src/google/protobuf/compiler/importer.cc                         \
        src/google/protobuf/compiler/parser.cc

    LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/src

    LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/android \
        bionic \
        $(LOCAL_PATH)/src \
        $(JNI_H_INCLUDE)

    LOCAL_SHARED_LIBRARIES := \
        libz libcutils libutils
    LOCAL_LDLIBS := -lz
    # stlport conflicts with the host stl library
    #ifneq ($(TARGET_SIMULATOR),true)
    #LOCAL_C_INCLUDES += external/stlport/stlport
    #LOCAL_SHARED_LIBRARIES += libstlport
    #endif

    # Define the header files to be copied
    #LOCAL_COPY_HEADERS := \
    #    src/google/protobuf/stubs/once.h \
    #    src/google/protobuf/stubs/common.h \
    #    src/google/protobuf/io/coded_stream.h \
    #    src/google/protobuf/generated_message_util.h \
    #    src/google/protobuf/repeated_field.h \
    #    src/google/protobuf/extension_set.h \
    #    src/google/protobuf/wire_format_lite_inl.h
    #
    #LOCAL_COPY_HEADERS_TO := $(LOCAL_MODULE)

    #LOCAL_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES) #export includes
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS) #export linker cmds
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS) #export c flgs
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS) #export cpp flgs

    include $(BUILD_STATIC_LIBRARY)

