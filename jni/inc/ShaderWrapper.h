//-----------------------------------------------------------------------------
//@File:	ShaderWrapper.h
//@Brief:	Shader wrapper class declaration
//@Author:	Hector Morales Piloni
//@Date:	April 15, 2015
//-----------------------------------------------------------------------------
#pragma once

#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

class ShaderWrapper
{
public:
	enum technique {GOURAUD, PHONG, SHADOWMAP};

	ShaderWrapper();
	~ShaderWrapper();
	void ProcessTechnique(string vs, string ps);
	void UseTechnique();
	void SetAttribute(string name);
	void SetUniform(string name);
	GLint GetAttributeID(string name);
	GLint GetUniformID(string name);

private:
	GLuint _mShaderProgramID;

	//These maps are going to hold all the attribute and uniform
	//variables, we can have different number/name of these per shader
	map<string,int> _mAttribute;
	map<string,int> _mUniform;
};

