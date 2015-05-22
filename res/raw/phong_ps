//-----------------------------------------------------------------------------
//@File:	Phong.frag
//@Brief:	Implements a basic Phong shading (per pixel lighting)
//@Author:	Hector Morales Piloni
//@Date:	April 14, 2015
//-----------------------------------------------------------------------------

//This specifies the precision of our variables
//speed vs performance
precision lowp float;

uniform vec3 lightPosition;

varying vec3 eyeNormal;
varying vec3 eyePosition;

//These are defined as constants to speed things up 
//but it would be better to have them passed from the OGLES application
const vec3 ambientColor = vec3(0.3, 0.0, 0.0);
const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main()
{
	vec3 normal = normalize(eyeNormal);
	
	//Calculate the light direction vector
	vec3 lightDir = normalize(lightPosition - eyePosition);
	
	//Calculate the light reflection vector
	vec3 reflectDir = reflect(-lightDir, normal);
	
	//Calculate the eye (viewer) direction, because specular light
	//changes upon a different viewing direction
	vec3 viewDir = normalize(-eyePosition);

	//Our diffuse or lambertian term would be the dot product 
	//between the normal and the light direction vector, the amount of
	//light received would be proportionally inverse to the angle between them
	float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;

	//if diffuse lighting is zero, we don't need to calculate anything else
	if(lambertian > 0.0) 
	{
		float specAngle = max(dot(reflectDir, viewDir), 0.0);
		specular = pow(specAngle, 10.0);
    }
	
	gl_FragColor = vec4(ambientColor + diffuseColor*lambertian + specular*specColor, 1.0);
}
