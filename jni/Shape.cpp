//-----------------------------------------------------------------------------
//@File:	Shape.cpp
//@Brief:	Shape implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#include <inc/Shape.h>

Shape::Shape()
{
	_mShader = NULL;
	_mIndices = NULL;
	_mVertices = _mNormals = _mColors = NULL;
	_mIBOIndices = _mVBOVertices = _mVBOColors = _mVBONormals = 0;
	_mPosX = _mPosY = _mPosZ = 0.0f;
	_mScaleX = _mScaleY = _mScaleZ = 1.0f;
	_mRotAngleX = _mRotAngleY = _mRotAngleZ = 0.0f;
}

Shape::~Shape()
{
	if(_mShader)
		delete _mShader;
	if(_mVertices)
		delete _mVertices;
	if(_mNormals)
		delete _mNormals;
	if(_mColors)
		delete _mColors;
	if(_mIndices)
		delete _mIndices;

	_mShader = NULL;
	_mVertices = _mNormals = _mColors = NULL;
	_mIndices = NULL;
}

void Shape::SetPosition(float x, float y, float z)
{
	_mPosX = x;
	_mPosY = y;
	_mPosZ = z;
}

void Shape::SetRotation(float x, float y, float z)
{
	_mRotAngleX = x;
	_mRotAngleY = y;
	_mRotAngleZ = z;
}

void Shape::SetScale(float x, float y, float z)
{
	_mScaleX = x;
	_mScaleY = y;
	_mScaleZ = z;
}

void Shape::AttachShader(ShaderWrapper *shader)
{
	_mShader = shader;
}
