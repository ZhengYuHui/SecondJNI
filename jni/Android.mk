LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := SecondJNI
LOCAL_SRC_FILES := SecondJNI.cpp
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)
