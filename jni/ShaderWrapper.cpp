//-----------------------------------------------------------------------------
//@File:	ShaderWrapper.cpp
//@Brief:	Shader wrapper class implementation
//@Author:	Hector Morales Piloni
//@Date:	April 15, 2015
//-----------------------------------------------------------------------------
#include <inc/ShaderWrapper.h>


ShaderWrapper::ShaderWrapper()
{
	_mShaderProgramID = -1;
}

ShaderWrapper::~ShaderWrapper()
{
}

void ShaderWrapper::UseTechnique()
{
	glUseProgram(_mShaderProgramID);
}

void ShaderWrapper::ProcessTechnique(technique t)
{
	const char *vertFileName = NULL;
	const char *fragFileName = NULL;

	switch(t) {
	case ShaderWrapper::GOURAUD:
		vertFileName = "gouraud.vert";
		fragFileName = "gouraud.frag";
		break;
	case ShaderWrapper::PHONG:
		vertFileName = "phong.vert";
		fragFileName = "phong.frag";
		break;
	case ShaderWrapper::SHADOWMAP:
		vertFileName = "shadowmap.vert";
		fragFileName = "shadowmap.frag";
		break;
	default:
		break;
	}

	//Clear every attribute & uniform previously defined so we can start over
	_mAttribute.clear();
	_mUniform.clear();

	//Create unique ID and process shaders
	GLuint vertexShaderID, fragmentShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char *vertShaderStr = NULL;
    char *fragShaderStr = NULL;
    unsigned int size = 0;

    FileReader::Read(vertFileName, &vertShaderStr, &size);
    FileReader::Read(fragFileName, &fragShaderStr, &size);

    GLint result = GL_FALSE;
    int logLength;

    //Compile vertex shader
    glShaderSource(vertexShaderID, 1, &vertShaderStr, NULL);
    glCompileShader(vertexShaderID);

    // Check vertex shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertexShaderID, logLength, NULL, &vertShaderError[0]);
    //__android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Vertex Error: %s", &vertShaderError[0]);

    // Compile fragment shader
    glShaderSource(fragmentShaderID, 1, &fragShaderStr, NULL);
    glCompileShader(fragmentShaderID);

    // Check fragment shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragmentShaderID, logLength, NULL, &fragShaderError[0]);
    //__android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Fragment Error: %s", &fragShaderError[0]);

    _mShaderProgramID = glCreateProgram();
    glAttachShader(_mShaderProgramID, vertexShaderID);
    glAttachShader(_mShaderProgramID, fragmentShaderID);
    glLinkProgram(_mShaderProgramID);
    glUseProgram(_mShaderProgramID);

    glGetProgramiv(_mShaderProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(_mShaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(_mShaderProgramID, logLength, NULL, &programError[0]);
    //__android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Program Error: %s", &programError[0]);

    if(fragShaderStr) delete fragShaderStr;
    if(vertShaderStr) delete vertShaderStr;

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void ShaderWrapper::SetAttribute(string name)
{
	//Get attribute location and store its ID in our attributes map
	_mAttribute[name] = glGetAttribLocation(_mShaderProgramID, name.c_str());
}

void ShaderWrapper::SetUniform(string name)
{
	//Get uniform location and store its ID in our uniforms map
	_mUniform[name] = glGetUniformLocation(_mShaderProgramID, name.c_str());
}

GLint ShaderWrapper::GetAttributeID(string name)
{
	//if map.find cannot find the value, returns map::end
	std::map<string,int>::iterator it = _mAttribute.find(name);
	if(it == _mAttribute.end())
		return -1;
	else
		return it->second;
}

GLint ShaderWrapper::GetUniformID(string name)
{
	//if map.find cannot find the value, returns map::end
	std::map<string,int>::iterator it = _mUniform.find(name);
	if(it == _mUniform.end())
		return -1;
	else
		return it->second;
}

