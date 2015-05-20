#include "Renderer.h"
#include <jni.h>

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
	renderer->OnDrawFrame();
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_OnSurfaceChanged(JNIEnv *, jclass, jint w, jint h)
{
	renderer->Initialize(w,h);
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
