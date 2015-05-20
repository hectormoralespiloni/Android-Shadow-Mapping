//-----------------------------------------------------------------------------
//@File:	Light.h
//@Brief:	Defines a basic light that can be attached to a scene
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#pragma once

#include <math.h>
#include <glm/vec3.hpp>

using namespace glm;

class Light
{
public:
	Light();
	~Light();

	//Static methods that can be accessed through the entire program
	//without having to instantiate e.g.: from shapes or other classes
	static vec3 GetPosition();
	static void SetPosition(float x, float y, float z);

	void SetRotation(float angle);
	float GetRotation();

private:
	static vec3 _mPosition;	//Fixed position, set by user
	static vec3 _mRotPosition;	//In case of rotational light, we need to calculate this new position
	float _mRotationAngle;
};
