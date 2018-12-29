LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := el_nv21_utils
LOCAL_SRC_FILES := el_nv21_utils.cpp
include $(BUILD_SHARED_LIBRARY)
