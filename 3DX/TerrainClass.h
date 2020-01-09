#pragma once
#include "additional_headers.h"
class TerrainClass : public DrawableSource<TerrainClass>
{
public:
	TerrainClass(Graphics& gfx, DirectX::XMFLOAT3 eyePos, UINT tW, UINT tH, float width, float height);
	void Update(float dt) { return; };
	DirectX::XMMATRIX GetTransformation() const;
	
	static float GetHillHeight(float x, float z)
	{
		return 0.3f*(z*sinf(0.1f*x) + x * cosf(0.1f*z));
	}
	

private:
	DirectX::XMFLOAT3 eyePos;
	int terrainWidth, terrainHeight;
};