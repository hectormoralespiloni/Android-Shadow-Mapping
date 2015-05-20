//-----------------------------------------------------------------------------
//@File:	Camera.h
//@Brief:	Defines a basic camera and projection matrix associated with it
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	//Static methods that can be accessed through the entire program
	//without having to instantiate e.g.: from shapes or other classes
	static vec3 GetPosition();
	static mat4x4 GetProjectionMatrix();
	static mat4x4 GetLookAtMatrix();
	static void SetPosition(float x, float y, float z);
	static void SetProjectionMatrix(mat4x4 m);
	static void SetLookAtMatrix(mat4x4 m);

private:
	static vec3 _mPosition;
	static mat4x4 _mProjectionMatrix;
	static mat4x4 _mLookAtMatrix;
};
