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
#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

static const char GOURAUD_VERTEX[] =
"attribute vec4 color;\n"
"attribute vec4 position;\n"
"attribute vec3 normal;\n"
"attribute vec2 texCoords;\n"
"uniform mat4 modelViewProjectionMatrix;\n"
"uniform mat4 modelViewMatrix;\n"
"uniform vec3 lightPosition;\n"
"varying vec4 v_color;\n"
"varying vec2 v_texCoords;\n"
"const vec4 ambientColor = vec4(0.1, 0.1, 0.1, 1.0);\n"
"void main() {\n"
"	vec3 eyePos = vec3(modelViewMatrix * position);\n"
"	vec3 eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));\n"
"	vec3 lightVector = normalize(lightPosition - eyePos);\n"
"	float diffuse = max(dot(eyeNormal, lightVector), 0.0);\n"
"	v_color = ambientColor + color * diffuse;\n"
"	v_texCoords = texCoords;\n"
"	gl_Position = modelViewProjectionMatrix * position;"
"}";

static const char GOURAUD_FRAGMENT[] =
"precision lowp float;\n"
"uniform bool useTexture;\n"
"uniform sampler2D texture0;\n"
"varying vec4 v_color;\n"
"varying vec2 v_texCoords;\n"
"void main() {\n"
"	if(useTexture) gl_FragColor = v_color * texture2D(texture0, v_texCoords);\n"
"	else gl_FragColor = v_color;\n"
"}";

class ShaderWrapper
{
public:
	ShaderWrapper();
	~ShaderWrapper();
	void SetTechnique(string technique);
	void UseTechnique();
	void SetAttribute(string name);
	void SetUniform(string name);
	GLint GetAttributeID(string name);
	GLint GetUniformID(string name);
	GLint GetProgramID();

private:
	const char* ReadFile(const char* fileName);
	GLuint _mShaderProgramID;

	//These maps are going to hold all the attribute and uniform
	//variables, we can have different number/name of these per shader
	map<string,int> _mAttribute;
	map<string,int> _mUniform;
};

