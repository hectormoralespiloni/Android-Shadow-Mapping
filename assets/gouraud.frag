//-----------------------------------------------------------------------------
//@File:	Gouraud.frag
//@Brief:	Implements a basic Gouraud shading (per vertex lighting)
//@Author:	Hector Morales Piloni
//@Date:	April 11, 2015
//-----------------------------------------------------------------------------

//This specifies the precision of our variables
//speed vs performance
precision lowp float;

uniform bool useTexture;
uniform sampler2D texture0;

varying vec4 v_color;
varying vec2 v_texCoords;

void main()
{
	//We check if we're using texture mapping or not, if true
	//we sample a value from the texture using texCoords
	//and blend it with our final color
	if(useTexture)
		gl_FragColor = v_color * texture2D(texture0, v_texCoords);
	else
		gl_FragColor = v_color;
}
