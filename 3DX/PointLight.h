#pragma once
#include "ConstBuffs.h"
#include "Box.h"
#include "MatHelper.h"
#include "TerrainClass.h"
#include "Sphere.h"

class PointLight : public Sphere
{
public:

	PointLight(Graphics& gfx);
	void Bind(Graphics& gfx);
	virtual void Utilize(Graphics& gfx) override;
	void DrawLightImgui(DirectX::XMFLOAT3& pos);



	void Update();

private:

	struct PointLightConstBuff
	{
		 DirectX::XMFLOAT4 ambient;
		 DirectX::XMFLOAT4 diffuse;
		 DirectX::XMFLOAT4 specular;
		 alignas(16)DirectX::XMFLOAT3 att;
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