//#pragma once
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "Entity.h"
#include "Types.h"
#include <DirectXMath.h>
#include "Renderable.h"

class Mesh : public Renderable
{
	struct Vertices
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT3 texCoordinates;
		//DirectX::XMFLOAT4 weights;
		//Byte boneIndices[4];
	};
public:
	Mesh()
	{
	}
	~Mesh()
	{
		std::cout << "Destructor Mesh" << std::endl;
	}
	void ParseMesh(const aiMesh& mesh);

	
private:
	std::vector<Vertices> m_vertices;
	std::vector<U16> m_indices;
	std::vector<Technique> m_techniques;
};