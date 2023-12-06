#pragma once
#include "Drawable.h"
#include <random>
#include "Camera.h"

class TestCube : public Drawable
{
public:
	TestCube(Graphics& gfx, float x, float y, float z);
	void UpdatePos(unsigned char key, uint32_t id);
	//void Update(float ft);
	//DirectX::XMMATRIX GetTransformation() const;
};