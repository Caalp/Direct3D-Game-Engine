#include "Drawable.h"

#include "RenderGraph.h"

Drawable::Drawable(std::string id) : objectID(id)
{
}

void Drawable::Bind(Graphics& gfx) const
{
	vertexBuffer->Bind(gfx);
	primitiveTopology->Bind(gfx);
	indexBuffer->Bind(gfx);
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
	transformation = std::move(xm);
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
	pitch += ft;
	yaw += ft;
	roll += ft;
	SetTransformationXM(DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(posX, posY, posZ));
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
	if (tech.GetName() == objectID)
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

UINT Drawable::GetIndexCount() const
{
	return indexBuffer->GetIndexCount();
}



