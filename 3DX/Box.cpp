#include "Box.h"
#include "Surface.h"
#include "TextureLoader.h"


Box::Box(Graphics & gfx, float x, float y, float z) :
	x(x), y(y), z(z)
{

	if (!isStaticallyBinded())
	{
		struct Vertex
		{

			DirectX::XMFLOAT3 Pos;
			DirectX::XMFLOAT2 texCoord;
			
		};
		
		
		std::vector<Vertex> vertices;
		vertices.resize(24);
		//float w = 1.0f;
		//float h = 1.0f;
		//float d = 1.0f;
		//constexpr float side = 1.0f / 2.0f;
		//
		//vertices[0] = { {-w,-h,-d}, {0,1} };
		//vertices[1] = { {-w,h,-d}, {0,0} };
		//vertices[2] = { {w,h,-d}, {1,0} };
		//vertices[3] = { {w,-h,-d}, {1,1} };
		//
		////Back Face
		//vertices[4] = { {-w,-h,d}, {1,1} };
		//vertices[5] = { {w,-h,d}, {0,1} };
		//vertices[6] = { {w,h,d}, {0,0} };
		//vertices[7] = { {-w,h,d}, {1,0} };

		////top Face
		//vertices[8] = { {-w,h,-d}, {0,1} };
		//vertices[9] = { {-w,h,d}, {0,0} };
		//vertices[10] = { {w,h,d}, {1,0} };
		//vertices[11] = { {w,h,-d}, {1,1} };

		////Bottom Face
		//vertices[12] = { {-w,-h,-d}, {1,1} };
		//vertices[13] = { {w,-h,-d}, {0,1} };
		//vertices[14] = { {w,-h,d}, {0,0} };
		//vertices[15] = { {-w,-h,d}, {1,0} };

		////Left Face
		//vertices[16] = { {-w,-h,d}, {0,1} };
		//vertices[17] = { {-w,h,d}, {0,0} };
		//vertices[18] = { {-w,h,-d}, {1,0} };
		//vertices[19] = { {-w,-h,-d}, {1,1} };

		////Right Face

		//vertices[20] = { {w,-h,-d}, {0,1} };
		//vertices[21] = { {w,h,-d}, {0,0} };
		//vertices[22] = { {w,h,d}, {1,0} };
		//vertices[23] = { {w,-h,d}, {1,1} };

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
		vertices[0].texCoord = { 0.0f,0.0f };
		vertices[1].texCoord = { 1.0f,0.0f };
		vertices[2].texCoord = { 0.0f,1.0f };
		vertices[3].texCoord = { 1.0f,1.0f };
		vertices[4].texCoord = { 0.0f,0.0f };
		vertices[5].texCoord = { 1.0f,0.0f };
		vertices[6].texCoord = { 0.0f,1.0f };
		vertices[7].texCoord = { 1.0f,1.0f };
		vertices[8].texCoord = { 0.0f,0.0f };
		vertices[9].texCoord = { 1.0f,0.0f };
		vertices[10].texCoord = { 0.0f,1.0f };
		vertices[11].texCoord = { 1.0f,1.0f };
		vertices[12].texCoord = { 0.0f,0.0f };
		vertices[13].texCoord = { 1.0f,0.0f };
		vertices[14].texCoord = { 0.0f,1.0f };
		vertices[15].texCoord = { 1.0f,1.0f };
		vertices[16].texCoord = { 0.0f,0.0f };
		vertices[17].texCoord = { 1.0f,0.0f };
		vertices[18].texCoord = { 0.0f,1.0f };
		vertices[19].texCoord = { 1.0f,1.0f };
		vertices[20].texCoord = { 0.0f,0.0f };
		vertices[21].texCoord = { 1.0f,0.0f };
		vertices[22].texCoord = { 0.0f,1.0f };
		vertices[23].texCoord = { 1.0f,1.0f };
		
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexBlenderPS.cso"));
		
		

		auto vs = std::make_unique<VertexShader>(gfx, L"TexBlenderVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		std::vector<unsigned short> indices =
		{
			
				0,2,1,    2,3,1,
				4,5,7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23

		};
		TextureLoader texLoader("WireFence.dds");
		AddStaticBind(std::make_unique<RasterizerState>(gfx));
		AddStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		//AddStaticBind(std::make_unique<BlendState>(gfx));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "texCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
		};
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<Texture>(gfx, texLoader));
		AddStaticBind(std::make_unique<SamplerState>(gfx));
	}
	else
	{
		SetIndexBufferFromStatic();
	}
		 
	 AddBind(std::make_unique<TransformationBuffer>(gfx,*this));
}

void Box::Update(float ft)
{
	pitch += ft;
	yaw += ft;
	roll += ft;
	
}

DirectX::XMMATRIX Box::GetTransformation() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y,z);
	//return DirectX::XMMatrixIdentity();
}









