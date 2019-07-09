# In order to compile this program, you must generate the C++ proxy from the
# AIDL file:
# [...]/sampservice$ aidl-cpp ISampService.aidl <pathtothisdirectory>/ <pathtothisdirectory/SampSystemServiceProxy.cpp

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := clientservicedemo
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES) # Très Important
LOCAL_SRC_FILES := client.cpp SampSystemServiceProxy.cpp
LOCAL_SHARED_LIBRARIES := libutils libcutils libbinder liblog
LOCAL_C_INCLUDES += frameworks/native/include system/core/include
include $(BUILD_EXECUTABLE)

