#pragma once
#include "Drawable.h"
#include <random>
#include "Camera.h"

class Box : public Drawable
{
public:
	Box(Graphics& gfx, float x, float y,float z);
};