//-----------------------------------------------------------------------------
//@File:	Cube.cpp
//@Brief:	Cube implementation file
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#include "Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

bool Cube::Initialize()
{
	_mVertices = new vector<GLfloat>;
	_mNormals = new vector<GLfloat>;
	_mColors = new vector<GLfloat>;
	_mIndices = new vector<GLuint>;

	//Bottom face
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back( 0.5); //v0
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v1
	_mVertices->push_back( 0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v2
	_mVertices->push_back( 0.5); _mVertices->push_back(-0.5); _mVertices->push_back( 0.5); //v3
	//Top face
	_mVertices->push_back(-0.5); _mVertices->push_back(0.5); _mVertices->push_back( 0.5); //v4
	_mVertices->push_back( 0.5); _mVertices->push_back(0.5); _mVertices->push_back( 0.5); //v5
	_mVertices->push_back( 0.5); _mVertices->push_back(0.5); _mVertices->push_back(-0.5); //v6
	_mVertices->push_back(-0.5); _mVertices->push_back(0.5); _mVertices->push_back(-0.5); //v7
	//Left face
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v8
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back( 0.5); //v9
	_mVertices->push_back(-0.5); _mVertices->push_back( 0.5); _mVertices->push_back( 0.5); //v10
	_mVertices->push_back(-0.5); _mVertices->push_back( 0.5); _mVertices->push_back(-0.5); //v11
	//Right face
	_mVertices->push_back(0.5); _mVertices->push_back(-0.5); _mVertices->push_back( 0.5); //v12
	_mVertices->push_back(0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v13
	_mVertices->push_back(0.5); _mVertices->push_back( 0.5); _mVertices->push_back(-0.5); //v14
	_mVertices->push_back(0.5); _mVertices->push_back( 0.5); _mVertices->push_back( 0.5); //v15
	//Front face
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back(0.5); //v16
	_mVertices->push_back( 0.5); _mVertices->push_back(-0.5); _mVertices->push_back(0.5); //v17
	_mVertices->push_back( 0.5); _mVertices->push_back( 0.5); _mVertices->push_back(0.5); //v18
	_mVertices->push_back(-0.5); _mVertices->push_back( 0.5); _mVertices->push_back(0.5); //v19
	//Back Face
	_mVertices->push_back( 0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v20
	_mVertices->push_back(-0.5); _mVertices->push_back(-0.5); _mVertices->push_back(-0.5); //v21
	_mVertices->push_back(-0.5); _mVertices->push_back( 0.5); _mVertices->push_back(-0.5); //v22
	_mVertices->push_back( 0.5); _mVertices->push_back( 0.5); _mVertices->push_back(-0.5); //v23

	//Bottom face
	_mNormals->push_back(0.0); _mNormals->push_back(-1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(-1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(-1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(-1.0); _mNormals->push_back(0.0);
	//Top face
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	_mNormals->push_back(0.0); _mNormals->push_back(1.0); _mNormals->push_back(0.0);
	//Left face
	_mNormals->push_back(-1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(-1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(-1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(-1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	//Right face
	_mNormals->push_back(1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	_mNormals->push_back(1.0); _mNormals->push_back(0.0); _mNormals->push_back(0.0);
	//Front face
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(1.0);
	//Back face
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(-1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(-1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(-1.0);
	_mNormals->push_back(0.0); _mNormals->push_back(0.0); _mNormals->push_back(-1.0);

	//We're drawing the cube faces as triangle fans, so we need 4 indices per face
	for (int i = 0; i < 24; i++) {
		_mIndices->push_back(i);
	}

	for (int side = 0; side < 6; side++)
	{
		for (int i = 0; i < 16; i += 4){
			switch (side){
			case 0: //Red
				_mColors->push_back(1.0);
				_mColors->push_back(0.0);
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				break;
			case 1: //Green
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				break;
			case 2: //Blue
				_mColors->push_back(0.0);
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				_mColors->push_back(1.0);
				break;
			case 3: //Yellow
				_mColors->push_back(1.0);
				_mColors->push_back(1.0);
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				break;
			case 4: //Cyan
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				_mColors->push_back(1.0);
				_mColors->push_back(1.0);
				break;
			case 5: //Magenta
				_mColors->push_back(1.0);
				_mColors->push_back(0.0);
				_mColors->push_back(1.0);
				_mColors->push_back(1.0);
				break;
			}
		}
	}

	_mRotAngleX = 0.0;
	_mRotAngleY = 0.0;
	_mRotAngleZ = 0.0;

	//Create Vertex & Index buffer objects to avoid copying shape's data from host CPU memory each frame
	//VBO are defined as GL_ARRAY_BUFFER and IBO as GL_ELEMENT_ARRAY_BUFFER
	//Last parameter means that passed data is modified once and used many times
	glGenBuffers(1, &_mVBOVertices);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOVertices);
	glBufferData(GL_ARRAY_BUFFER, 72*sizeof(GLfloat), &_mVertices->front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mVBONormals);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBONormals);
	glBufferData(GL_ARRAY_BUFFER, 72*sizeof(GLfloat), &_mNormals->front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mVBOColors);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOColors);
	glBufferData(GL_ARRAY_BUFFER, 96*sizeof(GLfloat), &_mColors->front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mIBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24*sizeof(GLuint), &_mIndices->front(), GL_STATIC_DRAW);

	//Unbind the buffers to avoid accidental writes to these buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//We can safely delete our shape data, since it has been transfered to GPU memory
	delete _mVertices;
	_mVertices = NULL;
	delete _mNormals;
	_mNormals = NULL;
	delete _mIndices;
	_mIndices = NULL;
	delete _mColors;
	_mColors = NULL;

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	return true;
}

void Cube::Draw()
{
	//Enable attributes for position, color and normals
	//because we're using VBO's, we pass as the last parameter an offset
	//instead of a pointer to the data buffer
	if (_mShader->GetAttributeID("position") >= 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _mVBOVertices);
		glEnableVertexAttribArray(_mShader->GetAttributeID("position"));
		glVertexAttribPointer(_mShader->GetAttributeID("position"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (_mShader->GetAttributeID("normal") >= 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _mVBONormals);
		glEnableVertexAttribArray(_mShader->GetAttributeID("normal"));
		glVertexAttribPointer(_mShader->GetAttributeID("normal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (_mShader->GetAttributeID("color") >= 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _mVBOColors);
		glEnableVertexAttribArray(_mShader->GetAttributeID("color"));
		glVertexAttribPointer(_mShader->GetAttributeID("color"), 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	_mModelViewMatrix = mat4(1.0);
	_mRotationMatrix = glm::rotate(mat4(1.0f), _mRotAngleX, vec3(1.0f, 0.0f, 0.0f));
	_mRotationMatrix = glm::rotate(_mRotationMatrix, _mRotAngleY, vec3(0.0f, 1.0f, 0.0f));
	_mScaleMatrix = glm::scale(mat4(1.0f), vec3(_mScaleX, _mScaleY, _mScaleZ));
	_mTranslationMatrix = glm::translate(mat4(1.0f), vec3(_mPosX, _mPosY, _mPosZ));
	_mModelViewMatrix = _mTranslationMatrix * _mScaleMatrix * _mRotationMatrix * _mModelViewMatrix;
	mat4 modelViewProjection = Camera::GetProjectionMatrix() * Camera::GetLookAtMatrix() * _mModelViewMatrix;

	if (_mShader->GetUniformID("modelViewProjectionMatrix") >= 0)
		glUniformMatrix4fv(_mShader->GetUniformID("modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjection));
	if (_mShader->GetUniformID("modelViewMatrix") >= 0)
		glUniformMatrix4fv(_mShader->GetUniformID("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(_mModelViewMatrix));
	if (_mShader->GetUniformID("lightPosition") >= 0)
		glUniform3f(_mShader->GetUniformID("lightPosition"), Light::GetPosition().x, Light::GetPosition().y, Light::GetPosition().z);
	if (_mShader->GetUniformID("useTexture") >= 0)
		glUniform1i(_mShader->GetUniformID("useTexture"), 0);


	//Update cube's rotation angles for animation
	_mRotAngleX += 0.05;
	_mRotAngleY += 0.05;
	if (_mRotAngleX >= 360) _mRotAngleX -= 360;
	if (_mRotAngleY >= 360) _mRotAngleY -= 360;

	//Bind our IBO and instead of passing the indices buffer
	//to glDrawElements we pass an offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	for (int side = 0; side < 6; side++) {
		GLvoid *offset = (GLvoid *)(side * 4 * sizeof(GLuint));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, offset);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
