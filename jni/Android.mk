LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)

LOCAL_MODULE    := AndroidShadowMapping
LOCAL_CFLAGS    := -Wall -Wextra
#LOCAL_SRC_FILES := Scene.cpp Cube.cpp Renderer.cpp jni.cpp
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_LDLIBS 	:= -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)
