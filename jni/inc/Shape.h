//-----------------------------------------------------------------------------
//@File:	Shape.h
//@Brief:	Defines a basic geometric shape and properties common to all
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#pragma once

#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "ShaderWrapper.h"
#include "Camera.h"
#include "Light.h"

using namespace std;
using namespace glm;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual void Draw() = 0;
	virtual bool Initialize() = 0;

	void AttachShader(ShaderWrapper *shader);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);

protected:
	mat4 _mModelViewMatrix;
	mat4 _mRotationMatrix;
	mat4 _mTranslationMatrix;
	mat4 _mScaleMatrix;

	GLfloat _mRotAngleX;
	GLfloat _mRotAngleY;
	GLfloat _mRotAngleZ;

	GLfloat _mScaleX;
	GLfloat _mScaleY;
	GLfloat _mScaleZ;

	GLfloat _mPosX;
	GLfloat _mPosY;
	GLfloat _mPosZ;

	//To hold data
	vector<GLfloat> *_mVertices;
	vector<GLfloat> *_mNormals;
	vector<GLfloat> *_mColors;
	vector<GLuint> *_mIndices;

	//Common VBO and IBO stuff
	GLuint _mVBOVertices;
	GLuint _mVBONormals;
	GLuint _mVBOColors;
	GLuint _mIBOIndices;

	ShaderWrapper *_mShader;
};

