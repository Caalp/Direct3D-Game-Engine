#include "Box.h"
#include "additional_headers.h"
#include "Texture.h"
#include "Surface.h"


Box::Box(Graphics & gfx, float x, float y, float z) :
	x(x), y(y), z(z)
{

	
	
		struct Vertex
		{

			DirectX::XMFLOAT3 pos;
			
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
		vertices.resize(8);
		
		vertices[0].pos = DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0);
		vertices[1].pos = DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f);
		vertices[2].pos = DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f);
		vertices[3].pos = DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f);
		vertices[4].pos = DirectX::XMFLOAT3(-1.0, -1.0f, 1.0f);
		vertices[5].pos = DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f);
		vertices[6].pos = DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f);
		vertices[7].pos = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		
		std::vector<WORD> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4

		};
		
		vertexBuffer = std::make_shared<VertexBuffer>(gfx, vertices);
		primitiveTopology = std::make_shared<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		indexBuffer = std::make_shared<IndexBuff>(gfx, indices);
		
		CommandPacket cmd{ this };
		
		{
			Step s0{ "default_box" };
			s0.AddBind(std::make_shared<PixelShader>(gfx, L"ConstantColorPS.cso"));
			auto vs = std::make_shared<VertexShader>(gfx, L"ColorBlenderVS.cso");
			auto vsBlob = vs->GetVBlob();
			s0.AddBind(std::move(vs));
			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
			};

			s0.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));



			s0.AddBind(std::make_shared<TransformationBuffer>(gfx,*this));
			s0.AddBind(std::make_shared< PSConstBuff <PixelShaderConstants>>(gfx, cb2, 0u));


			cmd.PushStep(s0);
			PushPacket(std::make_shared<CommandPacket>(cmd));
			
		}

		
		
		
		

		
		
		
		
		
		
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









