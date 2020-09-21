#pragma once
#include "Drawable.h"

class Sphere : public Drawable
{

public:
	Sphere(Graphics& gfx,std::string name, float radius, unsigned int sliceCount, unsigned int stackCount);
	void Utilize(Graphics& gfx);
	
};