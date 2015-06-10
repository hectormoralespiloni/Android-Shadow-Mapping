# Android Shadow Mapping (May 2015)
_Shadow mapping implementation for Android using OpenGL ES 2.0 & NDK_

This is a porting from my Shadow Mapping implementation for MaliSDK to Android. 
All the OpenGL logic is implemented in C++ and compiled using NDK.
The Activity and SurfaceView objects are made in Java & that code is bridged to C++ using JNI, which was the main purpose of this exercise.

![](https://github.com/hectormoralespiloni/Android-Shadow-Mapping/blob/master/AndroidShadowMapping.png)

Requirements:
* Android SDK
* Android NDK 
* Eclipse with ADT plugin