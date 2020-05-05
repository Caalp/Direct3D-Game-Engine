#pragma once
#include "Drawable.h"
#include <random>


class Box : public Drawable
{
public:
	Box() = default;
	Box(Graphics& gfx, float x, float y, float z, bool reflaction = false, bool isShadow=false);
	void Update(float ft);
	DirectX::XMMATRIX GetTransformation(Graphics& gfx) const;
	void ReflactionOn(bool reflationStatus);
	void ShadowOn(bool shadowStatus);
	void MoveBox(float fx, float fy, float fz);
	void BindTestShadow(Graphics& gfx, bool refStat);
private:
	bool isReflaction = false;
	bool isShadow = false;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float x, y,z;
};

