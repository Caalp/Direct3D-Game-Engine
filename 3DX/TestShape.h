#pragma once
#include "defines.h"
#include "Backend.h"
#include "buckets.h"
#include <vector>
#include "TextureDB.h"

class TestShape
{

	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 TexCoord;

	};


	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices =
	{

			0,2,1,    2,3,1,
			4,5,7,    4,7,6,
			8,10, 9,  10,11,9,
			12,13,15, 12,15,14,
			16,17,18, 18,17,19,
			20,23,21, 20,22,23

	};
public:
	TestShape()
	{
#pragma region CreateBox
		
		vertices.resize(24);


		constexpr float side = 1.0f / 2.0f;


		vertices[0].Pos = { -side,-side,-side };// 0 near side
		vertices[1].Pos = { side,-side,-side };// 1
		vertices[2].Pos = { -side,side,-side };// 2
		vertices[3].Pos = { side,side,-side };// 3
		vertices[4].Pos = { -side,-side,side };// 4 far side
		vertices[5].Pos = { side,-side,side };// 5
		vertices[6].Pos = { -side,side,side };// 6
		vertices[7].Pos = { side,side,side };// 7
		vertices[8].Pos = { -side,-side,-side };// 8 left side
		vertices[9].Pos = { -side,side,-side };// 9
		vertices[10].Pos = { -side,-side,side };// 10
		vertices[11].Pos = { -side,side,side };// 11
		vertices[12].Pos = { side,-side,-side };// 12 right side
		vertices[13].Pos = { side,side,-side };// 13
		vertices[14].Pos = { side,-side,side };// 14
		vertices[15].Pos = { side,side,side };// 15
		vertices[16].Pos = { -side,-side,-side };// 16 bottom side
		vertices[17].Pos = { side,-side,-side };// 17
		vertices[18].Pos = { -side,-side,side };// 18
		vertices[19].Pos = { side,-side,side };// 19
		vertices[20].Pos = { -side,side,-side };// 20 top side
		vertices[21].Pos = { side,side,-side };// 21
		vertices[22].Pos = { -side,side,side };// 22
		vertices[23].Pos = { side,side,side };// 23
		vertices[0].TexCoord = { 0.0f,0.0f };
		vertices[1].TexCoord = { 1.0f,0.0f };
		vertices[2].TexCoord = { 0.0f,1.0f };
		vertices[3].TexCoord = { 1.0f,1.0f };
		vertices[4].TexCoord = { 0.0f,0.0f };
		vertices[5].TexCoord = { 1.0f,0.0f };
		vertices[6].TexCoord = { 0.0f,1.0f };
		vertices[7].TexCoord = { 1.0f,1.0f };
		vertices[8].TexCoord = { 0.0f,0.0f };
		vertices[9].TexCoord = { 1.0f,0.0f };
		vertices[10].TexCoord = { 0.0f,1.0f };
		vertices[11].TexCoord = { 1.0f,1.0f };
		vertices[12].TexCoord = { 0.0f,0.0f };
		vertices[13].TexCoord = { 1.0f,0.0f };
		vertices[14].TexCoord = { 0.0f,1.0f };
		vertices[15].TexCoord = { 1.0f,1.0f };
		vertices[16].TexCoord = { 0.0f,0.0f };
		vertices[17].TexCoord = { 1.0f,0.0f };
		vertices[18].TexCoord = { 0.0f,1.0f };
		vertices[19].TexCoord = { 1.0f,1.0f };
		vertices[20].TexCoord = { 0.0f,0.0f };
		vertices[21].TexCoord = { 1.0f,0.0f };
		vertices[22].TexCoord = { 0.0f,1.0f };
		vertices[23].TexCoord = { 1.0f,1.0f };

		/*vertices[0].Normal = {1.0f,0.0f,0.0f };
		vertices[1].Normal = { 1.0f,0.0f,0.0f };
		vertices[2].Normal = { 1.0f,0.0f,0.0f };
		vertices[3].Normal = { 1.0f,0.0f,0.0f };
		vertices[4].Normal = { -1.0f,0.0f,0.0f };
		vertices[5].Normal = { -1.0f,0.0f,0.0f };
		vertices[6].Normal = { -1.0f,0.0f,0.0f };
		vertices[7].Normal = { -1.0f,0.0f,0.0f };
		vertices[8].Normal = { 0.0f,0.0f,-1.0f };
		vertices[9].Normal = { 0.0f,0.0f,-1.0f };
		vertices[10].Normal = { 0.0f,0.0f,-1.0f };
		vertices[11].Normal = { 0.0f,0.0f,-1.0f };
		vertices[12].Normal = { 0.0f,0.0f,1.0f };
		vertices[13].Normal = { 0.0f,0.0f,1.0f };
		vertices[14].Normal = { 0.0f,0.0f,1.0f };
		vertices[15].Normal = { 0.0f,0.0f,1.0f };
		vertices[16].Normal = { -1.0f,0.0f,0.0f };
		vertices[17].Normal = { -1.0f,0.0f,0.0f };
		vertices[18].Normal = { -1.0f,0.0f,0.0f };
		vertices[19].Normal = { -1.0f,0.0f,0.0f };
		vertices[20].Normal = { 1.0f,0.0f,0.0f };
		vertices[21].Normal = { 1.0f,0.0f,0.0f };
		vertices[22].Normal = { 1.0f,0.0f,0.0f };
		vertices[23].Normal = { 1.0f,0.0f,0.0f };*/


		

#pragma endregion
	

	}
	struct modelTransformBuffer
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX inverseTransform;
	} modelTransform;
	void Init(TextureHandle textureHandle,DirectX::XMFLOAT3 pos)
	{

		m_pos = pos;

		modelTransform.model = DirectX::XMMatrixIdentity() * DirectX::XMMatrixTranslation(pos.x,pos.y,pos.z);
		modelTransform.inverseTransform = DirectX::XMMatrixIdentity();
		auto xm = DirectX::XMMatrixIdentity();
		auto t1 = sizeof(xm);
		auto t2 = sizeof(xm.r[1]);
		//m_vsh = backend::CreateShader("ColorBlenderVS.cso", ShaderType::VertexShader);
		m_vsh = backend::CreateShader("VS_TextureMapping.cso", ShaderType::VertexShader);

		std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		m_vsCB = backend::CreateConstantBuffer(BufferType::VSConstantBuffer, &modelTransform, sizeof(modelTransform), sizeof(DirectX::XMMATRIX), 0u);
		backend::SortKey key;
		key.m_sortKey = TORC_STATE_DISCARD_ALL ;
		command::BindSampler* sampler = bucket::testBucket.AddCommand<command::BindSampler>(key, 0);
		sampler->Sampler = backend::CreateSampler();

		command::DrawIndexed* draw = bucket::testBucket.AppendCommand<command::DrawIndexed>(sampler, 0);
		draw->indexBuffer = backend::CreateIndexBuffer(indices.data(), (indices.size() * sizeof(U16)), sizeof(U16));
		draw->vertexBuffer = backend::CreateVertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex), sizeof(Vertex));
		draw->vertexLayout = backend::CreateVertexLayout(m_vsh, ied.data(), ied.size());
		draw->texHandle = textureHandle;
		draw->indexCount = indices.size();
		draw->baseVertexLocation = 0;
		draw->startIndexLocation = 0u;
		draw->drawInfo.cb = m_vsCB;
		draw->drawInfo.ps = backend::CreateShader("PS_TextureMapping.cso", ShaderType::PixelShader);
		draw->drawInfo.vs = m_vsh;
	}
	void Update(float dt)
	{
		static float step = dt;
		step += dt;
		modelTransform.model = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 1.5708 * step, 0.0f) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		modelTransform.inverseTransform = DirectX::XMMatrixIdentity();
		backend::UpdateConstantBuffer(m_vsCB, &modelTransform);
	}
private:
	DirectX::XMFLOAT3 m_pos;
	IndexBufferHandle m_ibh;
	VertexBufferHandle m_vbh;
	ShaderHandle m_psh;
	ShaderHandle m_vsh;
	ConstantBufferHandle m_vsCB;
	VertexLayoutHandle m_vlh;
};
