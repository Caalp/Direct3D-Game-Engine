#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Graphics & gfx) : __buff()
{
	__BufferData = {
		{ 0.2f,0.2f,0.2f,0.0f},
		{ 0.5f,0.5f,0.5f,0.0f},
		{ 0.5f,0.5f,0.5f,0.0f},
		{0.57735f, -0.57735f, 0.57735f},
	};
}

void DirectionalLight::Bind(Graphics & gfx)
{
	__buff.Update(__BufferData);
	__buff.Bind(gfx);
}
