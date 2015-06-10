//-----------------------------------------------------------------------------
//@File:	Depth.vert
//@Brief:	Outputs the distance (Z value) and saves it to a texture
//@Author:	Hector Morales Piloni
//@Date:	April 16, 2015
//@Ref:		http://malideveloper.arm.com/downloads/deved/tutorial/SDK/linux/2.4/shadow_mapping.html
//-----------------------------------------------------------------------------

attribute vec4 position;

uniform mat4 modelViewProjectionMatrix;

varying vec4 v_texCoord;

void main()
{
	//Transform both position and texture coordinates 
	//using the Light Model View Projection matrix
    v_texCoord = modelViewProjectionMatrix * position;
    gl_Position = modelViewProjectionMatrix * position;
}