//-----------------------------------------------------------------------------
//@File:	Camera.cpp
//@Brief:	Camera implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#include "Camera.h"

//In order to avoid Linkage problems
//we need to define static members in the implementation file
//since in the header (.h) file, we only declare them...
vec3 Camera::_mPosition;
mat4x4 Camera::_mProjectionMatrix;
mat4x4 Camera::_mLookAtMatrix;

Camera::Camera()
{
}

Camera::~Camera()
{
}

vec3 Camera::GetPosition()
{
	return _mPosition;
}

mat4x4 Camera::GetProjectionMatrix()
{
	return _mProjectionMatrix;
}

mat4x4 Camera::GetLookAtMatrix()
{
	return _mLookAtMatrix;
}

void Camera::SetPosition(float x, float y, float z)
{
	_mPosition.x = x;
	_mPosition.y = y;
	_mPosition.z = z;
}

void Camera::SetProjectionMatrix(mat4x4 m)
{
	_mProjectionMatrix = m;
}

void Camera::SetLookAtMatrix(mat4x4 m)
{
	_mLookAtMatrix = m;
}
