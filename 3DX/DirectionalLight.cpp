#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Graphics & gfx) : __buff(gfx)
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
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}
