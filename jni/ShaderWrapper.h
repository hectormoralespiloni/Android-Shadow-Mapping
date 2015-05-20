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

static const char GOURAUD_VERTEX[] = "\
attribute vec4 position;\
attribute vec4 color;\
attribute vec3 normal;\
attribute vec2 texCoords;\
\
uniform mat4 modelViewProjectionMatrix;\
uniform mat4 modelViewMatrix;\
uniform vec3 lightPosition;\
\
varying vec4 v_color;\
varying vec2 v_texCoords;\
\
/*Const to speed things up, */\
/*It would be better if we pass this from the OGLES program*/\
const vec4 ambientColor = vec4(0.1, 0.1, 0.1, 1.0);\
\
void main()\
{\
	/*We need to convert object vertex/normal into eye space*/\
	/*to do so, we multiply by our model view matrix*/\
	vec3 eyePos = vec3(modelViewMatrix * position);\
	vec3 eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));\
\
	/*Calculate the light direction vector*/\
	vec3 lightVector = normalize(lightPosition - eyePos);\
\
	/*Our diffuse or lambertian term would be the dot product */\
	/*between the normal and the light direction vector, the amount of*/\
	/*light received would be proportionally inverse to the angle between them*/\
	float diffuse = max(dot(eyeNormal, lightVector), 0.0);\
\
	/*our final color would be dimmed by the diffuse term, we add ambient light as well*/\
	v_color = ambientColor + color * diffuse;\
\
	/*pass-through our texture coordinates (if any)*/\
	v_texCoords = texCoords;\
\
	gl_Position = modelViewProjectionMatrix * position;\
}\
";

static const char GOURAUD_FRAGMENT[] = "\
/*This specifies the precision of our variables*/\
/*speed vs performance*/\
precision lowp float;\
\
uniform bool useTexture;\
uniform sampler2D texture0;\
\
varying vec4 v_color;\
varying vec2 v_texCoords;\
\
void main()\
{\
	/*We check if we're using texture mapping or not, if true*/\
	/*we sample a value from the texture using texCoords*/\
	/*and blend it with our final color*/\
	if(useTexture)\
		gl_FragColor = v_color * texture2D(texture0, v_texCoords);\
	else\
		gl_FragColor = v_color;\
}\
";

class ShaderWrapper
{
public:
	ShaderWrapper();
	~ShaderWrapper();
	void SetTechnique(string technique);
	void SetTechnique(string technique, string vs, string ps);
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

