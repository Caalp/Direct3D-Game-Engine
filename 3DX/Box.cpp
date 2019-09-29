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
	if (isBindsEmpty())
	{
		struct Vertex 
		{
			float x;
			float y;
			float z;
		};
		std::vector<Vertex> vertices =
		{
			{ -1.0f,-1.0f,-1.0},
			{ 1.0f,-1.0f,-1.0f},
			{ -1.0f,1.0f,-1.0f},
			{ 1.0f,1.0f,-1.0f},
			{ -1.0f,-1.0f,1.0f},
			{ 1.0f,-1.0f,1.0f},
			{ -1.0f,1.0f,1.0f},
			{ 1.0f,1.0f,1.0f},
		};
		AddToStaticBind(std::make_unique<VertexBuffer>(gfx,vertices));
		AddToStaticBind(std::make_unique<PixelShader>(gfx, L"PixelShader.hlsl", "main", "ps_5_0"));
		AddToStaticBind(std::make_unique<VertexShader>(gfx, L"VertexShader.hlsl", "main", "vs_5_0"));
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
		AddToStaticBind(std::make_unique<Texture>(gfx, wall));
		AddToStaticBind(std::make_unique<SamplerState>(gfx));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			//{ "Color",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
		AddToBinds(std::make_unique<InputLayout>(gfx,ied,))
	}
	
}

void Box::Update(float ft)
{
	pitch += ft;
	yaw += ft;
	roll += ft;

}
