#pragma once
#include "ConstBuffs.h"
#include "Box.h"
#include "MatHelper.h"
#include "TerrainClass.h"
class SpotLight
{
public:

	SpotLight(Graphics& gfx);
	void Bind(Graphics& gfx);
	void SetSpotLightPosition(dx::XMFLOAT3 v);
	//void Draw(Graphics& gfx);
private:

	struct SpotLightConstBuff
	{
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 specular;
		alignas(16)DirectX::XMFLOAT3 att;
		alignas(16)DirectX::XMFLOAT3 pos;
		alignas(16)DirectX::XMFLOAT3 dir;
		float range;
		float spot;
		


	};
private:
	
	//Box* boxlight;
	SpotLightConstBuff __BufferData;
	mutable PSConstBuff<SpotLightConstBuff> __buff;
};