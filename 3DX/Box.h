#pragma once
#include "DrawableSource.h"
#include <random>
#include "Camera.h"

class Box : public DrawableSource<Box>
{
public:
	Box(Graphics& gfx, float x, float y,float z);
	void Update(float ft);
	DirectX::XMMATRIX GetTransformation() const;
	
private:

	float pitch = 1.0f;
	float yaw = 1.0f;
	float roll = 1.0f;
	float x, y,z;
};

