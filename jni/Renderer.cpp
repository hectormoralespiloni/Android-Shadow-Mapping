#include <inc/Renderer.h>

Renderer::Renderer()
{
	_mLight = NULL;
	_mCamera = NULL;
	_mCube = NULL;
	_mFloor = NULL;
	_mWindowWidth = 0;
	_mWindowHeight = 0;
}

Renderer::~Renderer()
{
	if(_mCube)
		delete _mCube;
	if(_mFloor)
		delete _mFloor;

	_mFloor = NULL;
	_mCube = NULL;
}

void Renderer::DrawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_mShader[ShaderWrapper::GOURAUD]->UseTechnique();
	_mFloor->Draw();
	_mCube->Draw();
}

void Renderer::Initialize(int width, int height)
{
	_mWindowWidth = width;
	_mWindowHeight = height;

	//Initialize OpenGL ES
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, _mWindowWidth, _mWindowHeight);

	//Initialize the light
	_mLight = new Light();
	_mLight->SetPosition(3.0f, 4.0f, 10.0f);

	//Initialize the camera
	_mCamera = new Camera();
	_mCamera->SetPosition(0.0f, 0.5f, 5.0f);
	mat4x4 projectionMatrix = glm::perspective(45.0f, (float)_mWindowWidth / _mWindowHeight, 0.01f, 100.0f);
	mat4x4 lookAtMatrix = glm::lookAt(_mCamera->GetPosition(), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	_mCamera->SetProjectionMatrix(projectionMatrix);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	//Initialize the geometry
	_mFloor = new Floor();
	_mFloor->Initialize();
	_mFloor->SetScale(4.0, 1.0, 4.0);
	_mFloor->SetPosition(0.0, 0.0, -1.0);
	_mFloor->AttachShader(_mShader[ShaderWrapper::GOURAUD]);

	_mCube = new Cube();
	_mCube->Initialize();
	_mCube->SetPosition(1.0f, 1.5f, -1.0f);
	_mCube->AttachShader(_mShader[ShaderWrapper::GOURAUD]);
}

void Renderer::LoadShader(ShaderWrapper::technique t, string vs, string ps, string attributes[], int countA, string uniforms[], int countU)
{
	ShaderWrapper *shader;
	shader = new ShaderWrapper();
	shader->ProcessTechnique(vs, ps);

	//Originally we were using sizeof(attributes)/sizeof(attributes[0])
	//but sizeof is returning only 1 string, not the whole array

	for(int i=0; i<countA; i++){
		shader->SetAttribute(attributes[i]);
	}

	for(int i=0; i<countU; i++){
		shader->SetUniform(uniforms[i]);
	}

	_mShader[t] = shader;
}
