#include "SpotLight.h"

SpotLight::SpotLight(Graphics & gfx) : __buff(gfx,3u)
{
	__BufferData =
	{
		{0.0f,0.0f,0.0f,1.0f}, //ambient
		{1.0f,1.0f,0.0f,1.0f}, //diffuse
		{1.0f,1.0f,1.0f,1.0f}, // specular
		{1.0f,0.0f,0.010f}, // attenuation
		{0.0f,70.084f,-14.0f}, // pos
		{0.000f,0.-0.9560,0.394}, // direction
		1000.0f, // range
		100.0f // spot

	};
	
}

void SpotLight::Bind(Graphics & gfx)
{
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}

//void SpotLight::Draw(Graphics & gfx)
//{
//	boxlight = new Box(gfx, __BufferData.pos.x, __BufferData.pos.y, __BufferData.pos.z);
//	boxlight->Draw(gfx);
//}
