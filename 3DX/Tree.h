#pragma once
#include "Drawable.h"

class Tree : public Drawable
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 Size;

	};
	std::vector<Vertex> vertexData;

public:
	Tree(Graphics& gfx, std::vector<const char*> filePath);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
};