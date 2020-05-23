#pragma once
#include "Drawable.h"

class Bezier:public Drawable
{
public:
	Bezier(Graphics& gfx);
	void Update(float dt) override;
};