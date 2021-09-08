#pragma once
#include "Component.h"
#include "Technique.h"
#include "VertexBuffer.h"
#include "PrimitiveTopology.h"
#include "IndexBuff.h"
#include "TransformationBuffer.h"
#include "json/json.hpp"

class Graphics;

class RenderableComponent : public Component
{
	using json = nlohmann::json;
	friend class Entity;
	friend class RenderSystem;
public:
	RenderableComponent() = default;

	//RenderableComponent(const RenderableComponent& rhs) = delete;
	//RenderableComponent& operator=(const RenderableComponent& rhs) = delete;

	//RenderableComponent(RenderableComponent&& rhs) = default;
	//RenderableComponent& operator=(RenderableComponent&& rhs) = default;

	//

	//void SetVertexBuffer(std::unique_ptr<VertexBuffer> vb);
	//void SetTopology(std::unique_ptr<PrimitiveTopology> pt);
	//void SetIndexBuffer(std::unique_ptr<IndexBuff> ib);
	//U32 IndexCount() const;
	//void AppendTechnique(const Technique& tech);
	//void Bind() const;
	//static RenderableComponent Load(const char* filepath);
	//virtual void DrawImgui() override;
public:
	//std::weak_ptr<VSConstBuff<std::vector<char>>> m_TBuffer;
protected:

	//std::unique_ptr<VertexBuffer> vertexBuffer;
	//std::unique_ptr<PrimitiveTopology> primitiveTopology;
	//std::unique_ptr<IndexBuff> indexBuffer;
	//
	//std::vector<Technique> techniques;

};