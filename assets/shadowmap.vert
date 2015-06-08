//-----------------------------------------------------------------------------
//@File:	ShadowMap.vert
//@Brief:	Projects the shadow map texture into geometry
//@Author:	Hector Morales Piloni
//@Date:	April 16, 2015
//@Ref:		http://malideveloper.arm.com/downloads/deved/tutorial/SDK/linux/2.4/shadow_mapping.html
//-----------------------------------------------------------------------------

attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec2 texCoords;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjectionMatrix;	//Should be the same as the camera's projection Matrix
uniform vec3 lightPosition;

varying vec4 v_color;
varying vec2 v_texCoords;
varying vec4 v_shadowTexCoords;

const vec4 ambientColor = vec4(0.1, 0.1, 0.1, 1.0);

void main()
{
	//Shadow texture coordinates range from [-1,1]
	//so we need to normalize to [0,1] by multiplying by bias matrix below
    const mat4 biasMat = mat4(0.5, 0.0, 0.0, 0.0,
                              0.0, 0.5, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              0.5, 0.5, 0.0, 1.0);

    //Calculate vertex position, which is being seen from the light point-of-view
    v_shadowTexCoords =  lightProjectionMatrix * lightViewMatrix * modelViewMatrix * position;

    //Normalize texture coords from -1..1 to 0..1
    v_shadowTexCoords =  biasMat * v_shadowTexCoords;

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