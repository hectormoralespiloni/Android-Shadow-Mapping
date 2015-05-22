#include <inc/Renderer.h>
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
	renderer->DrawFrame();
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_NativeInit(JNIEnv *, jclass, jint w, jint h)
{
	renderer->Initialize(w,h);
}

JNIEXPORT void JNICALL Java_verman_androidshadowmapping_LibJNIWrapper_LoadShader(JNIEnv *env, jclass, jint technique, jstring vs, jstring ps, jobjectArray attributes, jobjectArray uniforms)
{
	int countA = env->GetArrayLength(attributes);
	int countU = env->GetArrayLength(uniforms);

	//Create arrays that will hold the attributes and uniforms
	string attributeArray[countA];
	string uniformArray[countU];

	for (int i=0; i<countA; i++)
	{
		jstring s = (jstring)env->GetObjectArrayElement(attributes, i);
		attributeArray[i] = env->GetStringUTFChars(s, 0);
	}

	for (int i=0; i<countU; i++)
	{
		jstring s = (jstring)env->GetObjectArrayElement(uniforms, i);
		uniformArray[i] = env->GetStringUTFChars(s, 0);
	}

	//For some reason inside LoadShader sizeof(string[]) is not returning the size of
	//the whole array, just one string, thus we're passing the number of elements in countX
	renderer->LoadShader(
			(ShaderWrapper::technique) technique,
			env->GetStringUTFChars(vs, 0),
			env->GetStringUTFChars(ps, 0),
			attributeArray, countA,
			uniformArray, countU);
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
