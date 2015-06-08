#include <inc/Renderer.h>
#include <inc/FileReader.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#ifndef _Included_verman_androidshadowmapping_LibJNIWrapper
#define _Included_verman_androidshadowmapping_LibJNIWrapper
#ifdef __cplusplus
extern "C" {
#endif

static Renderer *renderer = 0;

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_OnSurfaceCreated(JNIEnv *, jclass)
{
	renderer = new Renderer();
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_OnDrawFrame(JNIEnv *, jclass)
{
	renderer->DrawFrame();
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_NativeInit(JNIEnv *, jclass, jint w, jint h)
{
	renderer->Initialize(w,h);
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_CreateAssetMgr(JNIEnv *env, jclass, jobject assetManager)
{
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	FileReader::SetAssetManager(mgr);
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_OnStop(JNIEnv *, jclass)
{
	delete renderer;
	renderer = 0;
}

#ifdef __cplusplus
}
#endif
#endif
