#pragma once
#include "additional_headers.h"
#include "Entity.h"
#include "Technique.h"

// Drawable inherited from entity
// Can we mark an entity as drawable and add component drawable to add drawable feature 
// With that we can call all objects marked drawable and draw them later
// How can we make Drawable lightweight otherwise?



class RenderGraph;

class Technique;
//class Graphics;


class Drawable : public Entity
{
	friend class Mesh;
public:
	Drawable() = default;
	//Drawable(std::string id);
	//Drawable(const Drawable&) = delete;
	void Bind(Graphics& gfx) const;
	//Scene GetScene();
	void LinkTechnique(RenderGraph& rg);
	//const DirectX::XMMATRIX& GetTransformation() const { return *transformation; };
	//virtual DirectX::XMMATRIX GetTransformation(Graphics& gfx) const { return DirectX::XMMatrixIdentity(); };
	//virtual DirectX::XMMATRIX GetTexTransformXM() const { return DirectX::XMMatrixIdentity(); }
	//void SetTransformationXM(const DirectX::XMMATRIX& xm);
	//void RotateGeometry(float pitch, float yaw, float roll);
	//void TranslateGeometry(float x, float y, float z);
	//void Update(float dt);
	void AppendTechnique(const Technique& tech);
	
	//void SetName(std::string name);
	//std::string GetName() const;

	//void SetID(uint32_t id);
	//uint32_t GetID() const;

protected:
	//std::string objectName;
	//uint32_t m_id;
	std::unique_ptr<VertexBuffer> vertexBuffer;
	std::unique_ptr<PrimitiveTopology> primitiveTopology;
	std::unique_ptr<IndexBuff> indexBuffer;
	std::vector<Technique> techniques;
protected:
	//std::shared_ptr<DirectX::XMMATRIX> transformation;
	//float pitch{ 1.0f }, yaw{ 1.0f }, roll{1.0f};
	//float posX{ 0.0f }, posY{ 0.0f }, posZ{0.0f};
};


