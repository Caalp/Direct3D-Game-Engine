#pragma once
#include "DrawableSource.h"
#include <random>
#include "Camera.h"
class Box : public DrawableSource<Box> ,public Camera 
{
public:
	Box(Graphics& gfx, float x, float y);
	void Update(float ft) override;
	
	DirectX::XMMATRIX GetViewXM() const override;
	DirectX::XMMATRIX GetWorldXM() const override;
	DirectX::XMMATRIX GetProjXM() const override;
private:
	float pitch = 1.0f;
	float yaw = 1.0f;
	float roll = 1.0f;
	float x, y;
};