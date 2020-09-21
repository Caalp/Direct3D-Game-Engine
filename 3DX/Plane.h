#pragma once
#include "Drawable.h"

class Plane : public Drawable
{
public:
	
	Plane(Graphics& gfx,std::string name,UINT numRow, UINT numCol, float dx, float dt, float damping, float texScale = 1.0f);
	void Utilize(Graphics& gfx);
	

};