//-----------------------------------------------------------------------------
//@File:	Depth.frag
//@Brief:	Outputs the distance (Z value) and saves it to a texture
//@Author:	Hector Morales Piloni
//@Date:	April 16, 2015
//@Ref:		http://malideveloper.arm.com/downloads/deved/tutorial/SDK/linux/2.4/shadow_mapping.html
//-----------------------------------------------------------------------------

precision highp float;

varying vec4 v_texCoord;

void main()
{	
    //Here we're going to write the fragment depth instead of a color
	//But we have to pack it into a RGBA texture:
	//R - depth_whole_part * 0.1 (so it goes from 0-1)
	//G - depth_fractional_part (again, from 0-1)

	//We discard depth values > 10, according to reference, they cause rendering issues
    float value = 15.0 - v_texCoord.z;

    float whole_part = floor(value);
    float frac_part = value - whole_part;
    whole_part = whole_part * 0.1;
    gl_FragColor = vec4(whole_part, frac_part, 0.0, 1.0);	
}