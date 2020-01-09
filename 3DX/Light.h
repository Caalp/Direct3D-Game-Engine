#pragma once
#include "LightSource.h"
#include "ConstBuffs.h"
#include "MatHelper.h"
#include "Camera.h"

namespace dx = DirectX;

class Light 
{
	Light() 
	{
		

		if (onDirLight == 1)
		{
			mDirLight.ambient = dx::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			mDirLight.diff = dx::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			mDirLight.specular = dx::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			mDirLight.dir = dx::XMFLOAT3(0.57735f, -0.57735f, 0.57735f);
		}
		if(onPointLight == 1)
		{
			mPointLight.ambient = dx::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
			mPointLight.diff = dx::XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
			mPointLight.specular = dx::XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
			mPointLight.att = dx::XMFLOAT3(0.0f, 0.1f, 0.0f);
			mPointLight.range = 25.0f;
		}
		if (onSpotLight == 1)
		{
			mSpotLight.ambient = dx::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			mSpotLight.diff = dx::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
			mSpotLight.specular = dx::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			mSpotLight.att = dx::XMFLOAT3(1.0f, 0.0f, 0.0f);
			mSpotLight.spot = 96.0f;
			mSpotLight.range = 10000.0f;
		}
	}
	void switchDirLight(bool state)
	{
		if (state == 1)
		{
			onDirLight = true;
		}
		else if(state == 0)
		{
			onDirLight = false;
		}
	}
	void switchSpotLight(bool state)
	{
		if (state == 1)
		{
			onSpotLight = true;
		}
		else if (state == 0)
		{
			onSpotLight = false;
		}
	}
	void switchPointLight(bool state)
	{
		if (state == 1)
		{
			onPointLight = true;
		}
		else if (state == 0)
		{
			onPointLight = false;
		}
	}
	

private:
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> XMDirtLight;
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> XMPointLight;
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> XMSpotLight;
	static Material mat;

	DirectionalLight mDirLight;
	PointLight mPointLight;
	SpotLight mSpotLight;

	bool onDirLight;
	bool onPointLight;
	bool onSpotLight;
	
};