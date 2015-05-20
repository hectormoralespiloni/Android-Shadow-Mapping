#include "Renderer.h"

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
