#pragma once
#include "ConstBuffs.h"
#include "Box.h"
#include "MatHelper.h"
#include "TerrainClass.h"
class PointLight
{
public:

	PointLight(Graphics& gfx);
	void Bind(Graphics& gfx);
	void SetPointLightPosition(dx::XMFLOAT3 v);
	void Draw(Graphics& gfx);
private:

	struct PointLightConstBuff
	{
		 DirectX::XMFLOAT4 ambient;
		 DirectX::XMFLOAT4 diffuse;
		 DirectX::XMFLOAT4 specular;
		 DirectX::XMFLOAT3 att;
		 alignas(16)DirectX::XMFLOAT3 pos;
		 float range;
		/*alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;*/

	};
private:
	
	PointLightConstBuff __BufferData;
	mutable PSConstBuff<PointLightConstBuff> __buff;
};