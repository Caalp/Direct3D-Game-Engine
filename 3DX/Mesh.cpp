#include "Mesh.h"
//
//
////
////struct Vertices
////{
////	DirectX::XMFLOAT3 pos;
////	DirectX::XMFLOAT3 normal;
////	DirectX::XMFLOAT3 texCoordinates;
////	//DirectX::XMFLOAT4 weights;
////	//Byte boneIndices[4];
////};
//
void  Mesh::ParseMesh(const aiMesh& mesh)
{
	struct TransformBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldInverseTranspose;
	} tb;
	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		Vertices vertices;
		vertices.pos.x = mesh.mVertices[i].x;
		vertices.pos.y = mesh.mVertices[i].y;
		vertices.pos.z = mesh.mVertices[i].z;

		if (mesh.mNormals != NULL)
		{
			vertices.normal.x = mesh.mNormals[i].x;
			vertices.normal.y = mesh.mNormals[i].y;
			vertices.normal.z = mesh.mNormals[i].z;
		}
		else
		{
			vertices.normal.x = 0.0f;
			vertices.normal.y = 0.0f;
			vertices.normal.z = 0.0f;
		}

		if (mesh.mTextureCoords[0])
		{
			vertices.texCoordinates.x = mesh.mTextureCoords[0][i].x;
			vertices.texCoordinates.y = mesh.mTextureCoords[0][i].y;
			vertices.texCoordinates.z = mesh.mMaterialIndex;

		}
		else
		{
			vertices.texCoordinates = DirectX::XMFLOAT3(0.0f, 0.0f, mesh.mMaterialIndex);
		}
	/*	vertices.weights.x = 0.0f;
		vertices.weights.y = 0.0f;
		vertices.weights.z = 0.0f;
		vertices.weights.w = 0.0f;

		vertices.boneIndices[0] = 0;
		vertices.boneIndices[1] = 0;
		vertices.boneIndices[2] = 0;
		vertices.boneIndices[3] = 0;*/

		m_vertices.push_back(vertices);
	}

	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		aiFace face = mesh.mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			m_indices.push_back(face.mIndices[j]);

	}
	
	m_vertexBuffer = std::make_unique<VertexBuffer>(m_vertices);
	m_indexBuffer = std::make_unique<IndexBuff>(m_indices);
	m_topology = std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	tb.world = DirectX::XMMatrixIdentity();
	tb.worldInverseTranspose = DirectX::XMMatrixIdentity();
	std::vector<char> bytes;
	bytes.resize(sizeof(tb));
	memcpy(bytes.data(), &tb, sizeof(tb));
	// m_transformBuffer = std::make_unique<VSConstBuff<std::vector<char>>>(tb); !! doesn't work directly initializing with data
	m_transformBuffer = std::make_unique<VSConstBuff<std::vector<char>>>(sizeof(TransformBuffer));
	m_transformBuffer->Update(bytes, bytes.size());

}
//
//void  Mesh::ParseMesh(const aiMesh& mesh)
//{
//
//	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
//	{
//		Vertices vertices;
//		vertices.pos.x = mesh.mVertices[i].x;
//		vertices.pos.y = mesh.mVertices[i].y;
//		vertices.pos.z = mesh.mVertices[i].z;
//
//		if (mesh.mNormals != NULL)
//		{
//			vertices.normal.x = mesh.mNormals[i].x;
//			vertices.normal.y = mesh.mNormals[i].y;
//			vertices.normal.z = mesh.mNormals[i].z;
//		}
//		else
//		{
//			vertices.normal.x = 0.0f;
//			vertices.normal.y = 0.0f;
//			vertices.normal.z = 0.0f;
//		}
//
//		if (mesh.mTextureCoords[0])
//		{
//			vertices.texCoordinates.x = mesh.mTextureCoords[0][i].x;
//			vertices.texCoordinates.y = mesh.mTextureCoords[0][i].y;
//			vertices.texCoordinates.z = mesh.mMaterialIndex;
//
//		}
//		else
//		{
//			vertices.texCoordinates = DirectX::XMFLOAT3(0.0f, 0.0f, mesh.mMaterialIndex);
//		}
//
//
//		m_vertices.push_back(vertices);
//	}
//
//	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
//	{
//		aiFace face = mesh.mFaces[i];
//		for (unsigned int j = 0; j < face.mNumIndices; j++)
//			indices.push_back(face.mIndices[j]);
//
//	}
//
//}
//
