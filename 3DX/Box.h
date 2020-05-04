#pragma once
#include "Drawable.h"
#include <random>


class Box : public Drawable
{
	struct InstancedData
	{
		DirectX::XMFLOAT4X4 World;
		DirectX::XMFLOAT4 Color;
	};

public:
	Box() = default;
	Box(Graphics& gfx, float x, float y, float z, bool reflaction = false, bool isShadow=false);
	void Update(float ft);
	void FrustumCulling(Graphics& gfx);
	DirectX::XMMATRIX GetTransformation() const;
	void ReflactionOn(bool reflationStatus);
	void ShadowOn(bool shadowStatus);
	void MoveBox(float fx, float fy, float fz);
	void BindTestShadow(Graphics& gfx, bool refStat);
	
private:
	std::vector<InstancedData> mInstancedData;
	bool instancingEnabled = true;
	bool frustumCullingEnabled = true;
	bool isReflaction = false;
	bool isShadow = false;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	float x, y,z;
};

