#include "Drawable.h"

#include "RenderGraph.h"

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

void Drawable::AppendTechnique(const Technique& tech)
{
	techniques.push_back(tech);
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



