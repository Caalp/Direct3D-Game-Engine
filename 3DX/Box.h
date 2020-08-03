#pragma once
#include "Drawable.h"
#include <random>
#include "Camera.h"

class Box : public Drawable
{
public:

	Box(Graphics& gfx, float x, float y,float z);
	//void Update(float ft);
	//DirectX::XMMATRIX GetTransformation() const;
	
//private:
//	
//	float pitch = 1.0f;
//	float yaw = 1.0f;
//	float roll = 1.0f;
//	float x, y,z;
};

