#include "Drawable.h"
#include "Scene.h"
#include "RenderGraph.h"
#include <sstream>
#include "SceneRenderer.h"
#include "Technique.h"

Drawable::Drawable(std::string id) 
	: objectName(id)
{}

void Drawable::Bind(Graphics& gfx) const
{
	vertexBuffer->Bind(gfx);
	primitiveTopology->Bind(gfx);
	indexBuffer->Bind(gfx);
}

Scene Drawable::GetScene()
{
	return SceneRenderer::scene;
}

void Drawable::LinkTechnique(RenderGraph& rg)
{
	for (auto& elem : techniques)
	{
		elem.Link(rg);
	}
}

void Drawable::SetTransformationXM(const DirectX::XMMATRIX& xm)
{
	transformation  = std::make_shared<DirectX::XMMATRIX>(xm);
}

void Drawable::RotateGeometry(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}

void Drawable::TranslateGeometry(float x, float y, float z)
{
	this->posX = x;
	this->posY = y;
	this->posZ = z;
}

void Drawable::Update(float ft)
{
	std::ostringstream ss;
	ss << objectName << " :" << "posX: " << posX << " posY: " << posY << " posZ: " << posZ << std::endl;
	std::string s(ss.str());
	OutputDebugString(s.c_str());
	pitch += ft;
	yaw += ft;
	roll += ft;
}

void Drawable::AppendTechnique(const Technique& tech)
{
	for (const auto& tec : techniques)
	{
		if (tec.GetName() == tech.GetName())
		{
			return;
		}
	}
	if (tech.GetName() == objectName)
	{
		techniques.push_back(tech);
	}
}

void Drawable::Submit(size_t channel)
{
	for (auto& t : techniques)
	{
		t.Submit(*this,channel);
	}
}

void Drawable::SetName(std::string name)
{
	objectName = name;
}

std::string Drawable::GetName() const
{
	return objectName;
}

UINT Drawable::GetIndexCount() const
{
	return indexBuffer->GetIndexCount();
}

void Drawable::SetID(uint32_t id)
{
	m_id = id;
}

uint32_t Drawable::GetID() const
{
	return m_id;
}