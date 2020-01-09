#include "Box.h"
#include "additional_headers.h"
#include "Texture.h"
#include "Surface.h"


Box::Box(Graphics & gfx, float x, float y, float z) :
	x(x), y(y), z(z)
{

	if (!isStaticallyBinded())
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
		
		
		
		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		AddStaticBind(std::make_unique< PSConstBuff <PixelShaderConstants>>(gfx, cb2,1u));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorBlenderPS.cso"));
		
		

		auto vs = std::make_unique<VertexShader>(gfx, L"ColorBlenderVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		std::vector<WORD> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4

		};
		
		AddStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "POS",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }	
		};
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	}
	else
	{
		SetIndexBufferFromStatic();
	}
	struct VSMaterialConstant
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX worldviewProj;
		DirectX::XMFLOAT3 eyePos;
		//float padding;
		
	} VSConst;
	VSConst.model = DirectX::XMMatrixTranspose(GetTransformation());
	VSConst.worldviewProj = DirectX::XMMatrixTranspose(GetTransformation() * gfx.GetCamera());
	VSConst.eyePos = DirectX::XMFLOAT3(1.0f,1.0f,1.0f);

	AddBind(std::make_unique<VSConstBuff<VSMaterialConstant>>(gfx, VSConst));
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









