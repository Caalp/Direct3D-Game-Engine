#pragma once
#include "Sphere.h"

class Sky : public Sphere
{
public:
	Sky(Graphics& gfx, std::string name, float radius, unsigned int sliceCount, unsigned int stackCount);
	virtual void Utilize(Graphics& gfx) override;
};