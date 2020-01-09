#pragma once
#include"Graphics.h"
#include "ConstBuffs.h"

class DirectionalLight
{
public:
	DirectionalLight(Graphics& gfx);
	void Bind(Graphics& gfx);


private:
	// Directional Light Struct in order to pass data register properly aligned as 4 byte 
	// for each
	// Directional Light will go to register b0
	struct DirectionalLightCBuff
	{
		alignas(16) DirectX::XMFLOAT4 ambient; // amount of ambient light emitted by light source	
		alignas(16) DirectX::XMFLOAT4 diffuse; // amount of diffuse light emitted by light source	
		alignas(16) DirectX::XMFLOAT4 specular; // amount of specular light
		alignas(16) DirectX::XMFLOAT3 direction;	// direction of the light
		
	};
private:
	DirectionalLightCBuff __BufferData;
	mutable PSConstBuff<DirectionalLightCBuff> __buff;
};