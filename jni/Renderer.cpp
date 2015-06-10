#include <inc/Renderer.h>

Renderer::Renderer()
{
	_mLight = NULL;
	_mCamera = NULL;
	_mCube = NULL;
	_mFloor = NULL;
	_mSphere = NULL;
	_mWindowWidth = 0;
	_mWindowHeight = 0;
}

Renderer::~Renderer()
{
	if(_mCube)
		delete _mCube;
	if(_mFloor)
		delete _mFloor;
	if(_mSphere)
		delete _mSphere;

	_mFloor = NULL;
	_mCube = NULL;
	_mSphere = NULL;
}

void Renderer::DrawFrame()
{
	//Rotate the light circulary
	float angle = _mLight->GetRotation() + 1.0f;
	if (angle >= 360) angle -= 360;
	_mLight->SetRotation(angle);

	//-------------------------------------------------------------------------
	//1st Pass: Light's point of view
	//This will create the depth texture
	//-------------------------------------------------------------------------
	mat4x4 lookAtMatrix = glm::lookAt(_mLight->GetPosition(), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	glBindFramebuffer(GL_FRAMEBUFFER, _mFBO);
	glViewport(0, 0, 512, 512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_mFloor->AttachShader(_mShader[ShaderWrapper::DEPTH]);
	_mCube->AttachShader(_mShader[ShaderWrapper::DEPTH]);
	_mSphere->AttachShader(_mShader[ShaderWrapper::DEPTH]);
	_mShader[ShaderWrapper::DEPTH]->UseTechnique();
	_mFloor->Draw();
	_mCube->Draw();
	_mSphere->Draw();

	//-------------------------------------------------------------------------
	//2nd Pass: Camera's point of view
	//This will compare the distance stored in the depth texture vs eye
	//-------------------------------------------------------------------------
	lookAtMatrix = glm::lookAt(_mCamera->GetPosition(), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, _mWindowWidth, _mWindowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_mCube->AttachShader(_mShader[ShaderWrapper::GOURAUD]);
	_mFloor->AttachShader(_mShader[ShaderWrapper::SHADOWMAP]);
	_mSphere->AttachShader(_mShader[ShaderWrapper::PHONG]);
	_mShader[ShaderWrapper::SHADOWMAP]->UseTechnique();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _mShadowTextureID);
	glUniform1i(_mShader[ShaderWrapper::SHADOWMAP]->GetUniformID("shadowMap"), 1);
	_mFloor->Draw();
	_mShader[ShaderWrapper::GOURAUD]->UseTechnique();
	_mCube->Draw();
	_mShader[ShaderWrapper::PHONG]->UseTechnique();
	_mSphere->Draw();
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
	_mLight->SetPosition(3.0f, 8.0f, 5.0f);

	//Initialize the camera
	_mCamera = new Camera();
	_mCamera->SetPosition(0.0f, 0.5f, 5.0f);
	mat4x4 projectionMatrix = glm::perspective(45.0f, (float)_mWindowWidth / _mWindowHeight, 0.01f, 100.0f);
	mat4x4 lookAtMatrix = glm::lookAt(_mCamera->GetPosition(), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	_mCamera->SetProjectionMatrix(projectionMatrix);
	_mCamera->SetLookAtMatrix(lookAtMatrix);

	//Load shaders
	string gouraud_attr[] = {"color", "position", "normal", "texCoords"};
	string gouraud_unif[] = {"modelViewProjectionMatrix", "modelViewMatrix", "lightPosition", "useTexture", "texture0"};
	int size_gouraud_attr = sizeof(gouraud_attr)/sizeof(gouraud_attr[0]);
	int size_gouraud_unif = sizeof(gouraud_unif)/sizeof(gouraud_unif[0]);
	LoadShader(ShaderWrapper::GOURAUD, gouraud_attr, size_gouraud_attr, gouraud_unif, size_gouraud_unif);

	string phong_attr[] = {"position", "normal"};
	string phong_unif[] = {"modelViewProjectionMatrix", "modelViewMatrix", "lightPosition"};
	int size_phong_attr = sizeof(phong_attr)/sizeof(phong_attr[0]);
	int size_phong_unif = sizeof(phong_unif)/sizeof(phong_unif[0]);
	LoadShader(ShaderWrapper::PHONG, phong_attr, size_phong_attr, phong_unif, size_phong_unif);

	string shadow_attr[] = {"color", "position", "normal", "texCoords"};
	string shadow_unif[] = {"modelViewProjectionMatrix", "modelViewMatrix", "lightViewMatrix", "lightProjectionMatrix", "lightPosition", "useTexture", "texture0", "shadowMap"};
	int size_shadow_attr = sizeof(shadow_attr)/sizeof(shadow_attr[0]);
	int size_shadow_unif = sizeof(shadow_unif)/sizeof(shadow_unif[0]);
	LoadShader(ShaderWrapper::SHADOWMAP, shadow_attr, size_shadow_attr, shadow_unif, size_shadow_unif);

	string depth_attr[] = {"Depth", "position"};
	string depth_unif[] = {"modelViewProjectionMatrix"};
	int size_depth_attr = sizeof(depth_attr)/sizeof(depth_attr[0]);
	int size_depth_unif = sizeof(depth_unif)/sizeof(depth_unif[0]);
	LoadShader(ShaderWrapper::DEPTH, depth_attr, size_depth_attr, depth_unif, size_depth_unif);

	//Initialize the geometry
	_mFloor = new Floor();
	_mFloor->Initialize();
	_mFloor->SetScale(7.0, 1.0, 7.0);
	_mFloor->SetPosition(0.0, 0.0, -1.0);
	//_mFloor->AttachShader(_mShader[ShaderWrapper::GOURAUD]);

	_mCube = new Cube();
	_mCube->Initialize();
	_mCube->SetPosition(1.0f, 1.5f, -1.0f);
	//_mCube->AttachShader(_mShader[ShaderWrapper::GOURAUD]);

	_mSphere = new Sphere(3);
	_mSphere->Initialize();
	_mSphere->SetPosition(-1.0f, 1.5f, 1.0f);
	_mSphere->SetScale(0.4f, 0.4f, 0.4f);
	//_mSphere->AttachShader(_mShader[ShaderWrapper::PHONG]);

	CreateShadowTexture();
}

void Renderer::LoadShader(ShaderWrapper::technique t, string attributes[], int sizeA, string uniforms[], int sizeU)
{
	ShaderWrapper *shader;
	shader = new ShaderWrapper();
	shader->ProcessTechnique(t);

	for(int i=0; i<sizeA; i++) {
		shader->SetAttribute(attributes[i]);
	}

	for(int i=0; i<sizeU; i++) {
		shader->SetUniform(uniforms[i]);
	}

	_mShader[t] = shader;
}

//This method sets up a shadow texture using a Frame Buffer Object FBO
bool Renderer::CreateShadowTexture()
{
	//Here we generate the texture name and bind it to a TEXTURE 2D object
	//this texture is going to be used as a render target later
	glGenTextures(1, &_mShadowTextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _mShadowTextureID);

	//Specify the 2D shadow texture options
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Render Buffer Objects (RBO) are used along with FBOs as render targets for offline rendering
	//We don't need colors stored in RBO, only the depth component which is an internal type
	//we specify the type of storage in glRenderbufferStorage
	glGenFramebuffers(1, &_mFBO);
	glGenRenderbuffers(1, &_mRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, _mRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 512, 512);

	//Here we attach both the RBO and texture object to the FBO
	//FBOs have different attachment points, this allows to write
	//to multiple destinations at the same time0
	glBindFramebuffer(GL_FRAMEBUFFER, _mFBO);
	glBindTexture(GL_TEXTURE_2D, _mShadowTextureID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _mRBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _mShadowTextureID, 0);

	//Unbind FBO, otherwise we won't be able to render to the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	else {
		__android_log_print(ANDROID_LOG_DEBUG, "Renderer.cpp", "GOOD FBO");
		return true;
	}
}

