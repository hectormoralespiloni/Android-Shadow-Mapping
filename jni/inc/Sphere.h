//-----------------------------------------------------------------------------
//@File:	Sphere.h
//@Brief:	Defines an Icosphere made of triangles that can be refined further
//			by using a recursion level defined by the user.
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#pragma once

#include "Shape.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(int refineLevel);
	~Sphere();
	virtual void Draw();
	virtual bool Initialize();

private:
	int GetMiddlePoint(int p1, int p2);
	void CreateIcosphere(int refineLevel);

	int _mRefineLevel;
	int _mCountIndex;
	int _mCountNormal;
	int _mCountVertex;
	int _mCountTriangle;
};
