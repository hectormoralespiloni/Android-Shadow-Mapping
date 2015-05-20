//-----------------------------------------------------------------------------
//@File:	ShaderWrapper.cpp
//@Brief:	Shader wrapper class implementation
//@Author:	Hector Morales Piloni
//@Date:	April 15, 2015
//-----------------------------------------------------------------------------
#include "ShaderWrapper.h"


ShaderWrapper::ShaderWrapper()
{
}

ShaderWrapper::~ShaderWrapper()
{
}

void ShaderWrapper::UseTechnique()
{
	glUseProgram(_mShaderProgramID);
}

const char* ShaderWrapper::ReadFile(const char *filePath)
{
    string content;
    ifstream fileStream(filePath, ios::in);

    if(!fileStream.is_open())
    {
        //cout << "Could not read file " << filePath << ". File does not exist." << endl;
        __android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Could not read file %s. File does not exist", filePath);
        return "";
    }

    string line = "";
    while(!fileStream.eof())
    {
        getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content.c_str();
}

void ShaderWrapper::SetTechnique(string name)
{
	//Clear every attribute & uniform previoulsy defined so we can start over
	_mAttribute.clear();
	_mUniform.clear();

	//Full paths to the shader files
	string vertexShaderPath = name + ".vert";
	string fragmentShaderPath = name + ".frag";

	//Create unique ID and process shaders
	GLuint vertexShaderID, fragmentShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Load shaders from file
    const char *vertShaderStr = GOURAUD_VERTEX; //ReadFile(vertexShaderPath.c_str());
    const char *fragShaderStr = GOURAUD_FRAGMENT; //ReadFile(fragmentShaderPath.c_str());

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
    //cout << &vertShaderError[0] << endl;
    __android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Vertex Error:%d - %s", vertexShaderID, &vertShaderError[0]);


    // Compile fragment shader
    //cout << "Compiling fragment shader." << endl;
    glShaderSource(fragmentShaderID, 1, &fragShaderStr, NULL);
    glCompileShader(fragmentShaderID);

    // Check fragment shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragmentShaderID, logLength, NULL, &fragShaderError[0]);
    //cout << &fragShaderError[0] << endl;
    __android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Fragment Error:%d - %s", fragmentShaderID, &fragShaderError[0]);

    //cout << "Linking program" << endl;
    _mShaderProgramID = glCreateProgram();
    glAttachShader(_mShaderProgramID, vertexShaderID);
    glAttachShader(_mShaderProgramID, fragmentShaderID);
    glLinkProgram(_mShaderProgramID);
    glUseProgram(_mShaderProgramID);

    glGetProgramiv(_mShaderProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(_mShaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
    vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(_mShaderProgramID, logLength, NULL, &programError[0]);
    //cout << &programError[0] << endl;
    __android_log_print(ANDROID_LOG_DEBUG, "ShaderWrapper.cpp", "Program Error:%d - %s", _mShaderProgramID, &programError[0]);

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
	std::map<string,int>::iterator it = _mAttribute.find(name);
	return it->second;
}

GLint ShaderWrapper::GetUniformID(string name)
{
	std::map<string,int>::iterator it = _mUniform.find(name);
	return it->second;
}

