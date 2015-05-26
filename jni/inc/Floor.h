//-----------------------------------------------------------------------------
//@File:	Scene.h
//@Brief:	Defines a basic floor shape (quad)
//@Author:	Hector Morales Piloni
//@Date:	April 13, 2015
//-----------------------------------------------------------------------------
#pragma once

#include "Shape.h"
#include "Light.h"
#include "Camera.h"
//#include "Texture.h"

class Floor : public Shape
{
public:
	Floor();
	~Floor();
	virtual void Draw();
	virtual bool Initialize();

private:
	//Variables needed for texture mapping
	GLuint _mTextureID;
	vector<GLfloat> *_mTexCoords;
	GLuint _mVBOTexCoords;
};

