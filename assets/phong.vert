//-----------------------------------------------------------------------------
//@File:	Phong.vert
//@Brief:	Implements a basic phong shading (per pixel lighting)
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------
attribute vec4 position;
attribute vec3 normal;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

varying vec3 eyeNormal;
varying vec3 eyePosition;

void main()
{
	//We need to convert object vertex/normal into eye space
	//to do so, we multiply by our model view matrix
	eyePosition = vec3(modelViewMatrix * position);
	eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));

	//Transform vertices
	gl_Position = modelViewProjectionMatrix * position;
}
