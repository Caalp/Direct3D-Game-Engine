#include "PointLight.h"

PointLight::PointLight(Graphics & gfx) : __buff(gfx,2u)
{
	
	__BufferData =
	{
		{0.3f,0.3f,0.3f,1.0f},//ambient
		{0.7f,0.7f,0.7f,1.0f},//diffuse
		{0.7f,0.7f,0.7f,1.0f},//specular
		{0.0f,0.1f,0.0f}, //attenuation
		{ 0.0f,20.0f,-10.0f}, //position
		25.0f//range
		/*{ 1.5f,14.0f,-4.5f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,*/
	};
	
}

void PointLight::Bind(Graphics & gfx)
{
	
	__buff.Update(gfx, __BufferData);
	__buff.Bind(gfx);
}

/*void PointLight::SetPointLightPosition(dx::XMFLOAT3 v)
{
	__BufferData.pos = v;
	
}*/

//void PointLight::Draw(Graphics & gfx)
//{
//	boxlight = new Box(gfx, __BufferData.pos.x, __BufferData.pos.y, __BufferData.pos.z);
//	boxlight->Draw(gfx);
//}
