#pragma once
#include "Drawable.h"
#include <random>


class Box : public Drawable
{
public:
	Box() = default;
	Box(Graphics& gfx, float x, float y, float z, bool reflaction = false);
	void Update(float ft);
	DirectX::XMMATRIX GetTransformation() const;
	void ReflactionOn(bool reflationStatus);
	void MoveBox(float fx, float fy, float fz);
private:
	bool isReflaction = false;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float x, y,z;
};

