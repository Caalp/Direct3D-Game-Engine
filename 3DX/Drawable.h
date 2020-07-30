#pragma once

#include "additional_headers.h"
#include "Technique.h"

class RenderGraph;

class Drawable
{

public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void Bind(Graphics& gfx) const;
	
	void LinkTechnique(RenderGraph& rg);
	virtual DirectX::XMMATRIX GetTransformation() const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTransformation(Graphics& gfx) const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }

	void AppendTechnique(const Technique& tech);
	void Submit(size_t channel);
	UINT GetIndexCount() const;

protected:
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<PrimitiveTopology> primitiveTopology;
	std::unique_ptr<IndexBuff> indexBuffer;
	std::vector<Technique> techniques;

};


