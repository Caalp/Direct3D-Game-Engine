#include "Box.h"
#include "ConstBuffs.h"
#include "IndexBuff.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "PrimitiveTopology.h"
#include "TransCB_.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "SamplerState.h"
#include "Texture.h"
#include "Surface.h"
Box::Box(Graphics & gfx, float x, float y) :
	x(x), y(y)
{
	if (true)
	{
		struct Vertex
		{
			float x;
			float y;
			float z;
			struct
			{
				float u;
				float v;
			}tex;
		};
		std::vector<Vertex> vertices =
		{
			{ -1.0f,-1.0f,-1.0,{0.0f,0.0f}},
		{ 1.0f,-1.0f,-1.0f,{1.0f,0.0f}},
		{ -1.0f,1.0f,-1.0f,{0.0f,1.0f}},
		{ 1.0f,1.0f,-1.0f,{1.0f,1.0f} },
		{ -1.0f,-1.0f,1.0f,{0.0f,0.0f}},
		{ 1.0f,-1.0f,1.0f,{1.0f,0.0f}	},
		{ -1.0f,1.0f,1.0f,{0.0f,1.0f}	},
		{ 1.0f,1.0f,1.0f,{1.0f,1.0f}	},
		};
		AddToStaticBind(std::make_unique<VertexBuffer>(gfx,vertices));
		AddToStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.hlsl", "main", "ps_5_0"));
		auto vs = std::make_unique<VertexShader>(gfx, L"VertexShader.hlsl", "main", "vs_5_0");
		auto vsBlob = vs->GetVBlob();
		AddToStaticBind(std::move(vs));
		std::vector<WORD> indices=
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
			
		};
		AddToStaticBind(std::make_unique<IndexBuff>(gfx, indices));
		Surface wall = Surface("kappa50.bmp");
		AddToStaticBind(std::make_unique<SamplerState>(gfx));
		AddToStaticBind(std::make_unique<Texture>(gfx, wall));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
		AddToBinds(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddToStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		
	}
		/*auto transCB = std::make_unique<TransCB_>(gfx);
		transCB->SetworldM_(gfx,DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)*DirectX::XMMatrixTranslation(x, y, 4.0f)));
		transCB->SetprojM_(gfx, (DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity())));
		transCB->SetviewM_(gfx, (DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f))));
		AddBind(std::move(transCB));*/
		AddBind(std::make_unique<TransCB_>(gfx, *this));
}

void Box::Update(float ft)
{
	pitch += ft;
	yaw += ft;
	roll += ft;

}





DirectX::XMMATRIX Box::GetViewXM() const
{
	return GetViewMatrix();
}

DirectX::XMMATRIX Box::GetWorldXM() const
{

	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) * DirectX::XMMatrixTranslation(x, y, 4.0f);
}

DirectX::XMMATRIX Box::GetProjXM() const
{
	return DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f);
}

//DirectX::XMMATRIX Box::GetTransformXM() const
//{
//	namespace dx = DirectX;
//	return 
//		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
//		
//		dx::XMMatrixTranslation(x, y, 4.0f);
//}
