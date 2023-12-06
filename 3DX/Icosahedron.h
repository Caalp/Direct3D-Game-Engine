#pragma once
#include "Drawable.h"

class Icosahedron : public Drawable
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 texCoord;
	};
public:
	Icosahedron(Graphics& gfx, std::string name);
	void SubDivide(Graphics& gfx, unsigned int numTimesDivide);
	void Utilize(Graphics& gfx);
private:
	std::vector<Vertex> vertices;
	std::vector<WORD> indices;
};