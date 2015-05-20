#include "Renderer.h"

static string GOURAUD_VERTEX2 = "\
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

static string GOURAUD_FRAGMENT2 = "\
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

Renderer::Renderer()
{
	_mLight = NULL;
	_mCamera = NULL;
	_mCube = NULL;
	_mWindowWidth = 0;
	_mWindowHeight = 0;
}

Renderer::~Renderer()
{
	if(_mCube)
		delete _mCube;

	_mCube = NULL;
}

void Renderer::OnDrawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_mShader["Gouraud"]->UseTechnique();
	_mCube->Draw();
}

void Renderer::Initialize(int width, int height)
{
	_mWindowWidth = width;
	_mWindowHeight = height;

	//Initialize OpenGL ES
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, _mWindowWidth, _mWindowHeight);

	//Initialize the light
	_mLight = new Light();
	_mLight->SetPosition(3.0f, 4.0f, 10.0f);

	//Initialize the camera
	_mCamera = new Camera();
	_mCamera->SetPosition(0.0f, 0.5f, 5.0f);

	vec3 center, up;
	up.x = up.z = center.x = center.y = center.z = 0.0f;
	up.y = 1.0f;

	//__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "W=%d H=%d", _mWindowWidth, _mWindowHeight);
	mat4x4 projectionMatrix = glm::perspective(45.0f, (float)_mWindowWidth / _mWindowHeight, 0.01f, 100.0f);
	mat4x4 lookAtMatrix = glm::lookAt(_mCamera->GetPosition(), center, up);
	_mCamera->SetProjectionMatrix(projectionMatrix);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	//Initialize the geometry
	_mCube = new Cube();
	_mCube->Initialize();
	_mCube->SetPosition(1.0f, 1.5f, -1.0f);

	ShaderWrapper *shader;

	shader = new ShaderWrapper();
	shader->SetTechnique("Gouraud");
	shader->SetAttribute("position");
	shader->SetAttribute("color");
	shader->SetAttribute("normal");
	shader->SetAttribute("texCoords");
	shader->SetUniform("modelViewProjectionMatrix");
	shader->SetUniform("modelViewMatrix");
	shader->SetUniform("lightPosition");
	shader->SetUniform("texture0");
	shader->SetUniform("useTexture");
	_mShader["Gouraud"] = shader;
	_mCube->AttachShader(_mShader["Gouraud"]);
}

void Renderer::LoadShader(string technique, string vs, string ps,string *attributes, string *uniforms)
{
	__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "technique=%s", technique.c_str());
	__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "VS=%s", vs.c_str());
	__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "PS=%s", ps.c_str());

	ShaderWrapper *shader;
	shader = new ShaderWrapper();
	shader->SetTechnique(technique, vs, ps);

	for(int i=0; i<attributes->length(); i++){
		shader->SetAttribute(attributes[i]);
		__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "ATTR=%s", attributes[i].c_str());
	}

	for(int i=0; i<uniforms->length(); i++){
		shader->SetUniform(uniforms[i]);
		__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "UNIF=%s", uniforms[i].c_str());
	}

	_mShader[technique] = shader;
}

/*
void Renderer::OnSurfaceChanged(int width, int height)
{
	_mWindowWidth = width;
	_mWindowHeight = height;

	glViewport(0, 0, _mWindowWidth, _mWindowHeight);
	mat4x4 projectionMatrix = glm::perspective(45.0f, (float)_mWindowWidth / _mWindowHeight, 0.01f, 100.0f);
	_mCamera->SetProjectionMatrix(projectionMatrix);

}
*/
