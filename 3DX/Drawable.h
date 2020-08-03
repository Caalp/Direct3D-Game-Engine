#pragma once

#include "additional_headers.h"
#include "Technique.h"

class RenderGraph;

class Drawable
{

public:
	Drawable(std::string id);
	Drawable(const Drawable&) = delete;
	void Bind(Graphics& gfx) const;
	
	void LinkTechnique(RenderGraph& rg);
	DirectX::XMMATRIX GetTransformation() const { return transformation; };
	virtual DirectX::XMMATRIX GetTransformation(Graphics& gfx) const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }
	void SetTransformationXM(const DirectX::XMMATRIX& xm);
	void RotateGeometry(float pitch, float yaw, float roll);
	void TranslateGeometry(float x, float y, float z);
	void Update(float dt);
	void AppendTechnique(const Technique& tech);
	void Submit(size_t channel);
	UINT GetIndexCount() const;

protected:
	std::string objectID;
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<PrimitiveTopology> primitiveTopology;
	std::unique_ptr<IndexBuff> indexBuffer;
	std::vector<Technique> techniques;
protected:
	DirectX::XMMATRIX transformation;
	float pitch{ 1.0f }, yaw{ 1.0f }, roll{1.0f};
	float posX{ 0.0f }, posY{ 0.0f }, posZ{0.0f};
};


