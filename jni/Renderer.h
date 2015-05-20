//============================================================================
//@file		Renderer.h
//@brief	OpenGL ES 2.0 Demo Renderer class
//
//@author	Héctor Morales Piloni
//@date		April 11, 2015
///============================================================================
#ifndef RENDERER_H
#define RENDERER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Light.h"
#include "Cube.h"
#include "ShaderWrapper.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(int width, int height);
	void OnStop();
	void OnDrawFrame();
	//void OnSurfaceChanged(int width, int height);

private:
	int _mWindowHeight;
	int _mWindowWidth;

	Camera *_mCamera;
	Light *_mLight;
	//Floor _mFloor;
	Cube *_mCube;
	//Sphere _mSphere;
	//Torus _mTorus;

	//Container that maps a shader technique with
	//an actual ShaderWrapper object that can be
	//attached to different geometry
	map<string, ShaderWrapper*> _mShader;
};

#endif
