#include "Box.h"
#include "additional_headers.h"
#include "Texture.h"
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
		struct PixelShaderConstants
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[8];
		};
		const PixelShaderConstants cb2 =
		{
			{
				{ 1.0f,1.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,0.0f,1.0f },
				{ 0.0f,1.0f,1.0f },
				{ 0.0f,0.0f,0.0f },
			}
		};
		
		std::vector<Vertex> vertices;
		vertices.resize(24);
		float w = 0.5f;
		float h = 0.5f;
		float d = 0.5f;
		constexpr float side = 1.0f / 2.0f;
		/*vertices[0].Pos = DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0);
		vertices[1].Pos = DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertices[2].Pos = DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertices[3].Pos = DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertices[4].Pos = DirectX::XMFLOAT3(-1.0, -1.0f, 1.0f);
		vertices[5].Pos = DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertices[6].Pos = DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertices[7].Pos = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		
		vertices[0].texCoord = DirectX::XMFLOAT2(0.0f, 1.0f);
		vertices[1].texCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
		vertices[2].texCoord = DirectX::XMFLOAT2(0.0f, 0.0f);

		vertices[3].texCoord = DirectX::XMFLOAT2(1.0f, 0.0f);
		vertices[4].texCoord = DirectX::XMFLOAT2(0.0f, 1.0f);
		vertices[5].texCoord = DirectX::XMFLOAT2(0.0f, 1.0f);
		vertices[6].texCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		vertices[7].texCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		*/
		//Front Face
		vertices[0] = { {-w,-h,-d}, {0,1} };
		vertices[1] = { {-w,h,-d}, {0,0} };
		vertices[2] = { {w,h,-d}, {1,0} };
		vertices[3] = { {w,-h,-d}, {1,1} };
		
		//Back Face
		vertices[4] = { {-w,-h,d}, {1,1} };
		vertices[5] = { {w,-h,d}, {0,1} };
		vertices[6] = { {w,h,d}, {0,0} };
		vertices[7] = { {-w,h,d}, {1,0} };

		//top Face
		vertices[8] = { {-w,h,-d}, {0,1} };
		vertices[9] = { {-w,h,d}, {0,0} };
		vertices[10] = { {w,h,d}, {1,0} };
		vertices[11] = { {w,h,-d}, {1,1} };

		//Bottom Face
		vertices[12] = { {-w,-h,-d}, {1,1} };
		vertices[13] = { {w,-h,-d}, {0,1} };
		vertices[14] = { {w,-h,d}, {0,0} };
		vertices[15] = { {-w,-h,d}, {1,0} };

		//Left Face
		vertices[16] = { {-w,-h,d}, {0,1} };
		vertices[17] = { {-w,h,d}, {0,0} };
		vertices[18] = { {-w,h,-d}, {1,0} };
		vertices[19] = { {-w,-h,-d}, {1,1} };

		//Right Face

		vertices[20] = { {w,-h,-d}, {0,1} };
		vertices[21] = { {w,h,-d}, {0,0} };
		vertices[22] = { {w,h,d}, {1,0} };
		vertices[23] = { {w,-h,d}, {1,1} };

		//vertices[0] = { { -side,-side,-side },{ 0.0f,0.0f } };// 0 near side
		//vertices[1] = { { side,-side,-side },{ 1.0f,0.0f } };// 1
		//vertices[2] = { { -side,side,-side },{ 0.0f,1.0f } };// 2
		//vertices[3] = { { side,side,-side } ,{ 1.0f,1.0f } };// 3
		//vertices[4] = { { -side,-side,side } ,{ 0.0f,0.0f } };// 4 far side
		//vertices[5] = { { side,-side,side } ,{ 1.0f,0.0f } };// 5
		//vertices[6] = { { -side,side,side } ,{ 0.0f,1.0f } };// 6
		//vertices[7] = { { side,side,side } ,{ 1.0f,1.0f } };// 7
		//vertices[8] = { { -side,-side,-side }, { 0.0f,0.0f } };// 8 left side
		//vertices[9] = { { -side,side,-side }, { 1.0f,0.0f } };// 9
		//vertices[10] = { { -side, -side, side },{ 0.0f,1.0f } };// 10
		//vertices[11] = { { -side,side,side },{ 1.0f,1.0f } };// 11
		//vertices[12] = { { side,-side,-side },{ 0.0f,0.0f } };// 12 right side
		//vertices[14] = { { side,-side,side },{ 1.0f,0.0f } };// 14
		//vertices[13] = { { side,side,-side },{ 0.0f,1.0f } };// 13
		//vertices[15] = { { side,side,side },{ 1.0f,1.0f } };// 15
		//vertices[16] = { { -side,-side,-side },{ 0.0f,0.0f } };// 16 bottom side
		//vertices[17] = { { side,-side,-side },{ 1.0f,0.0f } };// 17
		//vertices[18] = { { -side,-side,side },{ 0.0f,1.0f } };// 18
		//vertices[19] = { { side,-side,side } ,{ 1.0f,1.0f } };// 19
		//vertices[20] = { { -side,side,-side },{ 0.0f,0.0f } };// 20 top side
		//vertices[21] = { { side,side,-side } ,{ 1.0f,0.0f } };// 21
		//vertices[22] = { { -side,side,side },{ 0.0f,1.0f } };// 22
		//vertices[23] = { { side,side,side } ,{ 1.0f,1.0f } };// 23
		
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		AddStaticBind(std::make_unique< PSConstBuff <PixelShaderConstants>>(gfx, cb2,1u));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"TexBlenderPS.cso"));
		
		

		auto vs = std::make_unique<VertexShader>(gfx, L"TexBlenderVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		std::vector<WORD> indices =
		{
			//0,2,1, 2,3,1, // Front Face
			//1,3,5, 3,7,5, // Right face
			//2,6,3, 3,6,7, // Top face
			//4,5,7, 4,7,6, // Back Face
			//0,4,2, 2,4,6, // Left Face
			//0,1,4, 1,5,4  //Bottom Face
			//0,2,1, 2,3,1,
			//4,5,6, 6,5,7,
			/*8,9,10, 10,9,11,
			12,13,14, 12,14,15,
			16,17,18, 18,17,19,
			20,21,22, 22,21,23*/
			/*0,2, 1,    2,3,1,
				4,5, 7,    4,7,6,
				8,10, 9,  10,11,9,
				12,13,15, 12,15,14,
				16,17,18, 18,17,19,
				20,23,21, 20,22,23*/
			0,1,2, 0,2,3,
			4,5,6, 4,6,7,
			8,9,10, 8,10,11,
			12,13,14, 12,14,15,
			16,17,18, 16,18,19,
			20,21,22, 20,22,23

			

		};
		TextureLoader texLoader("kappa50.bmp");
		AddStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		
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
	//struct VSMaterialConstant
	//{
	//	DirectX::XMMATRIX model;
	//	DirectX::XMMATRIX worldviewProj;
	//	DirectX::XMFLOAT3 eyePos;
	//	//float padding;
	//	
	//} VSConst;
	//VSConst.model = DirectX::XMMatrixTranspose(GetTransformation());
	//VSConst.worldviewProj = DirectX::XMMatrixTranspose(GetTransformation() * gfx.GetCamera());
	//VSConst.eyePos = DirectX::XMFLOAT3(1.0f,1.0f,1.0f);

	//AddBind(std::make_unique<VSConstBuff<VSMaterialConstant>>(gfx, VSConst));
	 
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









