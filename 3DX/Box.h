#pragma once
#include "Drawable.h"
#include <random>
#include "Camera.h"




class Box : public Drawable
{
public:

	Box(Graphics& gfx, float x, float y,float z);
	void ImguiFunc();

private:
	uint32_t mID1;
	uint32_t mID2;
	uint32_t mID3;
};

