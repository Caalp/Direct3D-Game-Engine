#pragma once
#include "ConstBuffs.h"
#include "MatHelper.h"
#include "Sphere.h"

class SpotLight : public Sphere
{
public:
	SpotLight(Graphics& gfx);
	void Bind(Graphics& gfx);
	virtual void Utilize(Graphics& gfx) override;
	void DrawLightImgui(DirectX::XMFLOAT3& pos);
	void Update();
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
	SpotLightConstBuff __BufferData;
	mutable PSConstBuff<SpotLightConstBuff> __buff;
};