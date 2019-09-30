#pragma once
#include "DrawableSource.h"
#include <random>
class Box : public DrawableSource<Box>
{
public:
	Box(Graphics& gfx, float x, float y);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	float pitch = 1.0f;
	float yaw = 1.0f;
	float roll = 1.0f;
	float x, y;
};