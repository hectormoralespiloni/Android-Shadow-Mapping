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

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_OnSurfaceChanged(JNIEnv *env, jclass, jint w, jint h, jstring technique, jstring vs, jstring ps, jobjectArray attributes, jobjectArray uniforms)
{
	/*
	string *attributeArray;
	string *uniformArray;

	int countAttr = env->GetArrayLength(attributes);
	int countUnif = env->GetArrayLength(uniforms);
	attributeArray = new string[countAttr];
	uniformArray = new string[countUnif];

	for (int i=0; i<countAttr; i++){
		jstring s = (jstring)env->GetObjectArrayElement(attributes, i);
		attributeArray[i] = env->GetStringUTFChars(s, 0);
	}

	for (int i=0; i<countUnif; i++){
		jstring s = (jstring)env->GetObjectArrayElement(uniforms, i);
		uniformArray[i] = env->GetStringUTFChars(s, 0);
	}

	renderer->LoadShader(env->GetStringUTFChars(technique, 0), env->GetStringUTFChars(vs, 0), env->GetStringUTFChars(ps, 0), attributeArray, uniformArray);
	*/

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
