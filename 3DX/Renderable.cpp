#include "Renderable.h"


Renderable::Renderable()
{
	// Submits itself to the renderer

}

void Renderable::Bind() const
{
	m_vertexBuffer->Bind();
	m_topology->Bind();
	m_indexBuffer->Bind();
	m_transformBuffer->Bind(0u, 1u);

}

void Renderable::SetVertexBuffer(Ptr<VertexBuffer> vb)
{
	m_vertexBuffer = std::move(vb);
}

void Renderable::SetTopology(Ptr<PrimitiveTopology> pt)
{
	m_topology = std::move(pt);
}

void Renderable::SetIndexBuffer(Ptr<IndexBuff> ib)
{
	m_indexBuffer = std::move(ib);
}

U32 Renderable::GetIndexCount() const
{
	return m_indexBuffer->GetIndexCount();
}

void Renderable::AppendTechnique(const Technique& tech)
{
	for (const auto& tec : m_techniques)
	{
		if (tec.GetName() == tech.GetName())
		{
			return;
		}
	}


	m_techniques.push_back(tech);
}
