#pragma once

#include "additional_headers.h"

#include "CommandBucket.h"

class Drawable
{

public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void Bind(Graphics& gfx) const;
	void LinkBucket(CommandBucket* cmdBucket);
	virtual DirectX::XMMATRIX GetTransformation() const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTransformation(Graphics& gfx) const { return DirectX::XMMatrixIdentity(); };
	virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }

	
	void PushPacket(std::shared_ptr<CommandPacket> cmd);
	UINT GetIndexCount() const;

protected:
	std::shared_ptr<IndexBuff> indexBuffer;
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<PrimitiveTopology> primitiveTopology;
	std::shared_ptr<CommandPacket> cmdPacket;

};

