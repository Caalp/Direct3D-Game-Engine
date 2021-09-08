#pragma once
#include "VertexBuffer.h"
#include "IndexBuff.h"
#include "PrimitiveTopology.h"
#include "Technique.h"
#include "Types.h"
#include "TransformationBuffer.h"

class Renderable
{
	friend class Renderer;
public:
	Renderable();
	void Bind() const;
	virtual ~Renderable()
	{
		std::cout << "Renderable destructor called! " << std::endl;
	}
	void SetVertexBuffer(Ptr<VertexBuffer> vb);
	void SetTopology(Ptr<PrimitiveTopology> pt);
	void SetIndexBuffer(Ptr<IndexBuff> ib);
	U32 GetIndexCount() const;
	void AppendTechnique(const Technique& tech);

protected:
	Ptr<VSConstBuff<std::vector<char>>> m_transformBuffer;
	Ptr<VertexBuffer> m_vertexBuffer;
	Ptr<IndexBuff> m_indexBuffer;
	Ptr<PrimitiveTopology> m_topology;
	std::vector<Technique> m_techniques;

};