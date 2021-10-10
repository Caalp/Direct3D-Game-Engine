#pragma once
#include <vector>
#include <DirectXMath.h>
#include <string>
struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT2 texCoord;
};
class Sphere
{
	
public:

	Sphere(std::string name, float radius, unsigned int sliceCount, unsigned int stackCount);	
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};