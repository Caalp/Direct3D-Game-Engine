#include "TerrainClass.h"

TerrainClass::TerrainClass(Graphics& gfx, Camera& cam, int tW, int tH): cam(cam)
{
	terrainWidth = tW;;
	terrainHeight = tH;
	struct Vertex
	{
		float x;
		float y;
		float z;
		struct
		{
			float r;
			float g;
			float b;
		};
	};
	float posX;
	float posZ;
	float index = 0;
	std::vector<Vertex> v;
	//std::vector<Vertex> v =
	//{

	//	{ -1.0f,-1.0f,-1.0,{0.0f,0.0f,1.0f}},
	//	{ 1.0f,-1.0f,-1.0f,{1.0f,0.0f,0.5f}},
	//	{ -1.0f,1.0f,-1.0f,{0.0f,1.0f,0.5f}},
	//	{ 1.0f,1.0f,-1.0f,{1.0f,1.0f,0.0f} },
	//	{ -1.0f,-1.0f,1.0f,{0.0f,0.0f,1.0f}},
	//	{ 1.0f,-1.0f,1.0f,{1.0f,0.0f,0.5f}	},
	//	{ -1.0f,1.0f,1.0f,{0.0f,1.0f,0.5f}	},
	//	{ 1.0f,1.0f,1.0f,{1.0f,1.0f,0.0f}	},
	//	
	//};
	std::vector<WORD> indexB;
	//{
	//	0,2,1, 2,3,1,
	//	1,3,5, 3,7,5,
	//	2,6,3, 3,6,7,
	//	4,5,7, 4,7,6,
	//	0,4,2, 2,4,6,
	//	0,1,4, 1,5,4
	//	/*0,2,1,
	//	2,3,1,*/
	//};
	for (int j = 0; j < (terrainHeight - 1); j++)
	{
		for (int i = 0; i < (terrainHeight - 1); i++)
		{
			//First Line upper-left corner

			posX = float(i);
			posZ = float(j + 1);
			v.push_back({ posX,0.0f,posZ , 1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			// upper right

			posX = float(i + 1);
			posZ = float(j + 1);
			v.push_back({ posX, 0.0f, posZ,1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			// Line 2 Upper Right

			posX = float(i + 1);
			posZ = float(j + 1);

			v.push_back({ posX, 0.0f, posZ,1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			// Bottom Right 
			posX = float(i + 1);
			posZ = float(j);

			v.push_back({ posX, 0.0f, posZ,1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			// Line 3 Bottom Right

			// LINE 3
			// Bottom right.
			posX = (float)(i + 1);
			posZ = (float)j;

			v.push_back({ posX, 0.0f, posZ, 1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			

			// Bottom left.
			posX = (float)i;
			posZ = (float)j;

			v.push_back({ posX, 0.0f, posZ, 1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			

			// LINE 4
			// Bottom left.
			posX = (float)i;
			posZ = (float)j;

			v.push_back({ posX, 0.0f, posZ, 1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			

			// Upper left.
			posX = (float)i;
			posZ = (float)(j + 1);

			v.push_back({ posX, 0.0f, posZ, 1.0f,1.0f,1.0f });
			indexB.push_back(index);
			index++;
			
		}
	}

	AddToStaticBind(std::make_unique<VertexBuffer>(gfx,v));
	AddToStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.hlsl", "main", "ps_5_0"));
	auto vs = std::make_unique<VertexShader>(gfx, L"VertexShader.hlsl", "main", "vs_5_0");
	auto vsBlob = vs->GetVBlob();
	AddToStaticBind(std::move(vs));
	AddToStaticBind(std::make_unique<IndexBuff>(gfx, indexB));

	const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	AddToBinds(std::make_unique<InputLayout>(gfx, ied, vsBlob));
	AddToStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_LINELIST));
	AddBind(std::make_unique<TransCB_>(gfx, *this));
}

DirectX::XMMATRIX TerrainClass::GetViewXM() const
{
	return cam.GetViewMatrix();
}

DirectX::XMMATRIX TerrainClass::GetWorldXM() const
{
	return DirectX::XMMatrixTranslation(0.2175, 0.1275, 4.0f);
}

DirectX::XMMATRIX TerrainClass::GetProjXM() const
{
	return DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f);
}