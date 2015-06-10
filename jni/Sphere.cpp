//-----------------------------------------------------------------------------
//@File:	Sphere.cpp
//@Brief:	Generates a sphere programmatically using the Icosphere method
//			starts with an Icosahedron and refines triangles until some
//			user-defined recursion level
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
#include <inc/Sphere.h>

Sphere::Sphere(int refineLevel)
{
	_mRefineLevel = refineLevel;
}

Sphere::Sphere()
{
	_mRefineLevel = 2;
	_mPosX = _mPosY = _mPosZ = 0;
}

Sphere::~Sphere()
{
}

//Calculates a middle point over an edge of a triangle
//As input parameters we pass the indices of both vertices
//in our _mVertices vector
int Sphere::GetMiddlePoint(int p1, int p2)
{
	float point1[3];
	float point2[3];
	float middle[3];

	//Given the index of each vertex, we can get component x,y,z
	//by adding an offset (0,1,2)
	point1[0] = _mVertices->at(p1 * 3);
	point1[1] = _mVertices->at(p1 * 3 + 1);
	point1[2] = _mVertices->at(p1 * 3 + 2);
	point2[0] = _mVertices->at(p2 * 3);
	point2[1] = _mVertices->at(p2 * 3 + 1);
	point2[2] = _mVertices->at(p2 * 3 + 2);
	middle[0] = (point1[0] + point2[0]) / 2.0f;
	middle[1] = (point1[1] + point2[1]) / 2.0f;
	middle[2] = (point1[2] + point2[2]) / 2.0f;

	//Normalize the new vertex to make sure it's on a unit sphere
	float len = sqrt(middle[0] * middle[0] + middle[1] * middle[1] + middle[2] * middle[2]);
	middle[0] /= len;
	middle[1] /= len;
	middle[2] /= len;

	_mVertices->push_back(middle[0]);
	_mVertices->push_back(middle[1]);
	_mVertices->push_back(middle[2]);
	_mCountVertex++;

	//store it, return index
	int i = _mCountVertex - 1;
	return i;
}

//We're creating an Icosphere to avoid the density of vertices being greater around the poles like a UV sphere
//In an icosphere, its vertices are distributed evenly.
//http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
void Sphere::CreateIcosphere(int refineLevel)
{
	//Start by creating the 12 vertices of an icosahedron
	//Phi is the golden ratio
	//http://paulbourke.net/geometry/platonic/
	float phi = (1.0f + sqrt(5.0f)) / 2.0f;

	_mCountVertex = 12;
	_mVertices = new vector<GLfloat>;
	_mVertices->push_back(-1); _mVertices->push_back( phi); _mVertices->push_back(0); //v0
	_mVertices->push_back( 1); _mVertices->push_back( phi); _mVertices->push_back(0); //v1
	_mVertices->push_back(-1); _mVertices->push_back(-phi); _mVertices->push_back(0); //v2
	_mVertices->push_back( 1); _mVertices->push_back(-phi); _mVertices->push_back(0); //v3

	_mVertices->push_back(0); _mVertices->push_back(-1); _mVertices->push_back( phi); //v4
	_mVertices->push_back(0); _mVertices->push_back( 1); _mVertices->push_back( phi); //v5
	_mVertices->push_back(0); _mVertices->push_back(-1); _mVertices->push_back(-phi); //v6
	_mVertices->push_back(0); _mVertices->push_back( 1); _mVertices->push_back(-phi); //v7

	_mVertices->push_back( phi); _mVertices->push_back(0); _mVertices->push_back(-1); //v8
	_mVertices->push_back( phi); _mVertices->push_back(0); _mVertices->push_back( 1); //v9
	_mVertices->push_back(-phi); _mVertices->push_back(0); _mVertices->push_back(-1); //v10
	_mVertices->push_back(-phi); _mVertices->push_back(0); _mVertices->push_back( 1); //v11

	//Normalize vertices to make sure they're on a unit sphere
	for (vector<GLfloat>::size_type i = 0; i < _mVertices->size(); i += 3)
	{
		GLfloat x = _mVertices->at(i + 0);
		GLfloat y = _mVertices->at(i + 1);
		GLfloat z = _mVertices->at(i + 2);
		float len = sqrt(x*x + y*y + z*z);

		_mVertices->at(i+0) /= len;
		_mVertices->at(i+1) /= len;
		_mVertices->at(i+2) /= len;
	}

	//then create the 20 triangles of the icosahedron (indices)
	//var faces = new List<TriangleIndices>();
	_mIndices = new vector<GLuint>;
	_mCountTriangle = 20;
	_mCountIndex = 20*3;

	//5 faces around point 0
	_mIndices->push_back(0); _mIndices->push_back(11); _mIndices->push_back( 5);
	_mIndices->push_back(0); _mIndices->push_back( 5); _mIndices->push_back( 1);
	_mIndices->push_back(0); _mIndices->push_back( 1); _mIndices->push_back( 7);
	_mIndices->push_back(0); _mIndices->push_back( 7); _mIndices->push_back(10);
	_mIndices->push_back(0); _mIndices->push_back(10); _mIndices->push_back(11);

	//5 adjacent faces
	_mIndices->push_back( 1); _mIndices->push_back( 5); _mIndices->push_back(9);
	_mIndices->push_back( 5); _mIndices->push_back(11); _mIndices->push_back(4);
	_mIndices->push_back(11); _mIndices->push_back(10); _mIndices->push_back(2);
	_mIndices->push_back(10); _mIndices->push_back( 7); _mIndices->push_back(6);
	_mIndices->push_back( 7); _mIndices->push_back( 1); _mIndices->push_back(8);

	//5 faces around point 3
	_mIndices->push_back(3); _mIndices->push_back(9); _mIndices->push_back(4);
	_mIndices->push_back(3); _mIndices->push_back(4); _mIndices->push_back(2);
	_mIndices->push_back(3); _mIndices->push_back(2); _mIndices->push_back(6);
	_mIndices->push_back(3); _mIndices->push_back(6); _mIndices->push_back(8);
	_mIndices->push_back(3); _mIndices->push_back(8); _mIndices->push_back(9);

	//5 adjacent faces
	_mIndices->push_back(4); _mIndices->push_back(9); _mIndices->push_back( 5);
	_mIndices->push_back(2); _mIndices->push_back(4); _mIndices->push_back(11);
	_mIndices->push_back(6); _mIndices->push_back(2); _mIndices->push_back(10);
	_mIndices->push_back(8); _mIndices->push_back(6); _mIndices->push_back( 7);
	_mIndices->push_back(9); _mIndices->push_back(8); _mIndices->push_back( 1);

	//Refine triangles
	int currentTriCount = _mCountTriangle;
	for (int r = 0; r < refineLevel; r++)
	{
		vector<GLuint> *indicesTemp = new vector<GLuint>;
		for (int t = 0, i = 0; t<currentTriCount; t++, i += 3)
		{
			//replace triangle by 4 triangles
			int a = GetMiddlePoint(_mIndices->at(i), _mIndices->at(i+1));
			int b = GetMiddlePoint(_mIndices->at(i+1), _mIndices->at(i+2));
			int c = GetMiddlePoint(_mIndices->at(i+2), _mIndices->at(i));

			//Add the new indices
			//T1
			indicesTemp->push_back(_mIndices->at(i));
			indicesTemp->push_back(a);
			indicesTemp->push_back(c);
			//T2
			indicesTemp->push_back(_mIndices->at(i + 1));
			indicesTemp->push_back(b);
			indicesTemp->push_back(a);
			//T3
			indicesTemp->push_back(_mIndices->at(i + 2));
			indicesTemp->push_back(c);
			indicesTemp->push_back(b);
			//T4
			indicesTemp->push_back(a);
			indicesTemp->push_back(b);
			indicesTemp->push_back(c);
		}

		//replace _mIndices with indicesTemp to keep the new index array
		_mIndices = indicesTemp;
		indicesTemp = NULL;

		//update triangle & indices count
		_mCountTriangle *= 4;
		_mCountIndex *= 4;
		currentTriCount = _mCountTriangle;
	}

	_mRotAngleX = 0.0;
	_mRotAngleY = 0.0;
	_mRotAngleZ = 0.0;
}

