//-----------------------------------------------------------------------------
//@File:	ShadowMap.frag
//@Brief:	Projects the shadow map texture into geometry
//@Author:	Hector Morales Piloni
//@Date:	April 16, 2015
//@Ref:		http://malideveloper.arm.com/downloads/deved/tutorial/SDK/linux/2.4/shadow_mapping.html
//-----------------------------------------------------------------------------
precision highp float;

uniform bool useTexture;
uniform sampler2D texture0;
uniform sampler2D shadowMap;

varying vec4 v_color;
varying vec2 v_texCoords;
varying vec4 v_shadowTexCoords;

void main()
{
    //Draw main scene - read and compare shadow map
    vec2 texDepth = texture2DProj(shadowMap, v_shadowTexCoords).xy;

	//unpack the depth value: R has the whole part and G the fractional
	//check the depth fragment shader packing method
    float depth = (texDepth.x * 10.0 + texDepth.y);
    float lightDepth = (15.0 - v_shadowTexCoords.z) + 0.1 - depth ;

    float intensity = 1.0;	
    if(depth > 0.0 && lightDepth < 0.0)
    {
		//Geometry is in shadow, lower the intensity
        intensity = 0.2;
    }	

	//We check if we're using texture mapping or not, if true
	//we sample a value from the texture using texCoords
	//and blend it with our final color
	vec4 finalColor;
	if(useTexture)
		finalColor = vec4(v_color.rgb * intensity, v_color.a) * texture2D(texture0, v_texCoords);
	else
		finalColor = vec4(v_color.rgb * intensity, v_color.a);

	gl_FragColor = finalColor;
}
