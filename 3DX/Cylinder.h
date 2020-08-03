#pragma once
#include "Drawable.h"

class Cylinder : public Drawable
{
public:
	Cylinder(Graphics& gfx, std::string name,float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, float texScale = 1.0f);
	void Utilize(Graphics& gfx);

};