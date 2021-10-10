#pragma once
#include "Sphere.h"
#include "defines.h"
#include <string>
#include <memory>



class SkyBox
{
public:
	SkyBox(std::string name, float radius, unsigned int sliceCount, unsigned int stackCount);
	void Init();
private:
	std::unique_ptr<Sphere> m_sphere;
	IndexBufferHandle m_ibh;
	VertexBufferHandle m_vbh;
	ShaderHandle m_psh;
	ShaderHandle m_vsh;
	ConstantBufferHandle m_vsCB;
	VertexLayoutHandle m_vlh;
	TextureHandle m_th;
	SamplerHandle m_sh;
};