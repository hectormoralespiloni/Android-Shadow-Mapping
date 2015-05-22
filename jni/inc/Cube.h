//-----------------------------------------------------------------------------
//@File:	Cube.h
//@Brief:	Defines a basic Cube shape
//@Author:	Hector Morales Piloni
//@Date:	April 12, 2015
//-----------------------------------------------------------------------------
#pragma once

#include "Shape.h"

class Cube : public Shape
{
public:
	Cube();
	~Cube();
	virtual void Draw();
	virtual bool Initialize();

private:

};