bool Sphere::Initialize()
{
	CreateIcosphere(_mRefineLevel);

	//Create Vertex & Index buffer objects to avoid copying shape's data from host CPU memory each frame
	//VBO are defined as GL_ARRAY_BUFFER and IBO as GL_ELEMENT_ARRAY_BUFFER
	//Last parameter means that passed data is modified once and used many times
	glGenBuffers(1, &_mVBOVertices);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBOVertices);
	glBufferData(GL_ARRAY_BUFFER, _mCountVertex * 3 * sizeof(GLfloat), &_mVertices->front(), GL_STATIC_DRAW);

	//A vertex normal in a sphere is the same vector from the center of sphere to the vertex...
	//furthermore, it is the very same 3D point, so we can use the same vertices array as normals.
	glGenBuffers(1, &_mVBONormals);
	glBindBuffer(GL_ARRAY_BUFFER, _mVBONormals);
	glBufferData(GL_ARRAY_BUFFER, _mCountVertex * 3 * sizeof(GLfloat), &_mVertices->front(), GL_STATIC_DRAW);

	glGenBuffers(1, &_mIBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mCountIndex * sizeof(GLuint), &_mIndices->front(), GL_STATIC_DRAW);

	//Unbind the buffers to avoid accidental writes to these buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//We can safely delete our shape data, since it has been transfered to GPU memory
	delete _mVertices;
	_mVertices = NULL;
	//delete _mNormals;
	//_mNormals = NULL;
	delete _mIndices;
	_mIndices = NULL;

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	return true;
}

void Sphere::Draw()
{
	//Enable attributes for position and normals
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

	//Create our transformation matrices
	_mModelViewMatrix = mat4(1.0);
	_mRotationMatrix = glm::rotate(mat4(1.0f), _mRotAngleY, vec3(0.0f, 1.0f, 0.0f));
	_mScaleMatrix = glm::scale(mat4(1.0f), vec3(_mScaleX, _mScaleY, _mScaleZ));
	_mTranslationMatrix = glm::translate(mat4(1.0f), vec3(_mPosX, _mPosY, _mPosZ));
	_mModelViewMatrix = _mTranslationMatrix * _mScaleMatrix * _mRotationMatrix * _mModelViewMatrix;
	mat4 modelViewProjection = Camera::GetProjectionMatrix() * Camera::GetLookAtMatrix() * _mModelViewMatrix;

	if (_mShader->GetUniformID("modelViewProjectionMatrix")>=0)
		glUniformMatrix4fv(_mShader->GetUniformID("modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjection));
	if(_mShader->GetUniformID("modelViewMatrix")>=0)
		glUniformMatrix4fv(_mShader->GetUniformID("modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(_mModelViewMatrix));
	if (_mShader->GetUniformID("lightPosition")>=0)
		glUniform3f(_mShader->GetUniformID("lightPosition"), Light::GetPosition().x, Light::GetPosition().y, Light::GetPosition().z);

	_mRotAngleY += 3;
	if (_mRotAngleY >= 360) _mRotAngleY -= 360;

	//Bind our IBO and instead of passing the indices buffer to glDrawElements
	//we pass an offset
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mIBOIndices);
	glDrawElements(GL_TRIANGLES, _mCountIndex, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
