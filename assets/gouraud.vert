//-----------------------------------------------------------------------------
//@File:	Gouraud.vert
//@Brief:	Implements a basic Gouraud shading (per vertex lighting)
//@Author:	Hector Morales Piloni
//@Date:	April 11, 2015
//-----------------------------------------------------------------------------
attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec2 texCoords;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 lightPosition;

varying vec4 v_color;
varying vec2 v_texCoords;

//Const to speed things up, 
//It would be better if we pass this from the OGLES program
const vec4 ambientColor = vec4(0.1, 0.1, 0.1, 1.0);

void main()
{
	//We need to convert object vertex/normal into eye space
	//to do so, we multiply by our model view matrix
	vec3 eyePos = vec3(modelViewMatrix * position);
	vec3 eyeNormal = vec3(modelViewMatrix * vec4(normal,0.0));

	//Calculate the light direction vector
	vec3 lightVector = normalize(lightPosition - eyePos);

	//Our diffuse or lambertian term would be the dot product 
	//between the normal and the light direction vector, the amount of
	//light received would be proportionally inverse to the angle between them
	float diffuse = max(dot(eyeNormal, lightVector), 0.0);

	//our final color would be dimmed by the diffuse term, we add ambient light as well
	v_color = ambientColor + color * diffuse;

	//pass-through our texture coordinates (if any)
	v_texCoords = texCoords;
	
	gl_Position = modelViewProjectionMatrix * position;
}
